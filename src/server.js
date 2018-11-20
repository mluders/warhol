if (process.cwd().split('/').pop() !== 'warhol') {
  throw Error('Expected root directory');
}

const File = require('./file');
const Configure = require('./configure');
const Render = require('./render');
const fs = require('fs');
const express = require('express');
const app = express();
const port = 8080;

app.get('/:designName', function (req, res) {
  let config;
  let animData;
  try {
    config = File.loadJSON(`./designs/${req.params.designName}.config.json`);
    animData = File.loadJSON(`./designs/${req.params.designName}.json`);
  }
  catch (err) {
    console.log(err);
    res.status(404).send('Design does not exist');
  }

  try {
    Configure.setLayers(req.query, config, animData);
    Render.renderAnimationData(animData, function(outPath, success) {
      if (success) {
        res.sendFile(outPath, {}, function(err) {
          if (err) {
            res.sendStatus(500);
          }
          else {
            fs.unlink(outPath, (err) => { if (err) throw err; });
          }
        });
      }
      else {
        res.sendStatus(500);
      }
    });
  }
  catch(err) {
    console.log(err);
    res.sendStatus(400);
    return;
  }
});

app.listen(port, () => console.log(`Warhol listening on port ${port}!`));
