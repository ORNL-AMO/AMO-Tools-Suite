const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'fan'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('fan test', function (t) {
    t.plan(1);
    t.type(bindings.fanPlaceholder, 'function');
    var inp = {
        fanSpeed: 1191,
        motorSpeed: 1191,
        fanSpeedCorrected: 1170,
        densityCorrected: 0.05,
        pressureBarometricCorrected: 26.28,
        FanInletFlange: {
            width: 143.63,
            length: 32.63,
            tdx: 123,
            pbx: 26.57,
            noInletBoxes: 2
        },
        FanEvaseOrOutletFlange: {
            width: 70,
            length: 78,
            tdx: 132.7,
            pbx: 26.57
            // noInletBoxes isn't necessary, will default to 1
        },
        FlowTraverse: {
            width: 143.63,
            length: 32.63,
            tdx: 123,
            pbx: 26.57,
            psx: -18.1,
            pitotTubeCoefficient: 0.87292611371180784,
            traverseData: [
                [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
                [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
                [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
            ]
        }
    };

    // FlowTraverse flowTraverse(143.63, 32.63, 123.0, 26.57, -18.1, std::sqrt(0.762), traverseHoleData);

    // FlowTraverse(double length, double width, double tdx, double pbx, double psx, double pitotTubeCoefficient,
    // std::vector< std::vector< double > > & traverseHoleData, unsigned noInletBoxes = 1);

    var res = bindings.fanPlaceholder(inp);
    // t.equal(rnd(res.totalChemicalEnergyInput), rnd(0));
});