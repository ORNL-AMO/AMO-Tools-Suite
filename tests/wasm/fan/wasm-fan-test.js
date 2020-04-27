function returnDoubleVector(doublesArray)
{
    let doubleVector = new Module.DoubleVector();

    for (x of doublesArray)
    {
        doubleVector.push_back(x);
    }

    return doubleVector;
}

function returnBaseCurveData(flow, pressure, power)
{
    let baseCurveData = new Module.FanCurveDataBaseCurve(flow, pressure, power);

    return baseCurveData;
}
function returnBaseCurveVector(baseCurveData)
{
    let baseCurveVector = new Module.BaseCurveVector();

    for (x of baseCurveData) // each row of baseCurveData should have three columns
    {
        baseCurveVector.push_back(returnBaseCurveData(x[0], x[1], x[2]));
    }

    return baseCurveVector;
}

function returnRatedPointData(flow, pressure, power, density, speed, speedCorrected)
{
    let ratedPointData = new Module.FanCurveDataRatedPoint(flow, pressure, power, density, speed, speedCorrected);

    return ratedPointData;
}
function returnRatedPointVector(ratedPointData)
{
    let ratedPointVector = new Module.RatedPointVector();

    for (x of ratedPointData) // each row of ratedPointData should have six columns
    {
        ratedPointVector.push_back(returnRatedPointData(x[0], x[1], x[2], x[3], x[4], x[5]));
    }

    return ratedPointVector;
}

function returnBaseOperatingPointData(flow, pressure, power, density, speed, speedCorrected, pressureBarometric, usePt1Factor, pt1)
{
    let baseOperatingPointData = new Module.FanCurveDataBaseOperatingPoint(flow, pressure, power, density, speed, speedCorrected, pressureBarometric, usePt1Factor, pt1);

    return baseOperatingPointData;
}
function returnRatedPointVector(baseOperatingPointData)
{
    let baseOperatingPointVector = new Module.BaseOperatingPointVector();

    for (x of baseOperatingPointData) // each row of baseOperatingPointData should have nine columns
    {
        baseOperatingPointVector.push_back(returnBaseOperatingPointData(x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8]));
    }

    return baseOperatingPointVector;
}


function resultsExisting() {
    let fanSpeed = 1180;
    let drive = Module.Drive.DIRECT_DRIVE;
    let lineFrequency = Module.LineFrequency.FREQ60;
    let motorRatedPower = 600;
    let motorRpm = 1180;
    let efficiencyClass = Module.MotorEfficiencyClass.ENERGY_EFFICIENT;
    let specifiedEfficiency = 100;
    let motorRatedVoltage = 460;
    let fullLoadAmps = 683.2505707137;
    let sizeMargin = 1;
    let measuredPower = 460;
    let measuredVoltage = 460;
    let measuredAmps = 660;
    let flowRate = 129691;
    let inletPressure = -16.36;
    let outletPressure = 1.1;
    let compressibilityFactor = .988;
    let loadEstimationMethod = Module.LoadEstimationMethod.POWER;
    let operatingHours = 8760;
    let unitCost = .06;
    let airDensity = 1.02;
    //unused
    let specifiedDriveEfficiency = 1;

    let fanInput = new Module.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
    let motor = new Module.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
    let baselineFieldData = new Module.FieldDataBaseline(measuredPower, measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor, loadEstimationMethod);
    let fanResult = new Module.FanResult(fanInput, motor, operatingHours, unitCost);
    let output = fanResult.calculateExisting(baselineFieldData);
    fanInput.delete();
    motor.delete();
    baselineFieldData.delete();
    fanResult.delete();
    //perform conversions for return object
    output.fanEfficiency = output.fanEfficiency * 100;
    output.motorEfficiency = output.motorEfficiency * 100;
    output.motorPowerFactor = output.motorPowerFactor * 100;
    output.driveEfficiency = output.driveEfficiency * 100;

    testNumberValue(output.fanEfficiency, 59.5398315, "Fan Results Existing (fanEfficiency)");
    testNumberValue(output.motorRatedPower, 600.0, "Fan Results Existing (motorRatedPower)");
    testNumberValue(output.motorShaftPower, 590.622186263, "Fan Results Existing (motorShaftPower)");
    testNumberValue(output.fanShaftPower, 590.622186263, "Fan Results Existing (fanShaftPower)");
    testNumberValue(output.motorEfficiency, 95.78351108, "Fan Results Existing (motorEfficiency)");
    testNumberValue(output.motorPowerFactor, 85.77466651, "Fan Results Existing (motorPowerFactor)");
    testNumberValue(output.motorCurrent, 673.1011529439, "Fan Results Existing (motorCurrent)");
    testNumberValue(output.motorPower, 460.0, "Fan Results Existing (motorPower)");
    testNumberValue(output.annualEnergy, 4029.6, "Fan Results Existing (annualEnergy)");
    testNumberValue(output.annualCost, 241.776, "Fan Results Existing (annualCost)");
    testNumberValue(output.estimatedFLA, 683.2505707137, "Fan Results Existing (estimatedFLA)");
    testNumberValue(output.fanEnergyIndex, 1.247872, "Fan Results Existing (fanEnergyIndex)");
}

function resultsModified() {
    let fanSpeed = 1180;
    let drive = Module.Drive.DIRECT_DRIVE;
    let lineFrequency = Module.LineFrequency.FREQ60;
    let motorRatedPower = 600;
    let motorRpm = 1180;
    let efficiencyClass = Module.MotorEfficiencyClass.ENERGY_EFFICIENT;
    let specifiedEfficiency = 100 / 100;
    let motorRatedVoltage = 460;
    let fullLoadAmps = 683.2505707137;
    let sizeMargin = 1;
    let measuredVoltage = 460;
    let measuredAmps = 660;
    let flowRate = 129691;
    let inletPressure = -16.36;
    let outletPressure = 1.1;
    let compressibilityFactor = .988;
    let operatingHours = 8760;
    let unitCost = .06;
    let airDensity = 1.02;
    let fanEfficiency = 59.5398315 / 100;
    let specifiedDriveEfficiency = 100 / 100;
    let isSpecified = false;
    //calculate
    let fanInput = new Module.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
    let fanFieldData = new Module.FieldDataModified(measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor)
    let motor = new Module.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
    let fanResult = new Module.FanResult(fanInput, motor, operatingHours, unitCost);
    output = fanResult.calculateModified(fanFieldData, fanEfficiency);
    fanInput.delete();
    fanFieldData.delete();
    motor.delete();
    fanResult.delete();
    //convert output
    output.fanEfficiency = output.fanEfficiency * 100;
    output.motorEfficiency = output.motorEfficiency * 100;
    output.motorPowerFactor = output.motorPowerFactor * 100;
    output.driveEfficiency = output.driveEfficiency * 100;
    testNumberValue(output.fanEfficiency, 59.5398315, "Fan Results Modified (fanEfficiency)");
    testNumberValue(output.motorRatedPower, 600.0, "Fan Results Modified (motorRatedPower)");
    testNumberValue(output.motorShaftPower, 590.622186263, "Fan Results Modified (motorShaftPower)");
    testNumberValue(output.fanShaftPower, 590.622186263, "Fan Results Modified (fanShaftPower)");
    testNumberValue(output.motorEfficiency, 95.783511, "Fan Results Modified (motorEfficiency)");
    testNumberValue(output.motorPowerFactor, 85.774801, "Fan Results Modified (motorPowerFactor)");
    testNumberValue(output.motorCurrent, 673.100309, "Fan Results Modified (motorCurrent)");
    testNumberValue(output.motorPower, 460.000144, "Fan Results Modified (motorPower)");
    testNumberValue(output.annualEnergy, 4029.601262, "Fan Results Modified (annualEnergy)");
    testNumberValue(output.annualCost, 241.776076, "Fan Results Modified (annualCost)");
    testNumberValue(output.fanEnergyIndex, 1.247872, "Fan Results Modified (fanEnergyIndex)");
}

function getBaseGasDensity() {
    let dryBulbTemp = 123;
    let staticPressure = -17.6;
    let barometricPressure = 26.57;
    let gasType = Module.GasType.AIR;
    let inputType = Module.BaseGasDensityInputType.RelativeHumidity;
    let relativeHumidity = 35;
    let specificGravity = 1.05;

    let relativeHumidityInstance = new Module.BaseGasDensity(dryBulbTemp, staticPressure, barometricPressure, relativeHumidity, gasType, inputType, specificGravity);
    let relativeHumidityResult = relativeHumidityInstance.getGasDensity();
    relativeHumidityInstance.delete();
    testNumberValue(relativeHumidityResult, 0.06231117736966, "Gas Density (relativeHumidity)");

    inputType = Module.BaseGasDensityInputType.DewPoint;
    dewPoint = 0.35;

    let dewPointInstance = new Module.BaseGasDensity(dryBulbTemp, staticPressure, barometricPressure, dewPoint, gasType, inputType, specificGravity);
    let dewPointResult = dewPointInstance.getGasDensity();
    dewPointInstance.delete();
    testNumberValue(dewPointResult, 0.06551801779516826, "Gas Density (dewPoint)");

    inputType = Module.BaseGasDensityInputType.WetBulbTemp;
    let wetBulbTemp = 110;
    let specificHeatGas = 1.03;

    let wetBulbInstance = new Module.BaseGasDensity(dryBulbTemp, staticPressure, barometricPressure, wetBulbTemp, gasType, inputType, specificGravity, specificHeatGas);
    let wetBulbResult = wetBulbInstance.getGasDensity();
    wetBulbInstance.delete();
    testNumberValue(wetBulbResult, 0.065456, "Gas Density (wetBulb)");
}

function getVelocityPressureData()
{
    let area = 143.63 * 32.63 / 144.0;
    let dryBulbTemp = 123;
    let barometricPressure = 26.57;
    let staticPressure = -18.1;
    let pitotTubeCoefficient = 0.87292611371180784;
    let traversePlaneTraverseData = new Module.DoubleVector2D();
    let traverseData = [
        [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
        [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
        [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
    ];

    let traverseDataVector = returnDoubleVector(traverseData[0]);
    let traverseDataVector2 = returnDoubleVector(traverseData[1]);
    let traverseDataVector3 = returnDoubleVector(traverseData[2]);

    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    let traversePlaneInstance = new Module.TraversePlane(area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    let pv3 = traversePlaneInstance.getPv3Value();
    let percent75Rule = traversePlaneInstance.get75percentRule() * 100; // Convert to percentage

    testNumberValue(pv3, 0.7508102988157324, "VelocityPressureData: pv3 (1)");
    testNumberValue(percent75Rule, 100, "VelocityPressureData: percent75Rule (1)");

    // Release memory
    traversePlaneInstance.delete();
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();

    area = 143.63 * 32.63 / 144.0;
    dryBulbTemp = 123;
    barometricPressure = 26.57;
    staticPressure = -17.0;
    pitotTubeCoefficient = 0.87292611371180784;
    traversePlaneTraverseData = new Module.DoubleVector2D();
    traverseData = [
        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
    ];

    traverseDataVector = returnDoubleVector(traverseData[0]);
    traverseDataVector2 = returnDoubleVector(traverseData[1]);
    traverseDataVector3 = returnDoubleVector(traverseData[2]);

    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    let traversePlaneInstance2 = new Module.TraversePlane(area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    pv3 = traversePlaneInstance2.getPv3Value();
    percent75Rule = traversePlaneInstance2.get75percentRule() * 100; // Convert to percentage

    testNumberValue(pv3, 0.6007, "VelocityPressureData: pv3 (2)");
    testNumberValue(percent75Rule, 100, "VelocityPressureData: percent75Rule (2)");

    // Release memory
    traversePlaneInstance2.delete();
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();
}

function getPlaneResults()
{
    let area = 143.63 * 32.63 / 144.0;

    //getPlaneData()

    //PlaneData
    let plane5upstreamOfPlane2 = true;
    let totalPressureLossBtwnPlanes1and4 = 0;
    let totalPressureLossBtwnPlanes2and5 = 0.627;

    //let planeDataInstance = new Module.PlaneData(FlangePlane, FlangePlane, TraversePlane, std::vector<TraversePlane>, MstPlane, MstPlane, double, double, bool)

    //FlangePlane
    //FanInletFlange
    let flangePlaneArea = area * 2;
    let flangePlaneLength = 32.63;
    let dryBulbTemp = 123;
    let barometricPressure = 26.57;
    let flangePlaneInstance = new Module.FlangePlane(flangePlaneArea, dryBulbTemp, barometricPressure);
    //FanEvaseOrOutletFlange
    flangePlaneArea = 70 * 78 / 144.0;
    dryBulbTemp = 132.7;
    barometricPressure = 26.57;
    let flangePlaneInstance2 = new Module.FlangePlane(flangePlaneArea, dryBulbTemp, barometricPressure);


    //TraversePlane
    //FlowTraverse
    let traverseArea = area;
    let traverseDryBulbTemp = 123;
    let traverseBarometricPressure = 26.57;
    let traverseStaticPressure = -18.1;
    let pitotTubeCoefficient = 0.87292611371180784;
    let traversePlaneTraverseData = new Module.DoubleVector2D();

    let traversePlaneTraverseDoubles = [
        [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
        [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
        [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
    ];
    
    let traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
    let traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
    let traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);
    
    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    // area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traverseInputData
    let traversePlaneInstance = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);
    
    // Release memory
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();

    //AddlTraversePlanes
    //traverse_plane_vector
    traverseArea = area;
    traverseDryBulbTemp = 123;
    traverseBarometricPressure = 26.57;
    traverseStaticPressure = -17.0;
    pitotTubeCoefficient = 0.87292611371180784;
    traversePlaneTraverseData = new Module.DoubleVector2D();

    traversePlaneTraverseDoubles = [
        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
    ];

    traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
    traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
    traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);

    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    traversePlaneInstance2 = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    // Release memory
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();

    traverseArea = area;
    traverseDryBulbTemp = 124;
    traverseBarometricPressure = 26.57;
    traverseStaticPressure = -16.5;
    pitotTubeCoefficient = 0.872;
    traversePlaneTraverseData = new Module.DoubleVector2D();

    traversePlaneTraverseDoubles = [
        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
    ];

    traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
    traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
    traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);

    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    traversePlaneInstance3 = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);
    
    // Release memory
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();
    
    let AddlTraversePlanes = new Module.TraversePlaneVector();
    AddlTraversePlanes.push_back(traversePlaneInstance2);
    AddlTraversePlanes.push_back(traversePlaneInstance3);

    traversePlaneInstance2.delete();
    traversePlaneInstance3.delete();

    //MstPlane
    //InletMstPlane
    let mstArea = area * 2;
    let mstDryBulbTemp = 123;
    let mstBarometricPressure = 26.57;
    let mstStaticPressure = -17.55;

    let mstPlaneInstance = new Module.MstPlane(mstArea, mstDryBulbTemp, mstBarometricPressure, mstStaticPressure);

    //OutletMstPlane
    mstArea = (55.42 * 60.49) / 144.0;
    mstDryBulbTemp = 132.7;
    mstBarometricPressure = 26.57;
    mstStaticPressure = 1.8;

    let mstPlaneInstance2 = new Module.MstPlane(mstArea, mstDryBulbTemp, mstBarometricPressure, mstStaticPressure);


    //getPlaneData()
    let planeDataInstance = new Module.PlaneData(flangePlaneInstance, flangePlaneInstance2, traversePlaneInstance, AddlTraversePlanes, mstPlaneInstance, mstPlaneInstance2, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);

    flangePlaneInstance.delete();
    flangePlaneInstance2.delete();
    traversePlaneInstance.delete()
    AddlTraversePlanes.delete();
    mstPlaneInstance.delete();
    mstPlaneInstance2.delete();

    //getBaseGasDensity()

    //BaseGasDensity
    let bgdDryBulbTemp = 123;
    let bgdStaticPressure = -17.6;
    let bgdBarometricPressure = 26.57;
    let bgdGasDensity = 0.0547;
    let gasType = Module.GasType.AIR;

    //getBaseGasDensity()
    let baseGasDensityInstance = new Module.BaseGasDensity(bgdDryBulbTemp, bgdStaticPressure, bgdBarometricPressure, bgdGasDensity, gasType);

    let output = Module.PlaneDataNodeBindingCalculate(planeDataInstance, baseGasDensityInstance);

    baseGasDensityInstance.delete();
    
    function testEq(results, expected, isStaticPressure, testNum) {
        testNumberValue(results.gasDensity, expected.gasDensity, "PlaneResults: gasDensity" + ' (' + testNum.toString() + ')');
        testNumberValue(results.gasVolumeFlowRate, expected.gasVolumeFlowRate, "PlaneResults: gasVolumeFlowRate" + ' (' + testNum.toString() + ')');
        testNumberValue(results.gasVelocity, expected.gasVelocity, "PlaneResults: gasVelocity" + ' (' + testNum.toString() + ')');
        testNumberValue(results.gasVelocityPressure, expected.gasVelocityPressure, "PlaneResults: gasVelocityPressure" + ' (' + testNum.toString() + ')');
        testNumberValue(results.gasTotalPressure, expected.gasTotalPressure, "PlaneResults: gasTotalPressure" + ' (' + testNum.toString() + ')');
        if (isStaticPressure) {
            testNumberValue(results.staticPressure, expected.staticPressure, "PlaneResults: staticPressure" + ' (' + testNum.toString() + ')');
        }
    }
    
    testEq(output.fanInletFlange, {
        "gasDensity": 0.054707937910736096,
        "gasVolumeFlowRate": 368484.70105160266,
        "gasVelocity": 5660.955271820326,
        "gasVelocityPressure": 1.4595154074095142,
        "gasTotalPressure": -16.090484592590485,
        "staticPressure": -17.55
    }, true, 1);
    testEq(output.fanOrEvaseOutletFlange, {
        "gasDensity": 0.05781581992717993,
        "gasVolumeFlowRate": 348742.34384798247,
        "gasVelocity": 9197.600277309428,
        "gasVelocityPressure": 4.070924792774011,
        "gasTotalPressure": 12.156298668206892,
        "staticPressure": 8.085373875432882
    }, true, 2);
    testEq(output.flowTraverse, {
        "gasDensity": 0.0546206208926391,
        "gasVolumeFlowRate": 132250.42933608184,
        "gasVelocity": 4063.47271956754,
        "gasVelocityPressure": .75081,
        "gasTotalPressure": -17.34919
    }, false, 3);
    testEq(output.inletMstPlane, {
        "gasDensity": 0.054707937910736096,
        "gasVolumeFlowRate": 368484.70105160266,
        "gasVelocity": 5660.955271820326,
        "gasVelocityPressure": 1.4595154074095142,
        "gasTotalPressure": -16.090484592590485
    }, false, 4);
    testEq(output.outletMstPlane, {
        "gasDensity": 0.05683429586662124,
        "gasVolumeFlowRate": 354698.4763125503,
        "gasVelocity": 15236.026136905648,
        "gasVelocityPressure": 10.983298668206892,
        "gasTotalPressure": 12.783298668206893
    }, false, 5);

    let trav = [
        {
            "gasDensity": 0.054795254928833075,
            "gasVolumeFlowRate": 118104.78734062292,
            "gasVelocity": 3628.839496538495,
            "gasVelocityPressure": 0.6007,
            "gasTotalPressure": -16.3993
        },
        {
            "gasDensity": 0.054780670621748434,
            "gasVolumeFlowRate": 117995.19024728928,
            "gasVelocity": 3625.472060975973,
            "gasVelocityPressure": 0.599426,
            "gasTotalPressure": -15.900574 
        }
    ];

    //let addlTravPlanesVector = new Module.PlaneDataNodeBindingDataVector(output.addlTravPlanes);

    let testNum = 6;
    for (let i = 0; i < output.addlTravPlanes.size(); i++) { // error: length = 0, was .size
        testEq(output.addlTravPlanes.get(i), trav[i], false, testNum);
        testNum++;
    }
}

function fan203()
{
    let area = 143.63 * 32.63 / 144.0;

    //FanRatedInfo
    let fanSpeed = 1191;
    let motorSpeed = 1191;
    let fanSpeedCorrected = 1170;
    let densityCorrected = 0.05;
    let pressureBarometricCorrected = 26.28;
    
    //getFanRatedInfo()
    let fanRatedInfoInstance = new Module.FanRatedInfo(fanSpeed, motorSpeed, fanSpeedCorrected, densityCorrected, pressureBarometricCorrected);

    //PlaneData
    let plane5upstreamOfPlane2 = true;
    let totalPressureLossBtwnPlanes1and4 = 0;
    let totalPressureLossBtwnPlanes2and5 = 0.627;

    //let planeDataInstance = new Module.PlaneData(FlangePlane, FlangePlane, TraversePlane, std::vector<TraversePlane>, MstPlane, MstPlane, double, double, bool)

    //FlangePlane
    //FanInletFlange
    let flangePlaneArea = area * 2;
    let flangePlaneLength = 32.63;
    let dryBulbTemp = 123;
    let barometricPressure = 26.57;
    let flangePlaneInstance = new Module.FlangePlane(flangePlaneArea, dryBulbTemp, barometricPressure);
    //FanEvaseOrOutletFlange
    flangePlaneArea = 70 * 78 / 144.0;
    dryBulbTemp = 132.7;
    barometricPressure = 26.57;
    let flangePlaneInstance2 = new Module.FlangePlane(flangePlaneArea, dryBulbTemp, barometricPressure);


    //TraversePlane
    //FlowTraverse
    let traverseArea = area;
    let traverseDryBulbTemp = 123;
    let traverseBarometricPressure = 26.57;
    let traverseStaticPressure = -18.1;
    let pitotTubeCoefficient = 0.87292611371180784;
    let traversePlaneTraverseData = new Module.DoubleVector2D();

    let traversePlaneTraverseDoubles = [
        [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
        [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
        [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
    ];
    
    let traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
    let traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
    let traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);
    
    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    // area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traverseInputData
    let traversePlaneInstance = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    // Release memory
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();

    //AddlTraversePlanes
    //traverse_plane_vector
    traverseArea = area;
    traverseDryBulbTemp = 123;
    traverseBarometricPressure = 26.57;
    traverseStaticPressure = -17.0;
    pitotTubeCoefficient = 0.87292611371180784;
    traversePlaneTraverseData = new Module.DoubleVector2D();

    traversePlaneTraverseDoubles = [
        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
    ];

    traverseDataVector = returnDoubleVector(traversePlaneTraverseDoubles[0]);
    traverseDataVector2 = returnDoubleVector(traversePlaneTraverseDoubles[1]);
    traverseDataVector3 = returnDoubleVector(traversePlaneTraverseDoubles[2]);

    traversePlaneTraverseData.push_back(traverseDataVector);
    traversePlaneTraverseData.push_back(traverseDataVector2);
    traversePlaneTraverseData.push_back(traverseDataVector3);

    traversePlaneInstance2 = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    // Release memory
    traverseDataVector.delete();
    traverseDataVector2.delete();
    traverseDataVector3.delete();
    traversePlaneTraverseData.delete();
    
    let AddlTraversePlanes = new Module.TraversePlaneVector();
    AddlTraversePlanes.push_back(traversePlaneInstance2);
    traversePlaneInstance2.delete();

    //MstPlane
    //InletMstPlane
    let mstArea = area * 2;
    let mstDryBulbTemp = 123;
    let mstBarometricPressure = 26.57;
    let mstStaticPressure = -17.55;

    let mstPlaneInstance = new Module.MstPlane(mstArea, mstDryBulbTemp, mstBarometricPressure, mstStaticPressure);

    //OutletMstPlane
    mstArea = (55.42 * 60.49) / 144.0;
    mstDryBulbTemp = 132.7;
    mstBarometricPressure = 26.57;
    mstStaticPressure = 1.8;

    let mstPlaneInstance2 = new Module.MstPlane(mstArea, mstDryBulbTemp, mstBarometricPressure, mstStaticPressure);


    //getPlaneData()
    let planeDataInstance = new Module.PlaneData(flangePlaneInstance, flangePlaneInstance2, traversePlaneInstance, AddlTraversePlanes, mstPlaneInstance, mstPlaneInstance2, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);

    // Release memory
    flangePlaneInstance.delete();
    flangePlaneInstance2.delete();
    AddlTraversePlanes.delete()
    mstPlaneInstance.delete()
    mstPlaneInstance2.delete();

    //BaseGasDensity
    let bgdDryBulbTemp = 123;
    let bgdStaticPressure = -17.6;
    let bgdBarometricPressure = 26.57;
    let bgdGasDensity = 0.0547;
    let gasType = Module.GasType.AIR;

    //getBaseGasDensity()
    let baseGasDensityInstance = new Module.BaseGasDensity(bgdDryBulbTemp, bgdStaticPressure, bgdBarometricPressure, bgdGasDensity, gasType);

    //FanShaftPower
    //const double motorShaftPower, const double efficiencyMotor, const double efficiencyVFD,
    //const double efficiencyBelt, const double sumSEF
    let fspMotorShaftPower = (4200 * 205 * 0.88 * Math.sqrt(3)) / 746.0;
    let fspEfficiencyMotor = 95;
    let fspEfficiencyVFD = 100;
    let fspEfficiencyBelt = 100;
    let fspSumSEF = 0;

    //getFanShaftPower()
    let fanShaftPowerInstance = new Module.FanShaftPower(fspMotorShaftPower, fspEfficiencyMotor, fspEfficiencyVFD, fspEfficiencyBelt, fspSumSEF);
    
    //Calculation procedure
    //Fan203::Output const rv = Fan203(fanRatedInfo, planeData, baseGasDensity, fanShaftPower).calculate();
    let fan203Instance = new Module.Fan203(fanRatedInfoInstance, planeDataInstance, baseGasDensityInstance, fanShaftPowerInstance);
    let fan203Output = fan203Instance.calculate();

    //Tests
    
    testNumberValue(fan203Output.fanEfficiencyTotalPressure, 53.60738684355601, "Fan203: Fan Efficiency Total Pressure");
    testNumberValue(fan203Output.fanEfficiencyStaticPressure, 49.20691409764023, "Fan203: Fan Efficiency Static Pressure");
    testNumberValue(fan203Output.fanEfficiencyStaticPressureRise, 50.768875240824116, "Fan203: Fan Efficiency Static Pressure Rise");
    
    testNumberValue(fan203Output.asTested.flow, 250332.6394178045, "Fan203: Flow");
    testNumberValue(fan203Output.asTested.kpc, 0.9982905074, "Fan203: KPC");
    testNumberValue(fan203Output.asTested.power, 1671.2107816151, "Fan203: Power");
    testNumberValue(fan203Output.asTested.pressureStatic, 21.2207447999, "Fan203: Pressure Static");
    testNumberValue(fan203Output.asTested.pressureTotal, 23.1184721997, "Fan203: Pressure Total");
    testNumberValue(fan203Output.asTested.staticPressureRise, 21.8943488943, "Fan203: Static Pressure Rise");

    testNumberValue(fan203Output.converted.flow, 245498.3175715673, "Fan203: Flow Corrected");
    testNumberValue(fan203Output.converted.kpc, 0.986542913, "Fan203: KPC Corrected");
    testNumberValue(fan203Output.converted.power, 1445.5400545013, "Fan203: Power Corrected");
    testNumberValue(fan203Output.converted.pressureStatic, 18.6846696404, "Fan203: Pressure Static Corrected");
    testNumberValue(fan203Output.converted.pressureTotal, 20.355601074, "Fan203: Pressure Total Corrected");
    testNumberValue(fan203Output.converted.staticPressureRise, 19.277771819, "Fan203: Static Pressure Rise Corrected");


    // Release memory
    fanRatedInfoInstance.delete();

}

function fanCurve()
{
    // Needs to be handled by the "middle layer"
    // if (baseCurveDataDefined)
    // else if (ratedPointCurveDataDefined)
    // else


    //BaseCurve
    let density = 0.0308;
    let densityCorrected = 0.0332;
    let speed = 1180;
    let speedCorrected = 1187;
    let pressureBarometric = 29.36;
    let pressureBarometricCorrected = 29.36;
    let pt1Factor = -0.93736;
    let gamma = 1.4;
    let gammaCorrected = 1.4;
    let area1 = 34;
    let area2 = 12.7;
    let curveType = "FanStaticPressure";
    let baseCurveData = [
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
    ];

    let baseCurveVector = returnBaseCurveVector(baseCurveData);
    let fanCurveData = new Module.FanCurveData(curveType, baseCurveVector);

    let fanCurve = new Module.FanCurve(density, densityCorrected, speed, speedCorrected, pressureBarometric, pressureBarometricCorrected, pt1Factor, gamma, gammaCorrected, area1, area2, fanCurveData);
    let resultData = fanCurve.calculate();

    
    //var res = bindings.fanCurve(inp);

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

    
    
    function testEq(results, expected, testNum) {
        for (var i = 0; i < results.size(); i++) {
            testNumberValue(results.get(i).flow, expected[i].flow, "FanCurve: flow" + ' (' + testNum.toString() + ')');
            testNumberValue(results.get(i).pressure, expected[i].pressure, "FanCurve: pressure" + ' (' + testNum.toString() + ')');
            testNumberValue(results.get(i).power, expected[i].power, "FanCurve: power" + ' (' + testNum.toString() + ')');
            testNumberValue(results.get(i).efficiency, expected[i].efficiency, "FanCurve: efficiency" + ' (' + testNum.toString() + ')');
            testNum++;
        }
    }

    function returnResultDataObj(flow, pressure, power, efficiency)
    {
        let resultDataObj = {
            "flow": flow,
            "pressure": pressure,
            "power": power,
            "efficiency": efficiency
        };

        return resultDataObj;
    }
    function returnResultDataObjArray(resultDataArrays)
    {
        let resultDataObjArray = [];

        for (x of resultDataArrays) // each row of resultDataArrays should have four columns
        {
            resultDataObjArray.push(returnResultDataObj(x[0], x[1], x[2], x[3]));
        }

        return resultDataObjArray;
    }

    let testNum = 1;
    testEq(resultData, returnResultDataObjArray(expected), testNum);

    // Release memory
    baseCurveVector.delete();
    fanCurveData.delete();
    fanCurve.delete();
    resultData.delete();

    
    //RatedPoint
    density = 0.0308;
    densityCorrected = 0.0332;
    speed = 1180;
    speedCorrected = 1187;
    pressureBarometric = 29.36;
    pressureBarometricCorrected = 29.36;
    pt1Factor = -0.93736;
    gamma = 1.4;
    gammaCorrected = 1.4;
    area1 = 34;
    area2 = 12.7;
    curveType = 'FanStaticPressure';
    let ratedPointCurveData = [
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
    ];

    // This final bit is currently not working due to overloaded constructor for FanCurveData not working correctly
    let ratedPointVector = returnRatedPointVector(ratedPointCurveData);
    fanCurveData = new Module.FanCurveData(curveType, ratedPointVector);
    //fanCurveData = Module.returnFanCurveData_RatedPoint(curveType, ratedPointVector);

    fanCurve = new Module.FanCurve(density, densityCorrected, speed, speedCorrected, pressureBarometric, pressureBarometricCorrected, pt1Factor, gamma, gammaCorrected, area1, area2, fanCurveData);
    resultData = fanCurve.calculate();

    //testNum = 16;
    testEq(resultData, returnResultDataObjArray(expected), testNum);

    // Release memory
    ratedPointVector.delete();
    fanCurveData.delete();
    fanCurve.delete();
    resultData.delete();
}

function optimalFanEfficiency()
{   
    //fanType = 0;
    let fanType = Module.OptimalFanEfficiencyFanType.AirfoilSISW
    let fanSpeed = 1180;
    let flowRate = 40000;
    let inletPressure = -9;
    let outletPressure = 1;
    let compressibility = 0.995;

    let optimalEfficiencyFactor = new Module.OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure, compressibility);
    let optimalEfficiencyFactorResult = optimalEfficiencyFactor.calculate();
    optimalEfficiencyFactorResult = optimalEfficiencyFactorResult * 100;
    testNumberValue(optimalEfficiencyFactorResult, 80.56103029, "Optimal Efficiency Factor (input 1)");

    optimalEfficiencyFactor.delete();

    //fanType = 11;
    fanType = Module.OptimalFanEfficiencyFanType.LongShavings;
    fanSpeed = 1180;
    flowRate = 10000;
    inletPressure = -9;
    outletPressure = 1;
    compressibility = 0.995;

    optimalEfficiencyFactor = new Module.OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure, compressibility);
    optimalEfficiencyFactorResult = optimalEfficiencyFactor.calculate();
    optimalEfficiencyFactorResult = optimalEfficiencyFactorResult * 100;
    testNumberValue(optimalEfficiencyFactorResult, 60.6953126, "Optimal Efficiency Factor (input 2)");

    optimalEfficiencyFactor.delete();

    //fanType = 6;
    fanType = Module.OptimalFanEfficiencyFanType.BackwardCurvedDIDW;
    fanSpeed = 1180;
    flowRate = 500000;
    inletPressure = -6;
    outletPressure = 1;
    compressibility = 0.995;

    optimalEfficiencyFactor = new Module.OptimalFanEfficiency(fanType, fanSpeed, flowRate, inletPressure, outletPressure, compressibility);
    optimalEfficiencyFactorResult = optimalEfficiencyFactor.calculate();
    optimalEfficiencyFactorResult = optimalEfficiencyFactorResult * 100;
    testNumberValue(optimalEfficiencyFactorResult, 29.31237501, "Optimal Efficiency Factor (input 3)");

    optimalEfficiencyFactor.delete();
}

function compressibilityFactor()
{
    let moverShaftPower = 300;
    let inletPressure = -8.5;
    let outletPressure = 3;
    let barometricPressure = 29;
    let flowRate = 1000;
    let specificHeatRatio = 1.4;

    let compressibilityFactor = new Module.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
    let compressibilityFactorResult = compressibilityFactor.calculate();
    testNumberValue(compressibilityFactorResult, 1.5795535958, "Compressibility Factor (input 1)");

    compressibilityFactor.delete();

    moverShaftPower = 566;
    inletPressure = -16.36;
    outletPressure = 1.1;
    barometricPressure = 29.36;
    flowRate = 129691;
    specificHeatRatio = 1.4;

    compressibilityFactor = new Module.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
    compressibilityFactorResult = compressibilityFactor.calculate();
    testNumberValue(compressibilityFactorResult, 0.9879934727, "Compressibility Factor (input 2)");

    compressibilityFactor.delete();
    
    moverShaftPower = 623;
    inletPressure = -8.92;
    outletPressure = 2.28;
    barometricPressure = 29.36;
    flowRate = 151961;
    specificHeatRatio = 1.4;

    compressibilityFactor = new Module.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
    compressibilityFactorResult = compressibilityFactor.calculate();
    testNumberValue(compressibilityFactorResult, 0.9953146218, "Compressibility Factor (input 3)");

    compressibilityFactor.delete();
}

//call tests
resultsExisting();
resultsModified();
getBaseGasDensity();
getVelocityPressureData();
getPlaneResults();
fan203();
fanCurve();
optimalFanEfficiency();
compressibilityFactor();