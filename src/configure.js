// params + config -> validation -> response
//
// User sends params. Picasso uses params to modify animData. Picasso attempts to render animData.
//

function changeTextCase(text, textCase) {
  switch (textCase) {
    case 'upper':
      return text.toUpperCase();
    case 'lower':
      return text.toLowerCase();
    case 'title':
      console.log(text);
      break;
  }
  return text.toUpperCase();
}

function setTextLayer(key, config, text, animData) {
  if (text.length > config[key].maxLength) {
    throw Error(`${text} exceeds max length of ${config[key].maxLength}`)
  }

  // Process text
  text = changeTextCase(text, config[key].case);

  // Set layer
  const index = config[key].index;
  animData.layers[index].t.d.k[0].s.t = text;
}

function setTextLayers(params, config, animData) {
  for (const key in config['textLayers']) {
    setTextLayer(key, config['textLayers'], params[key], animData);
  }
}

function setLayers(params, config, animData) {
  setTextLayers(params, config, animData);
  // Add more processing here
}

exports.setLayers = setLayers;
