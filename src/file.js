const fs = require("fs");

function loadJSON(path) {
  return JSON.parse(fs.readFileSync(path));
}

function writeJSON(data, path) {
  fs.writeFileSync(path, JSON.stringify(data));
}

exports.loadJSON = loadJSON;
exports.writeJSON = writeJSON;
