const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'fan'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('fansExisting', function (t) {
    t.plan(12);

    var input = {
        "fanSpeed": 1180, "drive": 0, "lineFrequency": 0, "motorRatedPower": 600, "motorRpm": 1180,
        "efficiencyClass": 1, "specifiedEfficiency": 100, "motorRatedVoltage": 460, "fullLoadAmps": 683.2505707137,
        "sizeMargin": 1, "measuredPower": 460, "measuredVoltage": 460, "measuredAmps": 660, "flowRate": 129691,
        "inletPressure": -16.36, "outletPressure": 1.1, "compressibilityFactor": 0.988, "loadEstimationMethod": 0,
        "operatingFraction": 1.0, "unitCost": 0.06, "airDensity": 1.02
    };

    var output = bindings.fanResultsExisting(input);

    t.equal(rnd(output.fanEfficiency), rnd(59.5398315));
    t.equal(rnd(output.motorRatedPower), rnd(600.0));
    t.equal(rnd(output.motorShaftPower), rnd(590.622186263));
    t.equal(rnd(output.fanShaftPower), rnd(590.622186263));
    t.equal(rnd(output.motorEfficiency), rnd(95.78351108));
    t.equal(rnd(output.motorPowerFactor), rnd(85.77466651));
    t.equal(rnd(output.motorCurrent), rnd(673.1011529439));
    t.equal(rnd(output.motorPower), rnd(460.0));
    t.equal(rnd(output.annualEnergy), rnd(4029.6));
    t.equal(rnd(output.annualCost), rnd(241.776));
    t.equal(rnd(output.estimatedFLA), rnd(683.2505707137));
    t.equal(rnd(output.fanEnergyIndex), rnd(1.247872));
});

test('fansModified', function (t) {
    t.plan(11);

    var input = {
        "fanSpeed": 1180, "drive": 0, "lineFrequency": 0, "motorRatedPower": 600, "motorRpm": 1180,
        "efficiencyClass": 1, "specifiedEfficiency": 100, "motorRatedVoltage": 460, "fullLoadAmps": 683.2505707137,
        "sizeMargin": 1, "measuredVoltage": 460, "measuredAmps": 660, "flowRate": 129691,
        "inletPressure": -16.36, "outletPressure": 1.1, "compressibilityFactor": 0.988,
        "operatingFraction": 1.0, "unitCost": 0.06, "airDensity": 1.02, "fanEfficiency": 59.5398315, "isSpecified": false,
    };

    var output = bindings.fanResultsModified(input);

    t.equal(rnd(output.fanEfficiency), rnd(59.5398315));
    t.equal(rnd(output.motorRatedPower), rnd(600.0));
    t.equal(rnd(output.motorShaftPower), rnd(590.622186263));
    t.equal(rnd(output.fanShaftPower), rnd(590.622186263));
    t.equal(rnd(output.motorEfficiency), rnd(95.783511));
    t.equal(rnd(output.motorPowerFactor), rnd(85.774801));
    t.equal(rnd(output.motorCurrent), rnd(673.100309));
    t.equal(rnd(output.motorPower), rnd(460.000144));
    t.equal(rnd(output.annualEnergy), rnd(4029.601262));
    t.equal(rnd(output.annualCost), rnd(241.776076));
    t.equal(rnd(output.fanEnergyIndex), rnd(1.247872));
});

test('fansOptimal', function (t) {
    t.plan(11);

    var input = {
        "fanSpeed": 1180, "drive": 0, "lineFrequency": 0, "motorRatedPower": 500, "motorRpm": 1180,
        "efficiencyClass": 1, "specifiedEfficiency": 100, "motorRatedVoltage": 460, "fullLoadAmps": 683.2505707137,
        "sizeMargin": 1, "measuredVoltage": 460, "measuredAmps": 660, "flowRate": 129691,
        "inletPressure": -16.36, "outletPressure": 1.1, "compressibilityFactor": 0.988,
        "operatingFraction": 1.0, "unitCost": 0.06, "airDensity": 0.07024, "fanType": 0, "isSpecified": false
    };

    var output = bindings.fanResultsOptimal(input);

    t.equal(rnd(output.fanEfficiency), rnd(75.657845));
    t.equal(rnd(output.motorRatedPower), rnd(500.0));
    t.equal(rnd(output.motorShaftPower), rnd(464.7970806678));
    t.equal(rnd(output.fanShaftPower), rnd(464.7970806678));
    t.equal(rnd(output.motorEfficiency), rnd(95.99974605));
    t.equal(rnd(output.motorPowerFactor), rnd(85.427246));
    t.equal(rnd(output.motorCurrent), rnd(530.661126));
    t.equal(rnd(output.motorPower), rnd(361.187025));
    t.equal(rnd(output.annualEnergy), rnd(3163.998343));
    t.equal(rnd(output.annualCost), rnd(189.839901));
    t.equal(rnd(output.fanEnergyIndex), rnd(1.237779));
});

test('fansOptimal specified ', function (t) {
    t.plan(11);

    var input = {
        "fanSpeed": 1180, "drive": 0, "lineFrequency": 0, "motorRatedPower": 500, "motorRpm": 1180,
        "efficiencyClass": 1, "specifiedEfficiency": 100, "motorRatedVoltage": 460, "fullLoadAmps": 683.2505707137,
        "sizeMargin": 1, "measuredVoltage": 460, "measuredAmps": 660, "flowRate": 129691,
        "inletPressure": -16.36, "outletPressure": 1.1, "compressibilityFactor": 0.988,
        "operatingFraction": 1.0, "unitCost": 0.06, "airDensity": 0.07024, "fanType": 0, "isSpecified": true, "userInputFanEfficiency": 75.65784493
    };

    var output = bindings.fanResultsOptimal(input);

    t.equal(rnd(output.fanEfficiency), rnd(75.657845));
    t.equal(rnd(output.motorRatedPower), rnd(500.0));
    t.equal(rnd(output.motorShaftPower), rnd(464.7970806678));
    t.equal(rnd(output.fanShaftPower), rnd(464.7970806678));
    t.equal(rnd(output.motorEfficiency), rnd(95.99974605));
    t.equal(rnd(output.motorPowerFactor), rnd(85.427246));
    t.equal(rnd(output.motorCurrent), rnd(530.661126));
    t.equal(rnd(output.motorPower), rnd(361.187025));
    t.equal(rnd(output.annualEnergy), rnd(3163.998343));
    t.equal(rnd(output.annualCost), rnd(189.839901));
    t.equal(rnd(output.fanEnergyIndex), rnd(1.237779));
});

test('fan203 test', function (t) {
    t.plan(16);
    t.type(bindings.fan203, 'function');

    var area = 143.63 * 32.63 / 144.0;
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
                area: area * 2,
                length: 32.63,
                dryBulbTemp: 123,
                barometricPressure: 26.57
            },
            FanEvaseOrOutletFlange: {
                area: 70 * 78 / 144.0,
                dryBulbTemp: 132.7,
                barometricPressure: 26.57
            },
            FlowTraverse: {
                area: area,
                dryBulbTemp: 123,
                barometricPressure: 26.57,
                staticPressure: -18.1,
                pitotTubeCoefficient: 0.87292611371180784,
                traverseData: [
                    [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
                    [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
                    [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
                ]
            },
            AddlTraversePlanes: [
                {
                    area: area,
                    dryBulbTemp: 123,
                    barometricPressure: 26.57,
                    staticPressure: -17.0,
                    pitotTubeCoefficient: 0.87292611371180784,
                    traverseData: [
                        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
                        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
                        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
                    ]
                }
            ],
            InletMstPlane: {
                area: area * 2,
                dryBulbTemp: 123,
                barometricPressure: 26.57,
                staticPressure: -17.55
            },
            OutletMstPlane: {
                area: (55.42 * 60.49) / 144.0,
                dryBulbTemp: 132.7,
                barometricPressure: 26.57,
                staticPressure: 1.8
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
            motorShaftPower: (4200 * 205 * 0.88 * Math.sqrt(3)) / 746.0,
            efficiencyMotor: 95,
            efficiencyVFD: 100,
            efficiencyBelt: 100,
            sumSEF: 0
        }
    };

    var res = bindings.fan203(inp);

    t.equal(rnd(res.fanEfficiencyTotalPressure), rnd(53.60738684355601));
    t.equal(rnd(res.fanEfficiencyStaticPressure), rnd(49.20691409764023));
    t.equal(rnd(res.fanEfficiencyStaticPressureRise), rnd(50.768875240824116));

    t.equal(rnd(res.flow), rnd(250332.6394178045));
    t.equal(rnd(res.kpc), rnd(0.9982905074));
    t.equal(rnd(res.power), rnd(1671.2107816151));
    t.equal(rnd(res.pressureStatic), rnd(21.2207447999));
    t.equal(rnd(res.pressureTotal), rnd(23.1184721997));
    t.equal(rnd(res.staticPressureRise), rnd(21.8943488943));

    t.equal(rnd(res.flowCorrected), rnd(245498.3175715673));
    t.equal(rnd(res.kpcCorrected), rnd(0.986542913));
    t.equal(rnd(res.powerCorrected), rnd(1445.5400545013));
    t.equal(rnd(res.pressureStaticCorrected), rnd(18.6846696404));
    t.equal(rnd(res.pressureTotalCorrected), rnd(20.355601074));
    t.equal(rnd(res.staticPressureRiseCorrected), rnd(19.277771819));
});

test('getBaseGasDensity', function (t) {
    t.plan(6);
    t.type(bindings.getBaseGasDensityRelativeHumidity, 'function');
    t.type(bindings.getBaseGasDensityDewPoint, 'function');
    t.type(bindings.getBaseGasDensityWetBulb, 'function');

    var inp = {
        dryBulbTemp: 123,
        staticPressure: -17.6,
        barometricPressure: 26.57,
        gasDensity: 0.0547,
        gasType: 'AIR',
        inputType: 'relativeHumidity',
        relativeHumidity: 0.35,
        specificGravity: 1.05
    };

    var res = bindings.getBaseGasDensityRelativeHumidity(inp);
    t.equal(rnd(res), rnd(0.06231117736966));

    inp = {
        dryBulbTemp: 123,
        staticPressure: -17.6,
        barometricPressure: 26.57,
        gasDensity: 0.0547,
        gasType: 'AIR',
        inputType: 'dewPoint',
        dewPoint: 0.35,
        specificGravity: 1.05
    };

    res = bindings.getBaseGasDensityDewPoint(inp);
    t.equal(rnd(res), rnd(0.06551801779516826));

    inp = {
        dryBulbTemp: 123,
        staticPressure: -17.6,
        barometricPressure: 26.57,
        gasDensity: 0.0547,
        gasType: 'AIR',
        inputType: 'wetBulb',
        wetBulbTemp: 110,
        specificGravity: 1.05,
        specificHeatGas: 1.03
    };

    res = bindings.getBaseGasDensityWetBulb(inp);
    t.equal(rnd(res), rnd(0.065456));
});

test('getVelocityPressureData', function (t) {
    t.plan(5);
    t.type(bindings.getVelocityPressureData, 'function');

    var inp = {
        area: 143.63 * 32.63 / 144.0,
        dryBulbTemp: 123,
        barometricPressure: 26.57,
        staticPressure: -18.1,
        pitotTubeCoefficient: 0.87292611371180784,
        traverseData: [
            [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
            [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
            [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
        ]
    };

    var res = bindings.getVelocityPressureData(inp);

    t.equal(rnd(res.pv3), rnd(0.7508102988157324));
    t.equal(rnd(res.percent75Rule), rnd(100));

    inp = {
        area: 143.63 * 32.63 / 144.0,
        dryBulbTemp: 123,
        barometricPressure: 26.57,
        staticPressure: -17.0,
        pitotTubeCoefficient: 0.87292611371180784,
        traverseData: [
            [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
            [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
            [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
        ]
    };

    res = bindings.getVelocityPressureData(inp);
    t.equal(rnd(res.pv3), rnd(0.6007));
    t.equal(rnd(res.percent75Rule), rnd(100));
});

test('getPlaneResults', function (t) {
    t.plan(38);
    t.type(bindings.getPlaneResults, 'function');

    var area = 143.63 * 32.63 / 144.0;

    inp = {
        PlaneData: {
            plane5upstreamOfPlane2: true,
            totalPressureLossBtwnPlanes1and4: 0,
            totalPressureLossBtwnPlanes2and5: 0.627,
            FanInletFlange: {
                area: area * 2,
                length: 32.63,
                dryBulbTemp: 123,
                barometricPressure: 26.57
            },
            FanEvaseOrOutletFlange: {
                area: 70 * 78 / 144.0,
                dryBulbTemp: 132.7,
                barometricPressure: 26.57
            },
            FlowTraverse: {
                area: area,
                dryBulbTemp: 123,
                barometricPressure: 26.57,
                staticPressure: -18.1,
                pitotTubeCoefficient: 0.87292611371180784,
                traverseData: [
                    [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
                    [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
                    [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
                ]
            },
            AddlTraversePlanes: [
                {
                    area: area,
                    dryBulbTemp: 123,
                    barometricPressure: 26.57,
                    staticPressure: -17.0,
                    pitotTubeCoefficient: 0.87292611371180784,
                    traverseData: [
                        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
                        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
                        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
                    ]
                },
                {
                    area: area,
                    dryBulbTemp: 124,
                    barometricPressure: 26.57,
                    staticPressure: -16.5,
                    pitotTubeCoefficient: 0.872,
                    traverseData: [
                        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
                        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
                        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
                    ]
                }
            ],
            InletMstPlane: {
                area: area * 2,
                dryBulbTemp: 123,
                barometricPressure: 26.57,
                staticPressure: -17.55
            },
            OutletMstPlane: {
                area: (55.42 * 60.49) / 144.0,
                dryBulbTemp: 132.7,
                barometricPressure: 26.57,
                staticPressure: 1.8
            }
        },
        BaseGasDensity: {
            dryBulbTemp: 123,
            staticPressure: -17.6,
            barometricPressure: 26.57,
            gasDensity: 0.0547,
            gasType: 'AIR'
        }
    };


    var res = bindings.getPlaneResults(inp);
    function testEq(results, expected, isStaticPressure) {
        t.equal(rnd(results.gasDensity), rnd(expected.gasDensity));
        t.equal(rnd(results.gasVolumeFlowRate), rnd(expected.gasVolumeFlowRate));
        t.equal(rnd(results.gasVelocity), rnd(expected.gasVelocity));
        t.equal(rnd(results.gasVelocityPressure), rnd(expected.gasVelocityPressure));
        t.equal(rnd(results.gasTotalPressure), rnd(expected.gasTotalPressure));
        if (isStaticPressure) {
            t.equal(rnd(results.staticPressure), rnd(expected.staticPressure));
        }
    }

    testEq(res.FanInletFlange, {
        "gasDensity": 0.054707937910736096,
        "gasVolumeFlowRate": 368484.70105160266,
        "gasVelocity": 5660.955271820326,
        "gasVelocityPressure": 1.4595154074095142,
        "gasTotalPressure": -16.090484592590485,
        "staticPressure": -17.55
    }, true);
    testEq(res.FanOrEvaseOutletFlange, {
        "gasDensity": 0.05781581992717993,
        "gasVolumeFlowRate": 348742.34384798247,
        "gasVelocity": 9197.600277309428,
        "gasVelocityPressure": 4.070924792774011,
        "gasTotalPressure": 12.156298668206892,
        "staticPressure": 8.085373875432882
    }, true);
    testEq(res.FlowTraverse, {
        "gasDensity": 0.0546206208926391,
        "gasVolumeFlowRate": 132250.42933608184,
        "gasVelocity": 4063.47271956754,
        "gasVelocityPressure": 0,
        "gasTotalPressure": 0
    }, false);
    testEq(res.InletMstPlane, {
        "gasDensity": 0.054707937910736096,
        "gasVolumeFlowRate": 368484.70105160266,
        "gasVelocity": 5660.955271820326,
        "gasVelocityPressure": 1.4595154074095142,
        "gasTotalPressure": -16.090484592590485
    }, false);
    testEq(res.OutletMstPlane, {
        "gasDensity": 0.05683429586662124,
        "gasVolumeFlowRate": 354698.4763125503,
        "gasVelocity": 15236.026136905648,
        "gasVelocityPressure": 10.983298668206892,
        "gasTotalPressure": 12.783298668206893
    }, false);
    var trav = [
        {
            "gasDensity": 0.054795254928833075,
            "gasVolumeFlowRate": 118104.78734062292,
            "gasVelocity": 3628.839496538495,
            "gasVelocityPressure": 0,
            "gasTotalPressure": 0
        },
        {
            "gasDensity": 0.054780670621748434,
            "gasVolumeFlowRate": 117995.19024728928,
            "gasVelocity": 3625.472060975973,
            "gasVelocityPressure": 0,
            "gasTotalPressure": 0
        }
    ];
    for (var i = 0; i < res.AddlTraversePlanes.length; i++) {
        testEq(res.AddlTraversePlanes[i], trav[i], false);
    }

});

test('fan curve test', function (t) {
    t.plan(121);
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

    var density = 0.0308, speed = 1180, speedCorrected = 1187;
    inp = {
        density: density, densityCorrected: 0.0332, speed: speed, speedCorrected: speedCorrected,
        pressureBarometric: 29.36, pressureBarometricCorrected: 29.36, pt1Factor: -0.93736,
        gamma: 1.4, gammaCorrected: 1.4, area1: 34, area2: 12.7, curveType: 'FanStaticPressure',
        RatedPointCurveData: [
            [0, 22.3, 115, density, speed, speedCorrected],
            [14410, 22.5, 154, density, speed, speedCorrected],
            [28820, 22.3, 194, density, speed, speedCorrected],
            [43230, 21.8, 241, density, speed, speedCorrected],
            [57640, 21.2, 293, density, speed, speedCorrected],
            [72050, 20.3, 349, density, speed, speedCorrected],
            [86460, 19.3, 406, density, speed, speedCorrected],
            [100871, 18, 462, density, speed, speedCorrected],
            [115281, 16.5, 515, density, speed, speedCorrected],
            [129691, 14.8, 566, density, speed, speedCorrected],
            [144101, 12.7, 615, density, speed, speedCorrected],
            [158511, 10.2, 667, density, speed, speedCorrected],
            [172921, 7.3, 725, density, speed, speedCorrected],
            [187331, 3.7, 789, density, speed, speedCorrected],
            [201741, -0.8, 861, density, speed, speedCorrected]
        ]
    };

    res = bindings.fanCurve(inp);
    testEq(res.ResultData, expected);
});

test('optimalFanEfficiency', function (t) {
    t.plan(4);
    t.type(bindings.optimalFanEfficiency, 'function');

    var input = {
        fanType: 0,
        fanSpeed: 1180,
        flowRate: 40000,
        inletPressure: -9,
        outletPressure: 1,
        compressibility: 0.995
    };

    var efficiency = bindings.optimalFanEfficiency(input);
    t.equal(rnd(efficiency), rnd(80.56103029));

    input = {
        fanType: 11,
        fanSpeed: 1180,
        flowRate: 10000,
        inletPressure: -9,
        outletPressure: 1,
        compressibility: 0.995
    };
    efficiency = bindings.optimalFanEfficiency(input);
    t.equal(rnd(efficiency), rnd(60.6953126));

    input = {
        fanType: 6,
        fanSpeed: 1180,
        flowRate: 500000,
        inletPressure: -6,
        outletPressure: 1,
        compressibility: 0.995
    };
    efficiency = bindings.optimalFanEfficiency(input);
    t.equal(rnd(efficiency), rnd(29.31237501));
});

test('compressibilityFactor', function (t) {
    t.plan(4);
    t.type(bindings.compressibilityFactor, 'function');

    var input = {
        moverShaftPower: 300, inletPressure: -8.5, outletPressure: 3,
        barometricPressure: 29, flowRate: 1000, specificHeatRatio: 1.4
    };

    var compressibilityFactor = bindings.compressibilityFactor(input);
    t.equal(rnd(compressibilityFactor), rnd(1.5795535958));

    input = {
        moverShaftPower: 566, inletPressure: -16.36, outletPressure: 1.1,
        barometricPressure: 29.36, flowRate: 129691, specificHeatRatio: 1.4
    };
    compressibilityFactor = bindings.compressibilityFactor(input);

    t.equal(rnd(compressibilityFactor), rnd(0.9879934727));

    input = {
        moverShaftPower: 623, inletPressure: -8.92, outletPressure: 2.28,
        barometricPressure: 29.36, flowRate: 151961, specificHeatRatio: 1.4
    };
    compressibilityFactor = bindings.compressibilityFactor(input);
    t.equal(rnd(compressibilityFactor), rnd(0.9953146218));
});
