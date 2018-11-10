const express = require('express');
const app = express();
const port = 8080;

app.get('/', function (req, res) {
  res.send('Hello stranger!');
  console.log('Got request');
});

app.listen(port, () => console.log(`Warhol listening on port ${port}!`));