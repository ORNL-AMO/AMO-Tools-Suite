const express = require('express')
const app = express()
const port = 3000
const path = require('path');

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname + '/wasm-express.html'));
});
app.use('/assets', express.static('bin'));
app.use('/tests', express.static('tests/wasm/psat/'));
app.use('/tests', express.static('tests/wasm/motor/'));
app.use('/tests', express.static('tests/wasm/fan/'));
app.use('/tests', express.static('tests/wasm/test-helpers/'));
app.use('/jquery', express.static('node_modules/jquery/dist/'));
app.use('/assert', express.static('node_modules/assert-plus'));

app.listen(port, () => console.log(`Wasm Testing Served on: localhost:${port}`));