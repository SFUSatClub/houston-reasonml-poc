const fs = require("fs");
const hash = require("object-hash");

module.exports = require("./helper.factory")({ fs, hash });
