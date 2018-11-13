function expectKeyInJSON(key, json) {
  if (!(key in json)) throw Error(`Expected '${key}' in JSON object`)
}


function setTextLayer(key, config, value, animData) {
  const index = config[key].index;
  const value = 

  data.layers[index].t.d.k[0].s.t = value;
  return data;
}

function setWidth(index) {
  console.log('bogus');
}


function extractTextLayerNames(config) {
  const layerNames = [];
  for (const key in config['textLayers']) {
    layerNames.push(key)
  }
  return layerNames;
}

function fakeConfigString() {
  return JSON.stringify({
    "textLayers": {
      "name": {
        "index": 0,
        "case": "upper",
        "maxLength": 12
      },
      "email": {
        "index": 1,
        "case": "lower",
        "maxLength": 64
      }
    }
  });
}

const config = JSON.parse(fakeConfigString());


const textLayerNames = extractTextLayerNames(config);
console.log(textLayerNames);