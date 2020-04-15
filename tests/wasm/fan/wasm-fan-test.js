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

function fan203()
{
    /*
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
    */

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
    let traversePlaneTraverseData = [
        [0.701, 0.703, 0.6675, 0.815, 0.979, 1.09, 1.155, 1.320, 1.578, 2.130],
        [0.690, 0.648, 0.555, 0.760, 0.988, 1.060, 1.100, 1.110, 1.458, 1.865],
        [0.691, 0.621, 0.610, 0.774, 0.747, 0.835, 0.8825, 1.23, 1.210, 1.569]
    ]
    // area, dryBulbTemp, barometricPressure, staticPressure, pitotTubeCoefficient, traverseInputData
    let traversePlaneInstance = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    //AddlTraversePlanes
    //traverse_plane_vector
    traverseArea = area;
    traverseDryBulbTemp = 123;
    traverseBarometricPressure = 26.57;
    traverseStaticPressure = -17.0;
    pitotTubeCoefficient = 0.87292611371180784;
    traversePlaneTraverseData = [
        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
    ]
    let traversePlaneInstance2 = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    traverseArea = area;
    traverseDryBulbTemp = 124;
    traverseBarometricPressure = 26.57;
    traverseStaticPressure = -16.5;
    pitotTubeCoefficient = 0.872;
    traversePlaneTraverseData = [
        [0.662, 0.568, 0.546, 0.564, 0.463, 0.507, 0.865, 1.017, 1.247, 1.630],
        [0.639, 0.542, 0.530, 0.570, 0.603, 0.750, 0.965, 1.014, 1.246, 1.596],
        [0.554, 0.452, 0.453, 0.581, 0.551, 0.724, 0.844, 1.077, 1.323, 1.620]
    ]
    let traversePlaneInstance3 = new Module.TraversePlane(traverseArea, traverseDryBulbTemp, traverseBarometricPressure, traverseStaticPressure, pitotTubeCoefficient, traversePlaneTraverseData);

    let AddlTraversePlanes = [traversePlaneInstance2, traversePlaneInstance3];

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

    //BaseGasDensity
    //let bgdDryBulbTemp = 123;
    //let bgdStaticPressure = -17.6;
    //let bgdBarometricPressure = 26.57;
    //let bgdGasDensity = 0.0547;
    //let gasType = Module.GasType.AIR;

    //let baseGasDensityInstance = new Module.BaseGasDensity(bgdDryBulbTemp, bgdStaticPressure, bgdBarometricPressure, bgdGasDensity, gasType);

    /*
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
    */

    //getPlaneData()
    let planeDataInstance = new Module.PlaneData(flangePlaneInstance, flangePlaneInstance2, traversePlaneInstance, AddlTraversePlanes, mstPlaneInstance, mstPlaneInstance2, totalPressureLossBtwnPlanes1and4, totalPressureLossBtwnPlanes2and5, plane5upstreamOfPlane2);

    //BaseGasDensity
    let bgdDryBulbTemp = 123;
    let bgdStaticPressure = -17.6;
    let bgdBarometricPressure = 26.57;
    let bgdGasDensity = 0.0547;
    let gasType = Module.GasType.AIR;

    //getBaseGasDensity()
    let baseGasDensityInstance = new Module.BaseGasDensity(bgdDryBulbTemp, bgdStaticPressure, bgdBarometricPressure, bgdGasDensity, gasType);

    //FanShaftPower
    let fspMotorShaftPower = (4200 * 205 * 0.88 * Math.sqrt(3)) / 746.0;
    let fspEfficiencyMotor = 95;
    let fspEfficiencyVFD = 100;
    let fspEfficiencyBelt = 100;
    let fspSumSEF = 0;

    //getFanShaftPower()
    let fanShaftPowerInstance = new Module.FanShaftPower(fspMotorShaftPower, fspEfficiencyMotor, fspEfficiencyVFD, fspEfficiencyBelt, fspSumSEF);
    
    //Calculation procedure
    //Fan203::Output const rv = Fan203(fanRatedInfo, planeData, baseGasDensity, fanShaftPower).calculate();
    fan203Instance = new Module.Fan203(fanRatedInfoInstance, planeDataInstance, baseGasDensityInstance, fanShaftPowerInstance);
    fan203Output = fan203Instance.calculate();

    /*
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
    */

    //Tests
    /*
    testNumberValue(fan203Output.fanEfficiencyTotalPressure, 53.60738684355601, "Fan Efficiency Total Pressure");
    testNumberValue(fan203Output.fanEfficiencyStaticPressure, 49.20691409764023, "Fan Efficiency Static Pressure");
    testNumberValue(fan203Output.fanEfficiencyStaticPressureRise, 50.768875240824116, "Fan Efficiency Static Pressure Rise");

    testNumberValue(fan203Output.flow, 250332.6394178045, "Flow");
    testNumberValue(fan203Output.kpc, 0.9982905074, "KPC");
    testNumberValue(fan203Output.power, 1671.2107816151, "Power");
    testNumberValue(fan203Output.pressureStatic, 21.2207447999, "Pressure Static");
    testNumberValue(fan203Output.pressureTotal, 23.1184721997, "Pressure Total");
    testNumberValue(fan203Output.staticPressureRise, 21.8943488943, "Static Pressure Rise");

    testNumberValue(fan203Output.flowCorrected, 245498.3175715673, "Flow Corrected");
    testNumberValue(fan203Output.kpcCorrected, 0.986542913, "KPC Corrected");
    testNumberValue(fan203Output.powerCorrected, 1445.5400545013, "Power Corrected");
    testNumberValue(fan203Output.pressureStaticCorrected, 18.6846696404, "Pressure Static Corrected");
    testNumberValue(fan203Output.pressureTotalCorrected, 20.355601074, "Pressure Total Corrected");
    testNumberValue(fan203Output.staticPressureRiseCorrected, 19.277771819, "Static Pressure Rise Corrected");
    */
}

function getFanCurve()
{
    //
}

function getOptimalFanEfficiency()
{   
    //let fanType = 0;
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
}

function getCompressibilityFactor()
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


    moverShaftPower = 566;
    inletPressure = -16.36;
    outletPressure = 1.1;
    barometricPressure = 29.36;
    flowRate = 129691;
    specificHeatRatio = 1.4;

    compressibilityFactor = new Module.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
    compressibilityFactorResult = compressibilityFactor.calculate();
    testNumberValue(compressibilityFactorResult, 0.9879934727, "Compressibility Factor (input 2)");

    
    moverShaftPower = 623;
    inletPressure = -8.92;
    outletPressure = 2.28;
    barometricPressure = 29.36;
    flowRate = 151961;
    specificHeatRatio = 1.4;

    compressibilityFactor = new Module.CompressibilityFactor(moverShaftPower, inletPressure, outletPressure, barometricPressure, flowRate, specificHeatRatio);
    compressibilityFactorResult = compressibilityFactor.calculate();
    testNumberValue(compressibilityFactorResult, 0.9953146218, "Compressibility Factor (input 3)");
}

//call tests
resultsExisting();
resultsModified();
getBaseGasDensity();
fan203();
//getFanCurve();
getOptimalFanEfficiency();
getCompressibilityFactor();