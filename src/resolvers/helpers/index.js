const fs = require("fs");
const hash = require("object-hash");

module.exports = require("./factory")({ fs, hash });
