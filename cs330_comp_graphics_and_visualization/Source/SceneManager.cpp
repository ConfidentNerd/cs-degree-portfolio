///////////////////////////////////////////////////////////////////////////////
// scenemanager.cpp
// ================
// This file contains the implementation of the `SceneManager` class, which is 
// responsible for managing the preparation and rendering of 3D scenes. It 
// handles textures, materials, lighting configurations, and object rendering.
//
// AUTHOR: Brian Battersby
// INSTITUTION: Southern New Hampshire University (SNHU)
// COURSE: CS-330 Computational Graphics and Visualization
//
// INITIAL VERSION: November 1, 2023
// LAST REVISED: December 1, 2024
//
// RESPONSIBILITIES:
// - Load, bind, and manage textures in OpenGL.
// - Define materials and lighting properties for 3D objects.
// - Manage transformations and shader configurations.
// - Render complex 3D scenes using basic meshes.
//
// NOTE: This implementation leverages external libraries like `stb_image` for 
// texture loading and GLM for matrix and vector operations.
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

// declaration of global variables
namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
}

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(ShaderManager* pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();
}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager()
{
	m_pShaderManager = NULL;
	delete m_basicMeshes;
	m_basicMeshes = NULL;
}

/***********************************************************
 *  CreateGLTexture()
 *
 *  This method is used for loading textures from image files,
 *  configuring the texture mapping parameters in OpenGL,
 *  generating the mipmaps, and loading the read texture into
 *  the next available texture slot in memory.
 ***********************************************************/
bool SceneManager::CreateGLTexture(const char* filename, std::string tag)
{
	int width = 0;
	int height = 0;
	int colorChannels = 0;
	GLuint textureID = 0;

	// indicate to always flip images vertically when loaded
	stbi_set_flip_vertically_on_load(true);

	// try to parse the image data from the specified image file
	unsigned char* image = stbi_load(
		filename,
		&width,
		&height,
		&colorChannels,
		0);

	// if the image was successfully read from the image file
	if (image)
	{
		std::cout << "Successfully loaded image:" << filename << ", width:" << width << ", height:" << height << ", channels:" << colorChannels << std::endl;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if the loaded image is in RGB format
		if (colorChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		// if the loaded image is in RGBA format - it supports transparency
		else if (colorChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			std::cout << "Not implemented to handle image with " << colorChannels << " channels" << std::endl;
			return false;
		}

		// generate the texture mipmaps for mapping textures to lower resolutions
		glGenerateMipmap(GL_TEXTURE_2D);

		// free the image data from local memory
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

		// register the loaded texture and associate it with the special tag string
		m_textureIDs[m_loadedTextures].ID = textureID;
		m_textureIDs[m_loadedTextures].tag = tag;
		m_loadedTextures++;

		return true;
	}

	std::cout << "Could not load image:" << filename << std::endl;

	// Error loading the image
	return false;
}

/***********************************************************
 *  BindGLTextures()
 *
 *  This method is used for binding the loaded textures to
 *  OpenGL texture memory slots.  There are up to 16 slots.
 ***********************************************************/
void SceneManager::BindGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  DestroyGLTextures()
 *
 *  This method is used for freeing the memory in all the
 *  used texture memory slots.
 ***********************************************************/
void SceneManager::DestroyGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		glGenTextures(1, &m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  FindTextureID()
 *
 *  This method is used for getting an ID for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureID(std::string tag)
{
	int textureID = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureID = m_textureIDs[index].ID;
			bFound = true;
		}
		else
			index++;
	}

	return(textureID);
}

/***********************************************************
 *  FindTextureSlot()
 *
 *  This method is used for getting a slot index for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureSlot(std::string tag)
{
	int textureSlot = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureSlot = index;
			bFound = true;
		}
		else
			index++;
	}

	return(textureSlot);
}

/***********************************************************
 *  FindMaterial()
 *
 *  This method is used for getting a material from the previously
 *  defined materials list that is associated with the passed in tag.
 ***********************************************************/
bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material)
{
	if (m_objectMaterials.size() == 0)
	{
		return(false);
	}

	int index = 0;
	bool bFound = false;
	while ((index < m_objectMaterials.size()) && (bFound == false))
	{
		if (m_objectMaterials[index].tag.compare(tag) == 0)
		{
			bFound = true;
			material.diffuseColor = m_objectMaterials[index].diffuseColor;
			material.specularColor = m_objectMaterials[index].specularColor;
			material.shininess = m_objectMaterials[index].shininess;
		}
		else
		{
			index++;
		}
	}

	return(true);
}

/***********************************************************
 *  SetTransformations()
 *
 *  This method is used for setting the transform buffer
 *  using the passed in transformation values.
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ)
{
	// variables for this method
	glm::mat4 modelView;
	glm::mat4 scale;
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotationZ;
	glm::mat4 translation;

	// set the scale value in the transform buffer
	scale = glm::scale(scaleXYZ);
	// set the rotation values in the transform buffer
	rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
	rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
	// set the translation value in the transform buffer
	translation = glm::translate(positionXYZ);

	modelView = translation * rotationZ * rotationY * rotationX * scale;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setMat4Value(g_ModelName, modelView);
	}
}

/***********************************************************
 *  SetShaderColor()
 *
 *  This method is used for setting the passed in color
 *  into the shader for the next draw command
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	// variables for this method
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, false);
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

/***********************************************************
 *  SetShaderTexture()
 *
 *  This method is used for setting the texture data
 *  associated with the passed in ID into the shader.
 ***********************************************************/
void SceneManager::SetShaderTexture(
	std::string textureTag)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, true);

		int textureID = -1;
		textureID = FindTextureSlot(textureTag);
		m_pShaderManager->setSampler2DValue(g_TextureValueName, textureID);
	}
}

/***********************************************************
 *  SetTextureUVScale()
 *
 *  This method is used for setting the texture UV scale
 *  values into the shader.
 ***********************************************************/
void SceneManager::SetTextureUVScale(float u, float v)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setVec2Value("UVscale", glm::vec2(u, v));
	}
}

/***********************************************************
 *  SetShaderMaterial()
 *
 *  This method is used for passing the material values
 *  into the shader.
 ***********************************************************/
void SceneManager::SetShaderMaterial(
	std::string materialTag)
{
	if (m_objectMaterials.size() > 0)
	{
		OBJECT_MATERIAL material;
		bool bReturn = false;

		bReturn = FindMaterial(materialTag, material);
		if (bReturn == true)
		{
			m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
			m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
			m_pShaderManager->setFloatValue("material.shininess", material.shininess);
		}
	}
}

/**************************************************************/
/*** STUDENTS CAN MODIFY the code in the methods BELOW for  ***/
/*** preparing and rendering their own 3D replicated scenes.***/
/*** Please refer to the code in the OpenGL sample project  ***/
/*** for assistance.                                        ***/
/**************************************************************/

/***********************************************************
  *  LoadSceneTextures()
  *
  *  This method is used for preparing the 3D scene by loading
  *  the shapes, textures in memory to support the 3D scene
  *  rendering
  ***********************************************************/
void SceneManager::LoadSceneTextures()
{
	// used similar logic from the OpenGL sample, loading the textures I downloaded from ambientcg.com
	// they're using the The Creative Commons CC0 license.

	bool bReturn = false;
	
	// edited the carpet texture I downloaded to be completely grey to fit the original image
	bReturn = CreateGLTexture("textures/Carpet003v2.jpg", "rug");

	bReturn = CreateGLTexture("textures/Metal028.jpg", "blackMetal");

	bReturn = CreateGLTexture("textures/WoodFloor051.jpg", "floor");

	bReturn = CreateGLTexture("textures/Wood007.jpg", "wood");

	// edited to beige color which is why I named it v2
	bReturn = CreateGLTexture("textures/Fabric019v2.jpg", "fabric");

	bReturn = CreateGLTexture("textures/Paper001.jpg", "paper");

	bReturn = CreateGLTexture("textures/Fabric081.jpg", "cover");

	// after the texture image data is loaded into memory, the
	// loaded textures need to be bound to texture slots - there
	// are a total of 16 available slots for scene textures
	BindGLTextures();
}

void SceneManager::DefineObjectMaterials()
{
	// adjusted from the OpenGL sample to be used as metal, wood and fabric materials

	OBJECT_MATERIAL metalMaterial;
	metalMaterial.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	metalMaterial.specularColor = glm::vec3(0.7f, 0.7f, 0.7f);
	metalMaterial.shininess = 50.0f;
	metalMaterial.tag = "metal";

	m_objectMaterials.push_back(metalMaterial);

	OBJECT_MATERIAL woodMaterial;
	woodMaterial.diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	woodMaterial.specularColor = glm::vec3(0.2f, 0.2f, 0.2f);
	woodMaterial.shininess = 20.0f;
	woodMaterial.tag = "wood";

	m_objectMaterials.push_back(woodMaterial);

	OBJECT_MATERIAL fabricMaterial;
	fabricMaterial.diffuseColor = glm::vec3(0.8f, 0.8f, 0.8f);
	fabricMaterial.specularColor = glm::vec3(0.0f, 0.0f, 0.0f);
	fabricMaterial.shininess = 0.15f;
	fabricMaterial.tag = "fabric";

	m_objectMaterials.push_back(fabricMaterial);
}

/***********************************************************
 *  SetupSceneLights()
 *
 *  This method is called to add and configure the light
 *  sources for the 3D scene.  There are up to 4 light sources.
 ***********************************************************/
void SceneManager::SetupSceneLights()
{
	// adjusted from the OpenGL sample to provide 2 distinct light sources


	// Enable lighting in the shader
	m_pShaderManager->setBoolValue(g_UseLightingName, true);

	
	// Directional light setup
	m_pShaderManager->setVec3Value("directionalLight.direction", -0.5f, -1.0f, -0.2f);
	m_pShaderManager->setVec3Value("directionalLight.ambient", 0.3f, 0.3f, 0.3f);
	m_pShaderManager->setVec3Value("directionalLight.diffuse", 0.3f, 0.3f, 0.3f);
	m_pShaderManager->setVec3Value("directionalLight.specular", 0.1f, 0.1f, 0.1f);
	m_pShaderManager->setBoolValue("directionalLight.bActive", true);

	
	// Point light 1 - key light
	m_pShaderManager->setVec3Value("pointLights[0].position", 9.0f, 4.5f, 6.0f);
	m_pShaderManager->setVec3Value("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
	// added orange color
	m_pShaderManager->setVec3Value("pointLights[0].diffuse", 1.0f, 0.5f, 0.0f);
	m_pShaderManager->setVec3Value("pointLights[0].specular", 0.3f, 0.3f, 0.3f);
	m_pShaderManager->setFloatValue("pointLights[0].constant", 1.0f);
	m_pShaderManager->setFloatValue("pointLights[0].linear", 0.09f);
	m_pShaderManager->setFloatValue("pointLights[0].quadratic", 0.032f);
	m_pShaderManager->setBoolValue("pointLights[0].bActive", true);

	
	// Point light 2 - fill light
	m_pShaderManager->setVec3Value("pointLights[1].position", -5.0f, 3.0f, 4.0f);
	m_pShaderManager->setVec3Value("pointLights[1].ambient", 0.0f, 0.0f, 0.0f);
	m_pShaderManager->setVec3Value("pointLights[1].diffuse", 0.1f, 0.1f, 0.1f);
	m_pShaderManager->setVec3Value("pointLights[1].specular", 0.1f, 0.1f, 0.1f);
	m_pShaderManager->setFloatValue("pointLights[1].constant", 1.0f);
	m_pShaderManager->setFloatValue("pointLights[1].linear", 0.09f);
	m_pShaderManager->setFloatValue("pointLights[1].quadratic", 0.032f);
	m_pShaderManager->setBoolValue("pointLights[1].bActive", true);

}

/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes, textures in memory to support the 3D scene
 *  rendering
 ***********************************************************/
void SceneManager::PrepareScene()
{
	// load the textures for the 3D scene
	LoadSceneTextures();

	// define the objects materials in order to properly light them
	DefineObjectMaterials();

	// add and define the light sources for the scene
	SetupSceneLights();

	// only one instance of a particular mesh needs to be
	// loaded in memory no matter how many times it is drawn
	// in the rendered 3D scene

	m_basicMeshes->LoadPlaneMesh();
	// Load basic shapes needed to create the scene
	m_basicMeshes->LoadTaperedCylinderMesh();
	m_basicMeshes->LoadCylinderMesh();
	m_basicMeshes->LoadBoxMesh();
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{
	/******* Floor *******/

	/* Plane 1 - the actual floor */
	/******************************************************************/
	// scaled the texture differently than the mesh scale so it will look bigger and closer to the image I chose
	RenderShape(
		glm::vec3(20.0f, 1.0f, 10.0f),
		0.0f, -10.0f, 0.0f,
		glm::vec3(0.0f, 0.0f, 5.0f),
		"floor",
		5.0f, 1.0f,
		"wood",
		"plane"
	);

	/* Plane 2 - rug */
	/******************************************************************/
	RenderShape(
		glm::vec3(6.0f, 1.0f, 3.0f),
		0.0f, -10.0f, 0.0f,
		glm::vec3(-1.0f, 0.01f, 5.5f),
		"rug",
		1.0f,
		1.0f,
		"fabric",
		"plane"
	);

	/******* Table *******/

	/* Cylinder */
	/******************************************************************/
	// made sure to scale texture according to mesh scale so it doesn't stretch
	RenderShape(
		glm::vec3(1.5f, 0.20f, 1.5f),
		0.0f, 0.0f, 0.0f,
		glm::vec3(3.5f, 3.0f, 3.5f),
		"wood",
		1.5f, 1.5f,
		"wood",
		"cylinder"
	);

	/* Tapered Cylinder */
	/******************************************************************/
	// made sure to scale texture according to mesh scale so it doesn't stretch
	RenderShape(
		glm::vec3(1.0f, 3.0f, 1.0f),
		0.0f, 0.0f, 0.0f,
		glm::vec3(3.5f, 0.0f, 3.5f),
		"blackMetal",
		1.0f, 3.0f,
		"metal",
		"tapered_cylinder"
	);

	/******* Book *******/

	// const to determine the paper and covers position
	const float BOOK_X_POSITION = 3.25f;

	/* Box 1 - bottom cover */
	/******************************************************************/
	// set shader material to fabric (I think a book should be mostly non-reflective similarly to fabric)
	RenderShape(
		glm::vec3(0.9f, 0.025f, 1.3f),
		0.0f, 0.0f, 0.0f,
		glm::vec3(BOOK_X_POSITION, 3.2125f, 3.5f),
		"cover",
		0.9f, 1.3f,
		"fabric",
		"box"
	);

	/* Box 2 - paper pages */
	/******************************************************************/
	RenderShape(
		glm::vec3(0.85f, 0.2f, 1.25f),
		0.0f, 0.0f, 0.0f,
		glm::vec3(BOOK_X_POSITION, 3.325f, 3.5f),
		"paper",
		0.85f, 1.25f,
		"fabric",
		"box"
	);

	/* Box 3 - top cover */
	/******************************************************************/
	RenderShape(
		glm::vec3(0.9f, 0.025f, 1.3f),
		0.0f, 0.0f, 0.0f,
		glm::vec3(BOOK_X_POSITION, 3.4375f, 3.5f),
		"cover",
		0.9f, 1.3f,
		"fabric",
		"box"
	);

	/* Box 4 - back cover */
	/******************************************************************/
	RenderShape(
		glm::vec3(0.025f, 0.25f, 1.3f),
		0.0f, 0.0f, 0.0f,
		glm::vec3(2.80f, 3.325f, 3.5f),
		"cover",
		0.25f, 1.3f,
		"fabric",
		"box"
	);

	/******* Armchair *******/

	/* Box 1 - base */
	/******************************************************************/
	// made sure to scale texture according to mesh scale so it doesn't stretch
	RenderShape(
		glm::vec3(3.5f, 0.3f, 3.5f),
		0.0f, 40.0f, 0.0f,
		glm::vec3(-2.0f, 0.85f, 4.0f),
		"wood",
		3.5f, 3.5f,
		"wood",
		"box"
	);

	/* Box 2 - Cushion */
	/******************************************************************/
	// looks better stretched so this is on purpose
	RenderShape(
		glm::vec3(3.5f, 1.0f, 3.5f),
		0.0f, 40.0f, 0.0f,
		glm::vec3(-2.0f, 1.5f, 4.0f),
		"fabric",
		0.6f, 0.6f,
		"fabric",
		"box"
	);

	/* Box 3 - Left arm */
	/******************************************************************/
	// made sure to scale texture according to mesh scale so it doesn't stretch
	RenderShape(
		glm::vec3(1.0f, 3.0f, 4.0f),
		0.0f, 40.0f, 0.0f,
		glm::vec3(-3.56f, 1.5f, 5.64f),
		"wood",
		3.0f, 4.0f,
		"wood",
		"box"
	);

	/* Box 4 - right arm */
	/******************************************************************/
	// made sure to scale texture according to mesh scale so it doesn't stretch
	RenderShape(
		glm::vec3(1.0f, 3.0f, 4.0f),
		0.0f, 40.0f, 0.0f,
		glm::vec3(-0.12f, 1.5f, 2.75f),
		"wood",
		3.0f, 4.0f,
		"wood",
		"box"
	);

	/* Box 5 - back */
	/******************************************************************/
	RenderShape(
		glm::vec3(3.5f, 3.5f, 1.0f),
		-10.0f, 40.0f, 0.0f,
		glm::vec3(-2.80f, 3.25f, 3.04f),
		"fabric",
		0.6f, 0.6f,
		"fabric",
		"box"
	);
}

// helper method to render shapes and reduce repeated object definitions
void SceneManager::RenderShape(
	glm::vec3 scaleXYZ,
	float XrotationDegrees, float YrotationDegrees, float ZrotationDegrees,
	glm::vec3 positionXYZ,
	std::string textureTag,
	float uvScaleU, float uvScaleV,
	std::string materialTag,
	std::string shapeType)
{
	// set the transformations into memory to be used on the drawn meshes
	// scale, rotation, position
	SetTransformations(
		scaleXYZ,
		XrotationDegrees,
		YrotationDegrees,
		ZrotationDegrees,
		positionXYZ);

	// set textures - the texture asset via texture tag, scale, and defined material
	SetShaderTexture(textureTag);
	SetTextureUVScale(uvScaleU, uvScaleV);
	SetShaderMaterial(materialTag);

	// call the correct method according the the mesh shape type
	// only added the shapes I actively use in my scene but would need to add other shapes if the scene expands
	if (shapeType == "plane") {
		m_basicMeshes->DrawPlaneMesh();
	}
	else if (shapeType == "box") {
		m_basicMeshes->DrawBoxMesh();
	}
	else if (shapeType == "cylinder") {
		m_basicMeshes->DrawCylinderMesh();
	}
	else if (shapeType == "tapered_cylinder") {
		m_basicMeshes->DrawTaperedCylinderMesh();
	}
}


