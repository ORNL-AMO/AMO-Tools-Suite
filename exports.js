// const testRoot = require('path').resolve(__dirname, '../')
//     , bindings = require('bindings')({ module_root: testRoot, bindings: 'db'});
//
// module.exports.db = bindings;
// console.log(module.exports.db);

// const testRoot = require('path').resolve(__dirname, '../')
//     , bindings = require('bindings')({ module_root: testRoot, bindings: 'db'});

const db = require('./build/Release/db.node');
module.exports.db = db;
console.log(module.exports.db);


// const psat = require('bindings')({ module_root: testRoot, bindings: 'psat'});
// const phast = require('bindings')({ module_root: testRoot, bindings: 'phast'});
// const ssmt = require('bindings')({ module_root: testRoot, bindings: 'ssmt'});
// const standalone = require('bindings')({ module_root: testRoot, bindings: 'standalone'});


// var dbNode = require('../build/Release/db.node');
// module.exports.db = dbNode;


// var db = require('../build/Release/db.node');
// module.exports.db = db;
// console.log(module.exports.db);

// module.exports.psat = psat;
// module.exports.phast = phast;
// module.exports.ssmt = ssmt;
// module.exports.standalone = standalone;
