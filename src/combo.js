const File = require('./file');
const Configure = require('./configure');

const params = {
  "text": 'john',
}
const config = File.loadJSON('../designs/welcome.config.json');
const animData = File.loadJSON('../designs/welcome.json');
Configure.setLayers(params, config, animData);

File.writeJSON(animData, '../designs/test.json');
