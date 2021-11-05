function returnDoubleVector(doublesArray)
{
    let doubleVector = new Module.DoubleVector();

    for (x of doublesArray)
    {
        doubleVector.push_back(x);
    }

    return doubleVector;
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
    let velocityPressure = 0;
    //unused
    let specifiedDriveEfficiency = 1;

    let fanInput = new Module.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
    let motor = new Module.Motor(lineFrequency, motorRatedPower, motorRpm, efficiencyClass, specifiedEfficiency, motorRatedVoltage, fullLoadAmps, sizeMargin);
    let baselineFieldData = new Module.FieldDataBaseline(measuredPower, measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor, loadEstimationMethod, velocityPressure);
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
    let velocityPressure = 0;
    //calculate
    let fanInput = new Module.FanInput(fanSpeed, airDensity, drive, specifiedDriveEfficiency);
    let fanFieldData = new Module.FieldDataModified(measuredVoltage, measuredAmps, flowRate, inletPressure, outletPressure, compressibilityFactor, velocityPressure)
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
    let gasDensityResult = relativeHumidityInstance.getGasDensity();
    let AbsolutePressureInResult = relativeHumidityInstance.getAbsolutePressureIn();
    let SaturatedHumidityRatioResult = relativeHumidityInstance.getSaturatedHumidityRatio();
    let DegreeOfSaturationResult = relativeHumidityInstance.getDegreeOfSaturation();
    let HumidityRatioResult = relativeHumidityInstance.getHumidityRatio();
    let SpecificVolumeResult = relativeHumidityInstance.getSpecificVolume();
    let EnthalpyResult = relativeHumidityInstance.getEnthalpy();
    let DewPointResult = relativeHumidityInstance.getDewPoint();
    let RelativeHumidityResult = relativeHumidityInstance.getRelativeHumidity();
    let SaturationPressureResult = relativeHumidityInstance.getSaturationPressure();
    let WetBulbTempResult = relativeHumidityInstance.getWetBulbTemp();
    relativeHumidityInstance.delete();

    testNumberValue(gasDensityResult, 0.05637830145287457, "Gas Density (relativeHumidity)");
    testNumberValue(AbsolutePressureInResult, 25.2767099634697, "AbsolutePressureInResult (relativeHumidity)");
    testNumberValue(SaturatedHumidityRatioResult, 0.10830760118401817, "SaturatedHumidityRatioResult (relativeHumidity)");
    testNumberValue(DegreeOfSaturationResult, 0.3144126326912711, "DegreeOfSaturationResult (relativeHumidity)");
    testNumberValue(HumidityRatioResult, 0.03405327802874338, "HumidityRatioResult (relativeHumidity)");
    testNumberValue(SpecificVolumeResult, 18.34133436767489, "SpecificVolumeResult (relativeHumidity)");
    testNumberValue(EnthalpyResult, 68.37124560820246, "EnthalpyResult (relativeHumidity)");
    testNumberValue(DewPointResult, 87.40387101362482, "DewPointResult (relativeHumidity)");
    testNumberValue(RelativeHumidityResult, 0.35, "RelativeHumidityResult (relativeHumidity)");
    testNumberValue(SaturationPressureResult, 3.7487420264687445, "SaturationPressureResult (relativeHumidity)");
    testNumberValue(WetBulbTempResult, 93.25804647868017, "WetBulbTempResult (relativeHumidity)");

    inputType = Module.BaseGasDensityInputType.DewPoint;
    dewPoint = 0.35;

    let dewPointInstance = new Module.BaseGasDensity(dryBulbTemp, staticPressure, barometricPressure, dewPoint, gasType, inputType, specificGravity);
    gasDensityResult = dewPointInstance.getGasDensity();
    AbsolutePressureInResult = dewPointInstance.getAbsolutePressureIn();
    SaturatedHumidityRatioResult = dewPointInstance.getSaturatedHumidityRatio();
    DegreeOfSaturationResult = dewPointInstance.getDegreeOfSaturation();
    HumidityRatioResult = dewPointInstance.getHumidityRatio();
    SpecificVolumeResult = dewPointInstance.getSpecificVolume();
    EnthalpyResult = dewPointInstance.getEnthalpy();
    DewPointResult = dewPointInstance.getDewPoint();
    RelativeHumidityResult = dewPointInstance.getRelativeHumidity();
    SaturationPressureResult = dewPointInstance.getSaturationPressure();
    WetBulbTempResult = dewPointInstance.getWetBulbTemp();
    dewPointInstance.delete();

    testNumberValue(gasDensityResult, 0.057473768082717605, "Gas Density (relativeHumidity)");
    testNumberValue(AbsolutePressureInResult, 25.2767099634697, "AbsolutePressureInResult (relativeHumidity)");
    testNumberValue(SaturatedHumidityRatioResult, 0.10830760118401817, "SaturatedHumidityRatioResult (relativeHumidity)");
    testNumberValue(DegreeOfSaturationResult, 0.008730399075033634, "DegreeOfSaturationResult (relativeHumidity)");
    testNumberValue(HumidityRatioResult, 0.0009455685811960639, "HumidityRatioResult (relativeHumidity)");
    testNumberValue(SpecificVolumeResult, 17.415694184877726, "SpecificVolumeResult (relativeHumidity)");
    testNumberValue(EnthalpyResult, 31.435887656005303, "EnthalpyResult (relativeHumidity)");
    testNumberValue(DewPointResult, 0.35, "DewPointResult (relativeHumidity)");
    testNumberValue(RelativeHumidityResult, 1.0235094719915057, "RelativeHumidityResult (relativeHumidity)");
    testNumberValue(SaturationPressureResult, 3.7487420264687445, "SaturationPressureResult (relativeHumidity)");
    testNumberValue(WetBulbTempResult, 62.94970394555405, "WetBulbTempResult (relativeHumidity)");

    inputType = Module.BaseGasDensityInputType.WetBulbTemp;
    let wetBulbTemp = 110;
    let specificHeatGas = 1.03;

    let wetBulbInstance = new Module.BaseGasDensity(dryBulbTemp, staticPressure, barometricPressure, wetBulbTemp, gasType, inputType, specificGravity, specificHeatGas);
    gasDensityResult = wetBulbInstance.getGasDensity();
    AbsolutePressureInResult = wetBulbInstance.getAbsolutePressureIn();
    SaturatedHumidityRatioResult = wetBulbInstance.getSaturatedHumidityRatio();
    DegreeOfSaturationResult = wetBulbInstance.getDegreeOfSaturation();
    HumidityRatioResult = wetBulbInstance.getHumidityRatio();
    SpecificVolumeResult = wetBulbInstance.getSpecificVolume();
    EnthalpyResult = wetBulbInstance.getEnthalpy();
    DewPointResult = wetBulbInstance.getDewPoint();
    RelativeHumidityResult = wetBulbInstance.getRelativeHumidity();
    SaturationPressureResult = wetBulbInstance.getSaturationPressure();
    WetBulbTempResult = wetBulbInstance.getWetBulbTemp();
    wetBulbInstance.delete();

    testNumberValue(gasDensityResult, 0.05536774050618011, "Gas Density (relativeHumidity)");
    testNumberValue(AbsolutePressureInResult, 25.2767099634697, "AbsolutePressureInResult (relativeHumidity)");
    testNumberValue(SaturatedHumidityRatioResult, 0.10830760118401817, "SaturatedHumidityRatioResult (relativeHumidity)");
    testNumberValue(DegreeOfSaturationResult, 0.6267018765874393, "DegreeOfSaturationResult (relativeHumidity)");
    testNumberValue(HumidityRatioResult, 0.06787657691070814, "HumidityRatioResult (relativeHumidity)");
    testNumberValue(SpecificVolumeResult, 19.286981320675572, "SpecificVolumeResult (relativeHumidity)");
    testNumberValue(EnthalpyResult, 106.10492372050894, "EnthalpyResult (relativeHumidity)");
    testNumberValue(DewPointResult, 108.44107215070429, "DewPointResult (relativeHumidity)");
    testNumberValue(RelativeHumidityResult, 66.34315384222288, "RelativeHumidityResult (relativeHumidity)");
    testNumberValue(SaturationPressureResult, 3.7487420264687445, "SaturationPressureResult (relativeHumidity)");
    testNumberValue(WetBulbTempResult, 110, "WetBulbTempResult (relativeHumidity)");
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

    //release memory
    fanShaftPowerInstance.delete();
    baseGasDensityInstance.delete();
    fan203Instance.delete();

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

function optimalFanEfficiency()
{
    //fanType = 0;
    let fanType = Module.FanType.AirfoilSISW
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
    fanType = Module.FanType.LongShavings;
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
    fanType = Module.FanType.BackwardCurvedDIDW;
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
optimalFanEfficiency();
compressibilityFactor();