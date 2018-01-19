const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'fan'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('fan test', function (t) {
    t.plan(2);
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
        },
        AddlTraversePlanes: [
            {
                width: 143.63,
                length: 32.63,
                tdx: 123,
                pbx: 26.57,
                psx: -17.0,
                pitotTubeCoefficient: 0.87292611371180784,
                traverseData: [
                    [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
                    [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
                    [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
                ]
            }
        ],
        InletMstPlane: {
            width: 143.63,
            length: 32.63,
            tdx: 123,
            pbx: 26.57,
            psx: -17.55,
            noInletBoxes: 2
        },
        OutletMstPlane: {
            width: 143.63,
            length: 32.63,
            tdx: 123,
            pbx: 26.57,
            psx: 1.8
            // noInletBoxes not provided here.. defaults to 1
        }
    };

    var res = bindings.fanPlaceholder(inp);

    var whatHappened = 0;
    // t.equal(rnd(res.totalChemicalEnergyInput), rnd(0));
    t.equal(res.addlTravPlanesSize, 1);
});