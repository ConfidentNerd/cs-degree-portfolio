const express = require('express');
const router = express.Router();

const tripsController = require('../controllers/trips');

// lists all trips
router.route('/trips').get(tripsController.tripsList);

// adds a trip
router.route('/trips').post(tripsController.tripsAddTrip);

// lists single trip
router.route('/trips/:tripCode').get(tripsController.tripsFindByCode);

// updates a trip
router.route('/trips/:tripCode').put(tripsController.tripsUpdateTrip);

// deletes a trip
router.route('/trips/:tripCode').delete(tripsController.tripsDeleteTrip);

module.exports = router;
