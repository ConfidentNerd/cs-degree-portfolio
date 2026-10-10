const mongoose = require('mongoose');
const Trip = require('../models/travlr');
const Model = mongoose.model('trips');

// GET: /trips - lists all the trips
const tripsList = async (req, res) => {
    const q = await Model
        .find({}) // return all records
        .exec();
        
    // console.log(q);

    if (!q) {
        // DB returned no data
        return res
            .status(404)
            .json(err);
    } else {
        // return resulting trip list
        return res
            .status(200)
            .json(q);
    }
};

// GET: /trips/:tripCode - lists a single trip
const tripsFindByCode = async (req, res) => {
    const q = await Model
        .find({ 'code': req.params.tripCode }) // return single record
        .exec();

    // console.log(q);

    if (!q) {
        return res
            .status(404)
            .json(err);
    } else {
        return res
            .status(200)
            .json(q);
    }
};

// POST: /trips - adds a new trip
const tripsAddTrip = async(req, res) => {
    const newTrip = new Trip({
        code: req.body.code,
        name: req.body.name,
        length: req.body.length,
        start: req.body.start,
        resort: req.body.resort,
        perPerson: req.body.perPerson,
        image: req.body.image,
        description: req.body.description
    });

    const q = await newTrip.save();

        if(!q)
        { // DB returned no data
            return res
                .status(400)
                .json(err);
        } else { // return new trip
            return res
                .status(201)
                .json(q);
        }

        // console.log(q);
};

// PUT: /trips/:tripCode - updates a trip
const tripsUpdateTrip = async(req, res) => {

    console.log(req.params);
    console.log(req.body);

    const q = await Model
        .findOneAndUpdate(
            { 'code' : req.params.tripCode },
            {
                code: req.body.code,
                name: req.body.name,
                length: req.body.length,
                start: req.body.start,
                resort: req.body.resort,
                perPerson: req.body.perPerson,
                image: req.body.image,
                description: req.body.description
            }
        )
        .exec();

        if(!q)
        { // DB returned no data
            return res
                .status(400)
                .json(err);
        } else { // return resulting updated trip
            return res
                .status(201)
                .json(q);
        }

        // console.log(q);
};

// DELETE: /trips/:tripCode - deletes a trip
const tripsDeleteTrip = async(req, res) => {
    const q = await Model
        .findOneAndDelete({ 'code' : req.params.tripCode })
        .exec();

        if(!q)
        { // DB returned no data
            return res
                .status(404)
                .json(err);
        } else { // return deleted trip
            return res
                .status(200)
                .json(q);
        }

        // console.log(q);
};

module.exports = {
    tripsList,
    tripsFindByCode,
    tripsAddTrip,
    tripsUpdateTrip,
    tripsDeleteTrip
};
