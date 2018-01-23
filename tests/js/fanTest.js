const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'fan'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('fan test', function (t) {
    t.plan(4);
    t.type(bindings.fanPlaceholder, 'function');
    var inp = {
        FanRatedInfo: {
            fanSpeed: 1191,
            motorSpeed: 1191,
            fanSpeedCorrected: 1170,
            densityCorrected: 0.05,
            pressureBarometricCorrected: 26.28
        },
        PlaneData: {
            plane5upstreamOfPlane2: true,
            totalPressureLossBtwnPlanes1and4: 0,
            totalPressureLossBtwnPlanes2and5: 0.627,
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
                width: 55.42,
                length: 60.49,
                tdx: 132.7,
                pbx: 26.57,
                psx: 1.8
                // noInletBoxes not provided here.. defaults to 1
            }
        },
        BaseGasDensity: {
            dryBulbTemp: 123,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasDensity: 0.0547,
            gasType: 'AIR'
        },
        FanShaftPower: {
            isMethodOne: false,
            voltage: 4200,
            amps: 205,
            powerFactorAtLoad: 0.88,
            efficiencyMotor: 95,
            efficiencyVFD: 100,
            efficiencyBelt: 100,
            sumSEF: 0
        }
    };

    var res = bindings.fanPlaceholder(inp);

    t.equal(rnd(res.fanEfficiencyTp), rnd(53.60738684355601));
    t.equal(rnd(res.fanEfficiencySp), rnd(49.20691409764023));
    t.equal(rnd(res.fanEfficiencySpr), rnd(50.768875240824116));
});

test('fan curve test', function (t) {
    t.plan(61);
    t.type(bindings.fanCurve, 'function');
    var inp = {
        density: 0.0308, densityCorrected: 0.0332, speed: 1180, speedCorrected: 1187,
        pressureBarometric: 29.36, pressureBarometricCorrected: 29.36, pt1Factor: -0.93736,
        gamma: 1.4, gammaCorrected: 1.4, area1: 34, area2: 12.7, curveType: 'FanStaticPressure',
        BaseCurveData: [
            [0, 22.3, 115],
            [14410, 22.5, 154],
            [28820, 22.3, 194],
            [43230, 21.8, 241],
            [57640, 21.2, 293],
            [72050, 20.3, 349],
            [86460, 19.3, 406],
            [100871, 18, 462],
            [115281, 16.5, 515],
            [129691, 14.8, 566],
            [144101, 12.7, 615],
            [158511, 10.2, 667],
            [172921, 7.3, 725],
            [187331, 3.7, 789],
            [201741, -0.8, 861]
        ]
    };

    var res = bindings.fanCurve(inp);

    var expected = [
        [0, 24.3237008519,  126.1802380783, 0],
        [14500.8543591511,  24.5509446301, 169.0344096605, 0.3296327776],
        [29026.8029521096,  24.3537683159, 213.1237007012, 0.5140168074],
        [43549.7454585634,  23.8129367203, 264.8147787583, 0.6053657684],
        [58070.0734274583,  23.1590288007, 321.9740080602, 0.6451968788],
        [72585.9393038736,  22.1753576429, 383.5029716631, 0.6484847133],
        [87098.9706713126,  21.0819694298, 446.1168381298, 0.6362806595],
        [101607.8897959761, 19.6602795889, 507.6073147301, 0.6089335382],
        [116111.3789740286, 18.0200947791, 565.7819229037, 0.5728692768],
        [130609.5615402702, 16.1615468983, 621.7364859870, 0.5266325641],
        [145098.2298738518, 13.8661188861, 675.4528304721, 0.4628825027],
        [159574.7652742440, 11.1342523247, 732.4119689902, 0.3778769228],
        [174035.6935709888, 7.96653610850, 795.8906212688, 0.2721540841],
        [188477.2686633575, 4.03652020770, 865.8668678138, 0.1378022756],
        [202889.8046137204, -0.8723928962, 944.4826765914, -0.029540604]
    ];

    function testEq(results, expected) {
        for (var i = 0; i < results.length; i++) {
            for (var j = 0; j < results[i].length; j++) {
                t.equal(rnd(results[i][j]), rnd(expected[i][j]));
            }
        }
    }

    testEq(res.ResultData, expected);


});
