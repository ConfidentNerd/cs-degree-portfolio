# Travlr Getaways Web Application

## Architecture

**Compare and contrast the types of frontend development you used in your full stack project, including Express HTML, JavaScript, and the single-page application (SPA).**

The Angular project is different from the Express customer-facing page, because the customer-facing site follows the MVC pattern where a user interacts with the view, but everything is rendered on the server side, while the Angular admin app is an SPA, meaning that the page re-renders itself as needed using the logic that runs in the client’s browser.

On the SPA, the heavy lifting is being done right on the browser, and components react to state changes and only re-render the components that need to change. For example, if I click “Add Trip” the view switches to the form, without reloading the entire page.

The main advantage is that we can reduce loading times and make our websites feel more like web “apps”, by instantly responding to user clicks and smooth animations.

**Why did the backend use a NoSQL MongoDB database?**

MongoDB was chosen as the backend database due to its schema-less design and the fact that JavaScript objects map directly to MongoDB entries, making CRUD operations smooth, easy and seamless.

## Functionality

**How is JSON different from Javascript and how does JSON tie together the frontend and backend development pieces?**

JSON is essentially a text format for storing and sending data that is shaped like a JavaScript object, while JavaScript is the full programming language. However unlike a JavaScript object, a JSON can only hold data, but not functions or logic.

JSON is what connects the frontend and backend. On the server, Express passes the request to the matching Controller function, which uses Mongoose to get the data from MongoDB. Afterwards the results travel back similarly: MongoDB returns them to the server, the server sends them to the browser as JSON, and the frontend saves them so the view could display them properly.

**Provide instances in the full stack process when you refactored code to improve functionality and efficiencies, and name the benefits that come from reusable user interface (UI) components.**

One example is the travel page, which at the start of the project had the trips hardcoded and was later refactored to get them from the API instead. This was especially a good way to reuse data as it allowed both the customer-facing site and the admin SPA to share the same data. The benefit that comes from using reusable components is that we don't need to edit the HTML manually in each page that reuses the same data, which otherwise would cause us to need to keep track of all places, and once we inevitably miss one, introduce inconsistencies across pages.

Making future changes becomes a lot easier due to reusable components. Changing code inside a component would reflect everywhere that component is being used.

## Testing

**Methods for request and retrieval necessitate various types of API testing of endpoints, in addition to the difficulties of testing with added layers of security. Explain your understanding of methods, endpoints, and security in a full stack application.**

Since a part of the code runs on the browser and communicates with our server, we need to secure it. We need to make sure only logged-in admins are able to change trips, which means we would need to add a login feature with hashed passwords, authenticate with JSON Web Tokens, and protect our API routes.

For Sign In, the entered email and password are sent to /api/login which the server then checks against the credentials that are already saved in the Mongo database, and if they match it sends back a JWT that the browser saves. For different Admin actions like adding, deleting or editing a trip, that token is then attached to the request, and the server verifies the token to decide whether to reject it, or allow changes to be made to the data in the database.

A table showcasing the different API endpoints is shown below.

| Method | Purpose | URL | Notes |
|---|---|---|---|
| **GET** | Retrieve list of trips | /api/trips | Returns all trips from the database as a JSON array. No login needed. Used by the Travel page. |
| **GET** | Retrieve a single trip | /api/trips/:tripCode | Returns the details of one trip matching the code in the URL. No login needed. Used to get a single trip from the database. |
| **DELETE** | Delete a trip | /api/trips/:tripCode | Removes the trip matching the code in the URL from the DB. Login needed. Used by the delete button in the admin SPA. |
| **POST** | Add a new trip | /api/trips | Creates new trip from the data sent in request. Login needed. Used by the Add Trip form in the admin SPA. |
| **PUT** | Update a trip | /api/trips/:tripCode | Updates trip matching the code in URL with the data sent in the request. Login needed. Used by the Edit Trip form in the admin SPA. |
| **POST** | Register a new user | /api/register | Creates a new user with a hashed password and returns a JWT. No login needed. Used to create admin accounts. |
| **POST** | Log in a user | /api/login | Checks email and password against the data in DB and returns a JWT if they match. No login needed. Used by the Login page in the admin SPA. |

For the API, I used Postman to send requests to the Express server, such as a GET to /api/trips/:tripCode to see if the right data was returned, then a PUT to the same route with one value changed, and then a GET again to double check that the change worked.

Also, since there are two different parts to the application, a customer site and an admin SPA, both of which depend on the same API and database, this means that any change to the API or data structure needs to be tested on both.

## Reflection

**How has this course helped you in reaching your professional goals? What skills have you learned, developed, or mastered in this course to help you become a more marketable candidate in your career field?**

As someone who already works in a part-time full-stack developer role in a university, while I was familiar with some concepts I do feel like I learned a ton. First of all I had no experience with Angular previously, and I found it really fun to have two different websites share the same API in one project.

Overall I believe this course has sharpened my skills further and I had a lot of fun along the way.

## Contact
Uri Naor