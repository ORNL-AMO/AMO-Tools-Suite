var request = require('request');

request.get({url: 'http://localhost:3000/stop'}, (error, response, body) => console.log(body));