const express = require('express');
const router = express.Router();
const jwt = require('jsonwebtoken');

const tripsController = require('../controllers/trips');
const authController = require('../controllers/authentication');

// authenticate JWT
function authenticateJWT(req, res, next) {
    // console.log('In Middleware');

    const authHeader = req.headers['authorization'];
    // console.log('Auth Header: ' + authHeader);

    if(authHeader == null)
    {
        console.log('Auth Header Required but NOT PRESENT!');
        return res.sendStatus(401);
    }

    let headers = authHeader.split(' ');
    if(headers.length < 1)
    {
        console.log('Not enough tokens in Auth Header: ' + headers.length);
        return res.sendStatus(501);
    }

    const token = authHeader.split(' ')[1];
    // console.log('Token: ' + token);

    if(token == null)
    {
        console.log('Null Bearer Token');
        return res.sendStatus(401);
    }

    // console.log(process.env.JWT_SECRET);
    // console.log(jwt.decode(token));
    const verified = jwt.verify(token, process.env.JWT_SECRET, (err, verified) => {
        if(err)
        {
            return res.sendStatus(401).json('Token Validation Error!');
        }
        req.auth = verified;
    });
    next();
}

// registers a new user
router.route('/register').post(authController.register);

// logs in a user
router.route('/login').post(authController.login);

// lists all trips
router.route('/trips').get(tripsController.tripsList);

// adds a trip
router.route('/trips').post(authenticateJWT, tripsController.tripsAddTrip);

// lists single trip
router.route('/trips/:tripCode').get(tripsController.tripsFindByCode);

// updates a trip
router.route('/trips/:tripCode').put(authenticateJWT, tripsController.tripsUpdateTrip);

// deletes a trip
router.route('/trips/:tripCode').delete(authenticateJWT, tripsController.tripsDeleteTrip);

module.exports = router;
