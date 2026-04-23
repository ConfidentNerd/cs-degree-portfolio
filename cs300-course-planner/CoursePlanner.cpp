/*******************************************************************************
 * Name:    Uri Naor
 * Date:    Apr 18
 * Purpose: Project 2
 ******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

enum {
    SUCCESS = 0,
    FAILURE = 1
};

/*******************************************************************************
                          FORWARD DECLARATIONS
*******************************************************************************/
class BinarySearchTree;
struct Course;

int loadData(BinarySearchTree* courses);
void printCourseDetails(Course course);
void printMenu();

/*******************************************************************************
                            STRUCTS & CLASSES
*******************************************************************************/

struct Course {
    string code;
    string name;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node *left;
    Node *right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

class BinarySearchTree {
private:
    Node* root;
    
    void destroyTree(Node* node);
    void inOrder(Node* node);
    void addNode(Node* node, Course course);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    
    void InOrder();
    void Insert(Course course);
    Course Search(string code);
};


/*******************************************************************************
                          CONSTRUCTORS & METHODS
*******************************************************************************/

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    destroyTree(root);
}

void BinarySearchTree::InOrder() {
    // call helper method
    inOrder(root);
}

void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        addNode(root, course);
    }
}

Course BinarySearchTree::Search(string code){
    Node* curr = root;

    while (curr != nullptr) {
        if (curr->course.code == code) {
            return curr->course;
        } else if (code < curr->course.code) {
            curr = curr->left;
        } else if (code > curr->course.code) {
            curr = curr->right;
        }
    }

    // if can't find, return an empty course object.
    Course course;
    return course;
}


/*******************************************************************************
                    PRIVATE HELPER METHODS
*******************************************************************************/

void BinarySearchTree::destroyTree(Node* node) {
    // used post order so children will be freed before parent
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void BinarySearchTree::inOrder(Node* node) {
    if (node == nullptr) {
        return;
    }

    inOrder(node->left);
    cout << node->course.code << ", " << node->course.name << endl;
    inOrder(node->right);
}

void BinarySearchTree::addNode(Node* node, Course course) {    
    // I'm assuming course codes can't be equal.
    if (node == nullptr) {
        return;
    }

    if (course.code < node->course.code) {
        if (node->left == nullptr) {
            node->left = new Node(course);
            return;
        }
        // else go into left child
        addNode(node->left, course);
    }

    if (course.code > node->course.code) {
        if (node->right == nullptr) {
            node->right = new Node(course);
            return;
        }
        // else go into right child
        addNode(node->right, course);
    }
}

int loadData(BinarySearchTree* courses) {
    string fileName;
    ifstream inputFile;

    while (!inputFile.is_open()) {
        cout << "Please enter name of file: ";
        cin >> fileName;

        // If fileName is missing or doesn't have proper extension continue looping
        if (fileName.length() < 5 || fileName.substr(fileName.length() - 4) != ".csv") {
            cout << "Wrong file extension, or missing file name. Please try again\n" << endl;
            continue;
        }

        inputFile.open(fileName);

        if (!inputFile.is_open()) {
            cout << "Could not open file, please try again" << endl;
        }
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;

        vector<string> parameters;

        // iterate over all items in the comma seperated line
        while (getline(ss, token, ',')) {
            // make sure to also ignore \r which might be present at end of lines
            if (!token.empty() && token != "\r") {
                parameters.push_back(token);
            }
        }

        if (parameters.size() < 2) {
            cout << "ERROR: line with incorrect format was found\n";
            inputFile.close();
            return FAILURE;
        }

        Course newCourse;
        newCourse.code = parameters[0];
        newCourse.name = parameters[1];

        if (parameters.size() > 2) {
            for (size_t i = 2; i < parameters.size(); i++) {
                newCourse.prerequisites.push_back(parameters[i]);
            }
        }

        courses->Insert(newCourse);
    }

    inputFile.close();
    return SUCCESS;
}

void printCourseDetails(Course course) {
    //output course code, course name and prereqs courses codes
    cout << course.code << ", " << course.name << endl;

    cout << "Prerequisites: ";
    if (course.prerequisites.empty()) {
            cout << "None" << endl;
    } else {
        size_t prereqAmount = course.prerequisites.size();

        for (size_t i = 0; i < prereqAmount; i++) {
            cout << course.prerequisites[i];
            
            // add comma after each prereq except for last
            if (i < prereqAmount - 1) {
                cout << ", ";
            }
        }
    }

    cout << endl;
}

void printMenu() {
    cout << "\n==== MENU ====" << endl;
    cout << "1) Load Into Data Structure" << endl;
    cout << "2) Print Sorted Course List" << endl;
    cout << "3) Print Specific Course Info" << endl;
    cout << "9) Exit The Program" << endl;
    cout << "Please enter your choice (as a number): ";
}


/*******************************************************************************
                                     MAIN
*******************************************************************************/

int main()
{
    BinarySearchTree* courses = new BinarySearchTree();
    bool exit = false;
    // used string on purpose so no issues if user inputs a non number value
    string userChoice = "";

    while(!exit) {
        printMenu();

        cin >> userChoice;
        cout << endl; // nicer spacing between input and prints

        if (userChoice == "1") {
            int status = loadData(courses);
            if (status == SUCCESS) {
                cout << "Data loaded successfully" << endl;
            } else {
                cout << "Loading failed" << endl;
            }
        }
        else if (userChoice == "2") {
            cout << "Printing all courses from file, sorted in alphanumeric order:" << endl;
            courses->InOrder();
        }
        else if (userChoice == "3") {
            string courseCode = "";

            cout << "What course do you want to know about? ";
            cin >> courseCode;
            
            // make sure user input is uppercase to match the expect CSV format
            for (size_t i = 0; i < courseCode.length(); i++) {
                courseCode[i] = toupper(courseCode[i]);
            }

            Course foundCourse = courses->Search(courseCode);
            
            if (foundCourse.code.empty()) {
                cout << "Sorry, a course with this code was not found" << endl;
                continue;
            }

            printCourseDetails(foundCourse);
        }
        else if (userChoice == "9") {
            exit = true;
        }
        else {
            cout << "\"" << userChoice << "\"" << " is not a valid option.\n"
            << "Please insert only a digit. Either 1, 2, 3 or 9" << endl;
        }
    }

    cout << "Closing program..." << endl;
    
    delete courses;
    return 0;
}