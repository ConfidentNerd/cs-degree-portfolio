const express = require('express');
const router = express.Router();

const tripsController = require('../controllers/trips');

// lists all trips
router.route('/trips').get(tripsController.tripsList);

// lists single trip
router.route('/trips/:tripCode').get(tripsController.tripsFindByCode);

module.exports = router;
