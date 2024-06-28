function powerFactorCalc(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.realDemand), rnd(expected[0]), "realDemand");
        testNumberValue(rnd(results.demandPenalty), rnd(expected[1]), "demandPenalty");
        testNumberValue(rnd(results.reactivePower), rnd(expected[2]), "reactivePower");
        testNumberValue(rnd(results.proposedReactivePower), rnd(expected[3]),"proposedReactivePower");
        testNumberValue(rnd(results.proposedCapacitance), rnd(expected[4]),"proposedCapacitance");
    };

    logMessage('Calculate Apparent Power, Real Power, Reactive Power, Phase Angle, Power Factor and Capacitance based on inputs, 9 combinations:', true);

    let instance = new Module.PowerFactor();

    logMessage('Powers as inputs, 3 combinations: ', true);
    logMessage('ApparentPower + RealPower as inputs: Test# 1', true);
    validate(instance.calculate(Module.PowerFactorModeType.ApparentPower_RealPower, 100, 87, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('ApparentPower + ReactivePower as inputs: Test# 2', true);
    validate(instance.calculate(Module.PowerFactorModeType.ApparentPower_ReactivePower, 100, 49.3052, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('RealPower + ReactivePower as inputs: Test# 3', true);
    validate(instance.calculate(Module.PowerFactorModeType.RealPower_ReactivePower, 87, 49.3052, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('Power and Phase Angle as inputs, 3 combinations: ', true);
    logMessage('ApparentPower + PhaseAngle as inputs: Test# 1', true);
    validate(instance.calculate(Module.PowerFactorModeType.ApparentPower_PhaseAngle, 100, 29.5413605, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('RealPower + PhaseAngle as inputs: Test# 2', true);
    validate(instance.calculate(Module.PowerFactorModeType.RealPower_PhaseAngle, 87, 29.5413605, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('ReactivePower + PhaseAngle as inputs: Test# 3', true);
    validate(instance.calculate(Module.PowerFactorModeType.ReactivePower_PhaseAngle, 49.3052, 29.5413605, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('Power and Power Factor as inputs, 3 combinations: ', true);
    logMessage('ApparentPower + PowerFactor as inputs: Test# 1', true);
    validate(instance.calculate(Module.PowerFactorModeType.ApparentPower_PowerFactor, 100, 0.87, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('RealPower + PowerFactor as inputs: Test# 2', true);
    validate(instance.calculate(Module.PowerFactorModeType.RealPower_PowerFactor, 87, 0.87, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    logMessage('ReactivePower + PowerFactor as inputs: Test# 3', true);
    validate(instance.calculate(Module.PowerFactorModeType.ReactivePower_PowerFactor, 49.3052, 0.87, 0.95), [91.5789, 8.4211, 49.3052, 28.5955, 20.7097]);

    instance.delete();
}

powerFactorCalc();