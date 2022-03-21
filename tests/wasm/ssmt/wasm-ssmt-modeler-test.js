function validateOutput(results) {
    validateOperations(results);
    validateBoiler(results);
    validateDeaerator(results);

    validateHighPressureHeaderSteam(results);
    validateMediumPressureHeaderSteam(results);
    validateLowPressureHeaderSteam(results);

    validateProcessSteamUsage(results);
    validateCondensate(results);
    validateHeaderHeatLoss(results);

    validateMakeupWater(results);
    validateMakeupWaterAndCondensate(results);
    validateHeatExchanger(results);
    validateCombinedCondensate(results);
    validateReturnCondensate(results);

    validateCondensingTurbine(results);
    validateCondensingTurbineIdeal(results);
    validateHighPressureToMediumPressureTurbine(results);
    validateHighPressureToMediumPressureTurbineIdeal(results);
    validateHighPressureToLowPressureTurbine(results);
    validateHighPressureToLowPressureTurbineIdeal(results);
    validateMediumPressureToLowPressureTurbine(results);
    validateMediumPressureToLowPressureTurbineIdeal(results);

    validateHighPressureToMediumPressurePrv(results);
    validateMediumPressureToLowPressurePrv(results);

    validateBlowdownFlashTank(results);
    validateCondensateFlashTank(results);
    validateHighPressureCondensateFlashTank(results);
    validateMediumPressureCondensateFlashTank(results);

    validatePowerBalanceCheckerCalculationsDomain(results);
}

function SectionHead(header){
    logMessage('Steam Modeler: Test# 1 - ' + header + ' Results ', true);
}

function defined(value){
    return (value || value == 0);
}

function validateFluidProperties(header, fluidProperties, expected){
    SectionHead(header);

    if(fluidProperties == null) return;

    if(defined(expected.pressure)) testNumberValue(fluidProperties.pressure, expected.pressure, "Pressure");
    if(defined(expected.temperature)) testNumberValue(fluidProperties.temperature, expected.temperature, "Temperature");
    if(defined(expected.specificEnthalpy)) testNumberValue(fluidProperties.specificEnthalpy, expected.specificEnthalpy, "SpecificEnthalpy");
    if(defined(expected.specificEntropy)) testNumberValue(fluidProperties.specificEntropy, expected.specificEntropy, "SpecificEntropy");
    if(defined(expected.quality)) testNumberValue(fluidProperties.quality, expected.quality, "Quality");
    if(defined(expected.specificVolume)) testNumberValue(fluidProperties.specificVolume, expected.specificVolume, "Volume");
    if(defined(expected.massFlow)) testNumberValue(fluidProperties.massFlow, expected.massFlow, "MassFlow");
    if(defined(expected.energyFlow)) testNumberValue(fluidProperties.energyFlow, expected.energyFlow, "EnergyFlow");
    if(defined(expected.density)) testNumberValue(fluidProperties.density, expected.density, "Density");
    if(defined(expected.internalEnergy)) testNumberValue(fluidProperties.internalEnergy, expected.internalEnergy, "InternalEnergy");
    if(defined(expected.processUsage)) testNumberValue(fluidProperties.processUsage, expected.processUsage, "processUsage");
}

function validateTurbineOutput(header, turbine, expected) {
    SectionHead(header);

    if(turbine == null) return;

    let inletProperties = turbine.getInletProperties();
    let outletProperties = turbine.getOutletProperties();

    if(defined(expected.energyOut)) testNumberValue(turbine.getEnergyOut(), expected.energyOut, "energyOut");
    if(defined(expected.generatorEfficiency)) testNumberValue(turbine.getGeneratorEfficiency(), expected.generatorEfficiency, "generatorEfficiency");
    if(defined(expected.inletEnergyFlow)) testNumberValue(turbine.getInletEnergyFlow(), expected.inletEnergyFlow, "inletEnergyFlow");

    if(defined(expected.inletPressure)) testNumberValue(inletProperties.pressure, expected.inletPressure, "inletPressure");
    if(defined(expected.inletQuality)) testNumberValue(inletProperties.quality, expected.inletQuality, "inletQuality");
    if(defined(expected.inletVolume)) testNumberValue(inletProperties.specificVolume, expected.inletVolume, "inletVolume");
    if(defined(expected.inletSpecificEnthalpy)) testNumberValue(inletProperties.specificEnthalpy, expected.inletSpecificEnthalpy, "inletSpecificEnthalpy");
    if(defined(expected.inletSpecificEntropy)) testNumberValue(inletProperties.specificEntropy, expected.inletSpecificEntropy, "inletSpecificEntropy");
    if(defined(expected.inletTemperature)) testNumberValue(inletProperties.temperature, expected.inletTemperature, "inletTemperature");

    if(defined(expected.isentropicEfficiency)) testNumberValue(turbine.getIsentropicEfficiency(), expected.isentropicEfficiency, "isentropicEfficiency");
    if(defined(expected.massFlow)) testNumberValue(turbine.getMassFlow(), expected.massFlow, "massFlow");
    if(defined(expected.outletEnergyFlow)) testNumberValue(turbine.getOutletEnergyFlow(), expected.outletEnergyFlow, "outletEnergyFlow");

    if(defined(expected.outletPressure)) testNumberValue(outletProperties.pressure, expected.outletPressure, "outletPressure");
    if(defined(expected.outletQuality)) testNumberValue(outletProperties.quality, expected.outletQuality, "outletQuality");
    if(defined(expected.outletVolume)) testNumberValue(outletProperties.specificVolume, expected.outletVolume, "outletVolume");
    if(defined(expected.outletSpecificEnthalpy)) testNumberValue(outletProperties.specificEnthalpy, expected.outletSpecificEnthalpy, "outletSpecificEnthalpy");
    if(defined(expected.outletSpecificEntropy)) testNumberValue(outletProperties.specificEntropy, expected.outletSpecificEntropy, "outletSpecificEntropy");
    if(defined(expected.outletTemperature)) testNumberValue(outletProperties.temperature, expected.outletTemperature, "outletTemperature");

    if(defined(expected.powerOut)) testNumberValue(turbine.getPowerOut(), expected.powerOut, "powerOut");

    if(defined(expected.outletIdealPressure)) testNumberValue(turbine.outletIdealPressure, expected.outletIdealPressure, "outletIdealPressure");
    if(defined(expected.outletIdealTemperature)) testNumberValue(turbine.outletIdealTemperature, expected.outletIdealTemperature, "outletIdealTemperature");
    if(defined(expected.outletIdealSpecificEnthalpy)) testNumberValue(turbine.outletIdealSpecificEnthalpy, expected.outletIdealSpecificEnthalpy, "outletIdealSpecificEnthalpy");
    if(defined(expected.outletIdealSpecificEntropy)) testNumberValue(turbine.outletIdealSpecificEntropy, expected.outletIdealSpecificEntropy, "outletIdealSpecificEntropy");
    if(defined(expected.outletIdealQuality)) testNumberValue(turbine.outletIdealQuality, expected.outletIdealQuality, "outletIdealQuality");
    if(defined(expected.outletIdealVolume)) testNumberValue(turbine.outletIdealVolume, expected.outletIdealVolume, "outletIdealVolume");
}

function validatePrvOutput(header, prv, expected) {
    SectionHead(header);

    if(prv == null) return;

    let steamProperties = prv.getInletProperties();
    if(defined(expected.inletEnergyFlow)) testNumberValue(prv.getInletEnergyFlow(), expected.inletEnergyFlow, "inletEnergyFlow");
    if(defined(expected.inletMassFlow)) testNumberValue(prv.getInletMassFlow(), expected.inletMassFlow, "inletMassFlow");
    if(defined(expected.inletPressure)) testNumberValue(steamProperties.pressure, expected.inletPressure, "inletPressure");
    if(defined(expected.inletQuality)) testNumberValue(steamProperties.quality, expected.inletQuality, "inletQuality");
    if(defined(expected.inletVolume)) testNumberValue(steamProperties.specificVolume, expected.inletVolume, "inletVolume");
    if(defined(expected.inletSpecificEnthalpy)) testNumberValue(steamProperties.specificEnthalpy, expected.inletSpecificEnthalpy, "inletSpecificEnthalpy");
    if(defined(expected.inletSpecificEntropy)) testNumberValue(steamProperties.specificEntropy, expected.inletSpecificEntropy, "inletSpecificEntropy");
    if(defined(expected.inletTemperature)) testNumberValue(steamProperties.temperature, expected.inletTemperature, "inletTemperature");

    steamProperties = prv.getOutletProperties();
    if(defined(expected.outletEnergyFlow)) testNumberValue(prv.getOutletMassFlow(), expected.outletEnergyFlow, "outletEnergyFlow");
    if(defined(expected.outletMassFlow)) testNumberValue(prv.getOutletEnergyFlow(), expected.outletMassFlow, "outletMassFlow");
    if(defined(expected.outletPressure)) testNumberValue(steamProperties.pressure, expected.outletPressure, "outletPressure");
    if(defined(expected.outletQuality)) testNumberValue(steamProperties.quality, expected.outletQuality, "outletQuality");
    if(defined(expected.outletVolume)) testNumberValue(steamProperties.specificVolume, expected.outletVolume, "outletVolume");
    if(defined(expected.outletSpecificEnthalpy)) testNumberValue(steamProperties.specificEnthalpy, expected.outletSpecificEnthalpy, "outletSpecificEnthalpy");
    if(defined(expected.outletSpecificEntropy)) testNumberValue(steamProperties.specificEntropy, expected.outletSpecificEntropy, "outletSpecificEntropy");
    if(defined(expected.outletTemperature)) testNumberValue(steamProperties.temperature, expected.outletTemperature, "outletTemperature");

    if(prv.isWithDesuperheating()) {
        let prvCast = new Module.PrvCastDesuperheating();
        let prvWith = prvCast.Cast(prv);
        if(prvWith != null) {
            steamProperties = prvWith.getFeedwaterProperties();
            if (defined(expected.feedwaterEnergyFlow)) testNumberValue(prvWith.getFeedwaterEnergyFlow(), expected.feedwaterEnergyFlow, "feedwaterEnergyFlow");
            if (defined(expected.feedwaterMassFlow)) testNumberValue(prvWith.getFeedwaterMassFlow(), expected.feedwaterMassFlow, "feedwaterMassFlow");
            if (defined(expected.feedwaterPressure)) testNumberValue(steamProperties.pressure, expected.feedwaterPressure, "feedwaterPressure");
            if (defined(expected.feedwaterQuality)) testNumberValue(steamProperties.quality, expected.feedwaterQuality, "feedwaterQuality");
            if (defined(expected.feedwaterVolume)) testNumberValue(steamProperties.specificVolume, expected.feedwaterVolume, "feedwaterVolume");
            if (defined(expected.feedwaterSpecificEnthalpy)) testNumberValue(steamProperties.specificEnthalpy, expected.feedwaterSpecificEnthalpy, "feedwaterSpecificEnthalpy");
            if (defined(expected.feedwaterSpecificEntropy)) testNumberValue(steamProperties.specificEntropy, expected.feedwaterSpecificEntropy, "feedwaterSpecificEntropy");
            if (defined(expected.feedwaterTemperature)) testNumberValue(steamProperties.temperature, expected.feedwaterTemperature, "feedwaterTemperature");
        }
        prvCast.delete();
    }
}

function validateOperations(results) {
    SectionHead('Energy And Cost Calculations Domain');

    testNumberValue(results.energyAndCostCalculationsDomain.powerGenerated, 5588284.77, "powerGenerated");
    testNumberValue(results.energyAndCostCalculationsDomain.boilerFuelCost, 514732367.9866, "boilerFuelCost");
    testNumberValue(results.energyAndCostCalculationsDomain.makeupWaterCost, 6628255709.3289, "makeupWaterCost");
    testNumberValue(results.energyAndCostCalculationsDomain.totalOperatingCost,  7143388397.3155, "totalOperatingCost");
    testNumberValue(results.energyAndCostCalculationsDomain.powerGenerationCost,  400320, "powerGenerationCost");
    testNumberValue(results.energyAndCostCalculationsDomain.boilerFuelUsage, 183832988566659.5, "boilerFuelUsage");
    testNumberValue(results.energyAndCostCalculationsDomain.sitePowerImport, 3600000, "sitePowerImport");
    testNumberValue(results.energyAndCostCalculationsDomain.powerDemand, 9188284.77, "powerDemand");
    testNumberValue(results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlow, 6276.7573, "makeupWaterVolumeFlow");
    testNumberValue(results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlowAnnual, 50214058.40, "makeupWaterVolumeFlowAnnual");
}

function validateBoiler(results){
    SectionHead('Boiler');

    let expected = {
        pressure:2.2,
        temperature:644,
        specificEnthalpy:3180.157,
        specificEntropy:6.98,
        quality:1,
        specificVolume: 0.13037,
        massFlow:6939154.63,
        energyFlow:22067600433.75
    };
    validateFluidProperties('Boiler Steam', results.boiler.getSteamProperties(), expected);

    expected = {
        pressure: 2.2,
        temperature: 490.406,
        specificEnthalpy: 930.98,
        specificEntropy: 2.49,
        quality: 0,
        specificVolume: 0.001135002372530348,
        massFlow: 141615.4,
        energyFlow: 131841177.21,
    };
    validateFluidProperties('Boiler Blowdown', results.boiler.getBlowdownProperties(), expected);

    expected = {
        pressure: 0.07,
        temperature: 363.0815,
        specificEnthalpy: 376.68,
        specificEntropy: 1.192,
        quality: 0,
        specificVolume: 0.0010611946777477246,
        massFlow: 7080770.035,
        energyFlow: 2667186575.75,
    };
    validateFluidProperties('Boiler Feed water', results.boiler.getFeedwaterProperties(), expected);

    testNumberValue(results.boiler.getBoilerEnergy(), 19532255035.21, "boilerEnergy");
    testNumberValue(results.boiler.getFuelEnergy(), 22979123570.83, "fuelEnergy");
    testNumberValue(results.boiler.getBlowdownRate(), 2, "blowdownRate");
    testNumberValue(results.boiler.getCombustionEfficiency(), 85, "combustionEff");
}

function validateDeaerator(results){
    SectionHead('Deaerator');

    let expected = {
        energyFlow: 2923708211.85,
        massFlow: 7761776.28,
        pressure: 0.07,
        quality: 0,
        specificEnthalpy: 376.68,
        specificEntropy: 1.192,
        temperature: 363.08,
        specificVolume: 0.001061195
    };
    validateFluidProperties('Deaerator Feed water', results.deaerator.getFeedwaterProperties(), expected);

    expected = {
        energyFlow:  2324044686.068,
        massFlow: 822796.53,
        pressure: 1.5,
        quality: 1,
        specificEnthalpy: 2824.568,
        specificEntropy: 6.513,
        specificVolume: 0.137,
        temperature: 483.395
    };
    validateFluidProperties('Deaerator Inlet Steam', results.deaerator.getInletSteamProperties(), expected);

    expected = {
        energyFlow: 620305327.12,
        massFlow: 6946741.527,
        pressure: 0.07,
        quality: 0,
        specificEnthalpy: 89.29,
        specificEntropy: 0.315,
        specificVolume: 0.001009054,
        temperature: 294.42
    };
    validateFluidProperties('Deaerator Inlet Water', results.deaerator.getInletWaterProperties(), expected);

    expected = {
        energyFlow: 20641801.34,
        massFlow: 7761.776,
        pressure: 0.07,
        quality: 1,
        specificEnthalpy: 2659.42,
        specificEntropy: 7.4789,
        specificVolume: 2.3645,
        temperature: 363.08
    };
    validateFluidProperties('Deaerator Vented Steam', results.deaerator.getVentedSteamProperties(), expected);
}

function validateHeatExchanger(results){
    let  heatExchangerOutput = results.makeupWaterAndCondensateHeaderCalculationsDomain.heatExchangerOutput;

    if(heatExchangerOutput == null) return;

    let expected = {
        pressure:0.101325,
        temperature:287.058,
        specificEnthalpy:58.506,
        specificEntropy:0.208,
        quality:0,
        specificVolume:0.0010013222396414172,
        massFlow:6271642.59,
        energyFlow:366928230.98
    };
    validateFluidProperties('HeatExchanger - Cold Outlet', heatExchangerOutput.coldOutlet, expected);

    expected = {
        pressure:1.5,
        temperature:293.15,
        specificEnthalpy:85.328,
        specificEntropy:0.2962677232029907,
        quality:0,
        specificVolume:0.0010013228612033836,
        massFlow:135338.725,
        energyFlow:11548253.427
    };
    validateFluidProperties('HeatExchanger - Hot Outlet', heatExchangerOutput.hotOutlet, expected);
}

function validateCombinedCondensate(results){
    let expected = {
        pressure:1.5,
        temperature:471.445,
        specificEnthalpy:844.717,
        specificEntropy:2.3147,
        quality:0,
        specificVolume:0.001186,
        massFlow:666299.675,
        energyFlow:562834606.11
    };
    validateFluidProperties('Combined Condensate', results.makeupWaterAndCondensateHeaderCalculationsDomain.combinedCondensate, expected);
}

function validateReturnCondensate(results){
    let expected = {
        energyFlow: 250897925.52,
        massFlow:  666076.58,
        pressure: 0.07,
        quality: 0,
        specificVolume: 0.001019660335144356,
        specificEnthalpy: 376.68,
        specificEntropy: 1.19,
        temperature: 363.08
    };
    validateFluidProperties('Return Condensate', results.makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensate, expected);
}

function validateProcessSteamUsage(results){
    let expected = {
        pressure: 2.2,
        temperature: 642.576,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        quality: undefined,
        specificVolume: undefined,
        massFlow: 2270000,
        energyFlow: 7211737188.13,
        processUsage:5098411442.64
    };
    validateFluidProperties('High Pressure Process Steam Usage', results.processSteamUsageCalculationsDomain.highPressureProcessSteamUsage, expected);

    let steamUsage = results.processSteamUsageCalculationsDomain.mediumPressureProcessUsagePtr;
    if(steamUsage != null) {
        expected = {
            pressure: 1.8,
            temperature: 482.22,
            specificEnthalpy: undefined,
            specificEntropy: undefined,
            quality: undefined,
            specificVolume: undefined,
            massFlow: 2270000,
            energyFlow: 6360441835.33,
            processUsage:4352367355.177
        };
        validateFluidProperties('Medium Pressure Process Steam Usage', steamUsage, expected);
    }

    steamUsage = results.processSteamUsageCalculationsDomain.lowPressureProcessUsagePtr;
    if(steamUsage != null) {
        expected = {
            pressure: 1.5,
            temperature: 483.396,
            specificEnthalpy: undefined,
            specificEntropy: undefined,
            quality: undefined,
            specificVolume: undefined,
            massFlow: 2270000,
            energyFlow: 6411769190.88,
            processUsage:4494261794.32
        };
        validateFluidProperties('Low Pressure Process Steam Usage', steamUsage, expected);
    }
}

function validateCondensate(results){
    let expected = {
        pressure:2.2,
        temperature:490.4058,
        specificEnthalpy:930.98,
        specificEntropy:2.49,
        quality:0,
        specificVolume:0.001135002372530348,
        massFlow:227000,
        energyFlow:211332574.55
    };
    validateFluidProperties('High Pressure Condensate', results.highPressureHeaderCalculationsDomain.highPressureCondensate, expected);

    if(results.mediumPressureHeaderCalculationsDomain != null) {
        expected = {
            pressure: 1.8,
            temperature: 480.27,
            specificEnthalpy:  884.61,
            specificEntropy: 2.3978,
            quality: 0,
            specificVolume: 0.001135002372530348,
            massFlow: 227000,
            energyFlow: 200807448.015
        };
        validateFluidProperties('Medium Pressure Condensate', results.mediumPressureHeaderCalculationsDomain.mediumPressureCondensate, expected);
    }

    if(results.lowPressureHeaderCalculationsDomain != null) {
        expected = {
            pressure: 1.5,
            temperature: 471.445,
            specificEnthalpy: 844.717,
            specificEntropy: 2.3146,
            quality: 0,
            specificVolume: 0.0011538,
            massFlow: 227000,
            energyFlow: 191750739.656
        };
        validateFluidProperties('Low Pressure Condensate', results.lowPressureHeaderCalculationsDomain.lowPressureCondensate, expected);
    }
}

function validateHeaderHeatLoss(results){
    let expectedInlet = {
        pressure:2.2,
        temperature:644,
        specificEnthalpy:3180.157,
        specificEntropy:6.98,
        quality:1,
        specificVolume: 0.13037,
        massFlow:6939154.63,
        energyFlow:22067600433.75
    };
    let expectedOutlet = {
        pressure:2.2,
        temperature:642.575,
        specificEnthalpy:3176.976,
        specificEntropy:6.978,
        quality:1,
        specificVolume:0.13,
        massFlow: 6939154.6344,
        energyFlow:22045532833.313
    };
    validateHeatLoss('High', results.highPressureHeaderCalculationsDomain.highPressureHeaderHeatLoss, 22067600.433746338, expectedInlet, expectedOutlet);

    if(results.mediumPressureHeaderCalculationsDomain != null) {
        expectedInlet = {
            pressure:1.8,
            temperature:483.15,
            specificEnthalpy:2804.76,
            specificEntropy:6.3958,
            quality:1,
            specificVolume:0.111439520680989,
            massFlow:5332623.68770465,
            energyFlow:14956737704.817
        };
        expectedOutlet = {
            pressure:1.8,
            temperature:482.22,
            specificEnthalpy:2801.957,
            specificEntropy:6.39,
            quality:1,
            specificVolume:0.111,
            massFlow:5332623.687,
            energyFlow:14941780967.112
        };
        validateHeatLoss('High', results.mediumPressureHeaderCalculationsDomain.mediumPressureHeaderHeatLoss, 14956737.705, expectedInlet, expectedOutlet);
    }

    if(results.lowPressureHeaderCalculationsDomain != null) {
        expectedInlet = {
            pressure:1.5,
            temperature:484.45,
            specificEnthalpy:2827.395,
            specificEntropy:6.519,
            quality:1,
            specificVolume:0.13715,
            massFlow:3096037.88,
            energyFlow:8753723012.46
        };
        expectedOutlet = {
            pressure:1.5,
            temperature:483.396,
            specificEnthalpy:2824.568,
            specificEntropy:6.51336,
            quality:1,
            specificVolume:0.1367,
            massFlow:3096037.88,
            energyFlow:8744969289.45
        };
        validateHeatLoss('High', results.lowPressureHeaderCalculationsDomain.lowPressureHeaderHeatLoss, 8753723.012, expectedInlet, expectedOutlet);
    }
}

function validateHeatLoss(pressureLevel, heatLoss, heatLossValue, expectedInlet, expectedOutlet){
    SectionHead(pressureLevel + ' Pressure Steam Heat Loss');
    testNumberValue(heatLoss.getHeatLoss(), heatLossValue,"heatLoss");

    validateFluidProperties(pressureLevel + ' Pressure Steam Heat Loss - Inlet', heatLoss.getInletProperties(), expectedInlet);

    validateFluidProperties(pressureLevel + ' Pressure Steam Heat Loss - Outlet', heatLoss.getOutletProperties(), expectedOutlet);
}

function validateHighPressureHeaderSteam(results){
    let expected = {
        pressure:2.2,
        temperature:642.575,
        specificEnthalpy:3176.977,
        specificEntropy:6.97798,
        quality:1,
        specificVolume:0.13,
        massFlow:6939154.63,
        energyFlow:22045532833.31
    };

    validateFluidProperties('High Pressure Header Steam', results.highPressureHeaderCalculationsDomain.highPressureHeaderOutput, expected);
}

function validateMakeupWater(results){
    let expected = {
        pressure: 0.101325,
        temperature: 283.15,
        specificEnthalpy: 42.11872247100606,
        specificEntropy: 0.15107627374941596,
        quality: 0,
        specificVolume: 0.0010002985489353622,
        massFlow: 6274883.941,
        energyFlow:  264290095.23
    };
    validateFluidProperties('Makeup Water', results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWater, expected);
}

function validateMakeupWaterAndCondensate(results){
    let expected = {
        pressure: 0.07,
        temperature: 294.42,
        specificEnthalpy: 89.29,
        specificEntropy: 0.3145,
        quality: 0,
        specificVolume: 0.0010090535069731171,
        massFlow: 6942819.171,
        energyFlow: 619955082.58,
    };
    validateFluidProperties('Makeup Water And Condensate', results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput, expected);
}

function validateCondensingTurbine(results){
    let expected = {
        energyOut: 2134794.337,
        generatorEfficiency: 98,
        inletEnergyFlow: 16202581.348,
        inletPressure: 2.2,
        inletQuality: 1,
        inletVolume: 0.13,
        inletSpecificEnthalpy: 3176.976,
        inletSpecificEntropy: 6.978,
        inletTemperature: 642.575,
        isentropicEfficiency: 65,
        massFlow: 5100,
        outletEnergyFlow: 14067787.011,
        outletPressure: 0.1,
        outletQuality: 1,
        outletVolume: 1.8932,
        outletSpecificEnthalpy: 2758.39,
        outletSpecificEntropy: 7.57,
        outletTemperature: 413.998,
        powerOut:  2092098.45,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    validateTurbineOutput('Condensing Turbine', results.highPressureHeaderCalculationsDomain.condensingTurbine, expected);
}

function validateCondensingTurbineIdeal(results){
    let expected = {
        energyOut:3284298.9797,
        generatorEfficiency:98,
        inletEnergyFlow:16202581.348,
        inletPressure:2.2,
        inletQuality:1,
        inletVolume: 0.13,
        inletSpecificEnthalpy:3176.976,
        inletSpecificEntropy:6.9779,
        inletTemperature:642.575,
        isentropicEfficiency:100,
        massFlow:5100,
        outletEnergyFlow:12918282.368,
        outletPressure:0.1,
        outletQuality:0.937,
        outletVolume:1.587,
        outletSpecificEnthalpy:2532.9965,
        outletSpecificEntropy:6.9779,
        outletTemperature:372.7559,
        powerOut:3218613,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined
    };
    validateTurbineOutput('Condensing Turbine Ideal', results.highPressureHeaderCalculationsDomain.condensingTurbineIdeal, expected);
}

function validateHighPressureToMediumPressureTurbine(results){
    let expected = {
        energyOut: 918.37,
        generatorEfficiency: 98,
        inletEnergyFlow: 79964.27,
        inletPressure: 2.2,
        inletQuality: 1,
        inletVolume: 0.13,
        inletSpecificEnthalpy: 3176.977,
        inletSpecificEntropy: 6.98,
        inletTemperature: 642.5755,
        isentropicEfficiency: 65,
        massFlow: 25.17,
        outletEnergyFlow: 79045.90,
        outletPressure: 1.8,
        outletQuality: 1,
        outletVolume: 0.154,
        outletSpecificEnthalpy: 3140.49,
        outletSpecificEntropy: 7.01,
        outletTemperature: 622.54,
        powerOut: 900,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    validateTurbineOutput('High Pressure To Medium Pressure Turbine', results.highPressureHeaderCalculationsDomain.highToMediumPressureTurbine, expected);
}

function validateHighPressureToMediumPressureTurbineIdeal(results){
    let expected = {
        energyOut: 3306000,
        generatorEfficiency: 98,
        inletEnergyFlow: 287871000,
        inletPressure: 2.2,
        inletQuality: 1,
        inletVolume: 0.13,
        inletSpecificEnthalpy: 3177,
        inletSpecificEntropy: 6.978,
        inletTemperature: 642.6,
        isentropicEfficiency: 100,
        massFlow: 90612,
        outletEnergyFlow: 294565000,
        outletPressure: 1.8,
        outletQuality: 1,
        outletVolume: 0.152,
        outletSpecificEnthalpy: 3120.8,
        outletSpecificEntropy: 6.978,
        outletTemperature: 613.7,
        powerOut: 3239880,
        outletIdealPressure: 1.8,
        outletIdealTemperature: 613.7,
        outletIdealSpecificEnthalpy: 3120.8,
        outletIdealSpecificEntropy: 6.978,
        outletIdealQuality: 1,
        outletIdealVolume: 0.152,
    };
    validateTurbineOutput('High Pressure To Medium Pressure Turbine Ideal', results.highPressureHeaderCalculationsDomain.highToMediumPressureTurbineIdle, expected);
}

function validateHighPressureToLowPressureTurbine(results){
    let expected = {
        energyOut: 3070426.64,
        generatorEfficiency: 98,
        inletEnergyFlow: 142963953.07,
        inletPressure: 2.2,
        inletQuality: 1,
        inletVolume: 0.13,
        inletSpecificEnthalpy: 3176.98,
        inletSpecificEntropy: 6.978,
        inletTemperature: 642.5755,
        isentropicEfficiency: 65,
        massFlow: 45000,
        outletEnergyFlow: 139893526.43,
        outletPressure: 1.5,
        outletQuality: 1,
        outletVolume: 0.18056,
        outletSpecificEnthalpy: 3108.745,
        outletSpecificEntropy: 7.0396,
        outletTemperature: 605.13,
        powerOut: 3009018.11,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    validateTurbineOutput('High Pressure To Low Pressure Turbine', results.highPressureHeaderCalculationsDomain.highToLowPressureTurbine, expected);
}

function validateHighPressureToLowPressureTurbineIdeal(results){
    let expected = {
        energyOut: 4723733.295,
        generatorEfficiency: 98,
        inletEnergyFlow: 142963953.068,
        inletPressure: 2.2,
        inletQuality: 1,
        inletVolume: 0.13,
        inletSpecificEnthalpy: 3176.977,
        inletSpecificEntropy: 6.978,
        inletTemperature: 642.575,
        isentropicEfficiency: 100,
        massFlow: 45000,
        outletEnergyFlow: 138240219.77,
        outletPressure: 1.5,
        outletQuality: 1,
        outletVolume: 0.175,
        outletSpecificEnthalpy: 3072.005,
        outletSpecificEntropy: 6.97799,
        outletTemperature: 588.389,
        powerOut: 4629258.63,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    validateTurbineOutput('High Pressure To Low Pressure Turbine Ideal', results.highPressureHeaderCalculationsDomain.highToLowPressureTurbineIdeal, expected);
}

function validateMediumPressureToLowPressureTurbine(results){
    let expected = {
        energyOut: 496192.056,
        generatorEfficiency: 98,
        inletEnergyFlow: 128890010.76,
        inletPressure: 1.8,
        inletQuality: 1,
        inletVolume: 0.111,
        inletSpecificEnthalpy: 2801.96,
        inletSpecificEntropy: 6.39,
        inletTemperature: 482.22,
        isentropicEfficiency: 30,
        massFlow: 46000,
        outletEnergyFlow: 128393818.70373154,
        outletPressure: 1.5,
        outletQuality: 1,
        outletVolume: 0.132,
        outletSpecificEnthalpy: 2791.17,
        outletSpecificEntropy: 6.44,
        outletTemperature: 471.499,
        powerOut: 486268.215,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    if(results.mediumPressureHeaderCalculationsDomain != null)
        validateTurbineOutput('Medium Pressure To Low Pressure Turbine', results.mediumPressureHeaderCalculationsDomain.mediumToLowPressureTurbine, expected);
}

function validateMediumPressureToLowPressureTurbineIdeal(results){
    let expected = {
        energyOut: 1653973.52,
        generatorEfficiency: 98,
        inletEnergyFlow: 128890010.76,
        inletPressure: 1.8,
        inletQuality: 1,
        inletVolume: 0.111,
        inletSpecificEnthalpy: 2801.96,
        inletSpecificEntropy: 6.39,
        inletTemperature: 482.217,
        isentropicEfficiency: 100,
        massFlow: 46000,
        outletEnergyFlow: 127236037.239,
        outletPressure: 1.5,
        outletQuality: 0.987,
        outletVolume: 0.13,
        outletSpecificEnthalpy: 2766,
        outletSpecificEntropy: 6.39,
        outletTemperature: 471.445,
        powerOut: 1620894.05,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    if(results.mediumPressureHeaderCalculationsDomain != null)
        validateTurbineOutput('Medium Pressure To Low Pressure Turbine Ideal', results.mediumPressureHeaderCalculationsDomain.mediumToLowPressureTurbineIdeal, expected);
}

function validateMediumPressureHeaderSteam(results){
    let expected = {
        pressure: 1.8,
        temperature: 482.2174,
        specificEnthalpy: 2801.957,
        specificEntropy: 6.39,
        quality: 1,
        specificVolume: 0.111,
        massFlow: 5332623.687,
        energyFlow: 14941780967.111,
    };
    if(results.mediumPressureHeaderCalculationsDomain != null)
        validateFluidProperties('Medium Pressure Header Steam', results.mediumPressureHeaderCalculationsDomain.mediumPressureHeaderOutput, expected);
}

function validateLowPressureHeaderSteam(results){
    let expected = {
        pressure: 1.5,
        temperature: 483.396,
        specificEnthalpy: 2824.568,
        specificEntropy: 6.513,
        quality: 1,
        specificVolume: 0.137,
        massFlow: 3096037.88,
        energyFlow: 8744969289.45,
    };
    if(results.lowPressureHeaderCalculationsDomain != null)
        validateFluidProperties('Low Pressure Header Steam', results.lowPressureHeaderCalculationsDomain.lowPressureHeaderOutput, expected);
}

function validateHighPressureToMediumPressurePrv(results){
    let expected = {
        feedwaterEnergyFlow: 266713182.727,
        feedwaterMassFlow: 708062.4690502095,
        feedwaterPressure: 0.07,
        feedwaterQuality: 0,
        feedwaterVolume: 0.00103,
        feedwaterSpecificEnthalpy: 376.68,
        feedwaterSpecificEntropy: 1.19,
        feedwaterTemperature: 363.08,
        inletEnergyFlow: 14674549146.495258,
        inletMassFlow: 4619029.464546394,
        inletPressure: 2.2,
        inletQuality: 1,
        inletVolume: 0.13,
        inletSpecificEnthalpy: 3176.977,
        inletSpecificEntropy: 6.978,
        inletTemperature: 642.5755,
        outletEnergyFlow: 5327091.933596604,
        outletMassFlow: 14941262329.222578,
        outletPressure: 1.8,
        outletQuality: 1,
        outletVolume: 0.111,
        outletSpecificEnthalpy: 2804.77,
        outletSpecificEntropy: 6.396,
        outletTemperature: 483.15,
    };
    if(results.mediumPressureHeaderCalculationsDomain != null)
        validatePrvOutput('High Pressure To Medium Pressure Prv', results.mediumPressureHeaderCalculationsDomain.highToMediumPressurePrv, expected);
}

function validateMediumPressureToLowPressurePrv(results){
    let expected = {
        feedwaterEnergyFlow: -10191546.627202913,
        feedwaterMassFlow: -27056.22419749442,
        feedwaterPressure: 0.07,
        feedwaterQuality: 0,
        feedwaterVolume: 0.001,
        feedwaterSpecificEnthalpy: 376.68,
        feedwaterSpecificEntropy: 1.192,
        feedwaterTemperature: 363.08,
        inletEnergyFlow: 8452449121.022741,
        inletMassFlow: 3016623.6877046498,
        inletPressure: 1.8,
        inletQuality: 1,
        inletVolume: 0.111,
        inletSpecificEnthalpy: 2801.96,
        inletSpecificEntropy: 6.39,
        inletTemperature: 482.217,
        outletEnergyFlow: 2989567.46,
        outletMassFlow: 8442257574.395539,
        outletPressure: 1.5,
        outletQuality: 1,
        outletVolume: 0.1366,
        outletSpecificEnthalpy: 2823.906,
        outletSpecificEntropy: 6.512,
        outletTemperature: 483.15,
    };
    if(results.lowPressureHeaderCalculationsDomain != null)
        validatePrvOutput('Medium Pressure To Low Pressure Prv', results.lowPressureHeaderCalculationsDomain.lowPressurePrv, expected);
}

function validateBlowdownFlashTank(results){
    if(results.blowdownFlashTank != null) {
        let expected = {
            energyFlow: 131841177.21,
            massFlow: 141615.4,
            pressure: 2.2,
            quality: 0,
            specificVolume: 0.001135002372530348,
            specificEnthalpy: 930.98,
            specificEntropy: 2.49,
            temperature: 490.4057
        };
        validateFluidProperties('Blowdown Flash Tank - inletWater', results.blowdownFlashTank.getInletWaterProperties(), expected);

        expected = {
            energyFlow: 17518266.52,
            massFlow: 6276.675,
            pressure: 1.5,
            quality: 1,
            specificVolume: 0.1317,
            specificEnthalpy: 2791.01,
            specificEntropy:  6.44,
            temperature: 471.445
        };
        validateFluidProperties('Blowdown Flash Tank - outletGas', results.blowdownFlashTank.getOutletGasSaturatedProperties(), expected);

        expected = {
            energyFlow: 114322910.6866,
            massFlow: 135338.725,
            pressure: 1.5,
            quality: 0,
            specificVolume: 0.001135002372530348,
            specificEnthalpy: 844.717,
            specificEntropy: 2.31468,
            temperature: 471.445
        };
        validateFluidProperties('Blowdown Flash Tank - outletLiquid', results.blowdownFlashTank.getOutletLiquidSaturatedProperties(), expected);
    }
}

function validateCondensateFlashTank(results){
    let flashTank = results.makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensateCalculationsDomain.condensateFlashTank;

    if(flashTank == null) return;

    let expected = {
        energyFlow: 251491228.92,
        massFlow:  666299.675,
        pressure: 1.5,
        quality: 0,
        specificVolume: 0.001019660335144356,
        specificEnthalpy: 377.44,
        specificEntropy: 1.1898,
        temperature: 363
    };
    validateFluidProperties('Condensate Flash Tank - inletWater', flashTank.getInletWaterProperties(), expected);

    expected = {
        energyFlow: 593303.404,
        massFlow: 223.095,
        pressure: 0.07,
        quality: 1,
        specificVolume: 2.3648,
        specificEnthalpy: 2659.417,
        specificEntropy: 7.4789,
        temperature: 363.08
    };
    validateFluidProperties('Condensate Flash Tank - outletGas', flashTank.getOutletGasSaturatedProperties(), expected);

    expected = {
        energyFlow: 250897925.52,
        massFlow:  666076.58,
        pressure: 0.07,
        quality: 0,
        specificVolume: 0.001019660335144356,
        specificEnthalpy: 376.68,
        specificEntropy: 1.19,
        temperature: 363.08
    };
    validateFluidProperties('Condensate Flash Tank - outletLiquid', flashTank.getOutletLiquidSaturatedProperties(), expected);
}

function validateHighPressureCondensateFlashTank(results){
    let flashTank = results.highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;

    if(flashTank == null) return;

    let expected = {
        energyFlow: 211332574.55,
        massFlow: 227000,
        pressure: 2.2,
        quality: 0,
        specificVolume: 0.00118,
        specificEnthalpy: 930.98,
        specificEntropy: 2.49,
        temperature: 490.4057
    };
    validateFluidProperties('High Pressure Condensate Flash Tank - inletWater', flashTank.getInletWaterProperties(), expected);

    expected = {
        energyFlow: 15396329.69,
        massFlow: 5506.58,
        pressure: 1.8,
        quality: 1,
        specificVolume: 0.11,
        specificEnthalpy: 2795.9855,
        specificEntropy: 6.3776,
        temperature: 480.27
    };
    validateFluidProperties('High Pressure Condensate Flash Tank - outletGas', flashTank.getOutletGasSaturatedProperties(), expected);

    expected = {
        energyFlow: 195936244.86,
        massFlow: 221493.42,
        pressure: 1.8,
        quality: 0,
        specificVolume: 0.00116,
        specificEnthalpy: 884.61,
        specificEntropy: 2.398,
        temperature: 480.269
    };
    validateFluidProperties('High Pressure Condensate Flash Tank - outletLiquid', flashTank.getOutletLiquidSaturatedProperties(), expected);
}

function validateMediumPressureCondensateFlashTank(results){
    if(results.lowPressureHeaderCalculationsDomain == null) return;

    let flashTank = results.lowPressureHeaderCalculationsDomain.lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;

    if(flashTank == null) return;

    let expected = {
        energyFlow: 396743692.87,
        massFlow: 448493.42,
        pressure: 1.5,
        quality: 0.02,
        specificVolume: 0.0038,
        specificEnthalpy: 884.61,
        specificEntropy: 2.399,
        temperature: 471.445
    };
    validateFluidProperties('Medium Pressure Condensate Flash Tank - inletWater', flashTank.getInletWaterProperties(), expected);

    expected = {
        energyFlow: 25659826.414,
        massFlow: 9193.74,
        pressure: 1.5,
        quality: 1,
        specificVolume: 0.1317,
        specificEnthalpy: 2791.01,
        specificEntropy: 6.44,
        temperature: 471.445
    };
    validateFluidProperties('Medium Pressure Condensate Flash Tank - outletGas', flashTank.getOutletGasSaturatedProperties(), expected);

    expected = {
        energyFlow: 371083866.458,
        massFlow: 439299.675,
        pressure: 1.5,
        quality: 0,
        specificVolume: 0.0015,
        specificEnthalpy: 844.7169,
        specificEntropy: 2.31,
        temperature: 471.445
    };
    validateFluidProperties('Medium Pressure Condensate Flash Tank - outletLiquid', flashTank.getOutletLiquidSaturatedProperties(), expected);
}

function validatePowerBalanceCheckerCalculationsDomain(results){
    let pbCheck = results.powerBalanceCheckerCalculationsDomain;
    let lowPrVentedCalc = pbCheck.lowPressureVentedSteamCalculationsDomain;

    let expected = {
        density: 7.314,
        energyFlow: 9155412.5,
        massFlow: 3241.35,
        pressure: 1.5,
        quality: 1,
        specificVolume: 0.137,
        specificEnthalpy: 2824.568,
        specificEntropy: 6.513,
        temperature: 483.396
    };
    validateFluidProperties('Power Balance Checker Calculations Domain - Fluid Properties', pbCheck.lowPressureVentedSteam, expected);

    logMessage('Steam Modeler: Test# 1 - Power Balance Checker Calculations Domain Results ', true);
    testNumberValue(pbCheck.steamBalance, 4.6567e-10, "Steam Balance");

    if(lowPrVentedCalc != null) {
        logMessage('Steam Modeler: Test# 1 - Power Balance Checker Calculations Domain Low Pressure Vented Steam Calculations Domain Results ', true);
        testNumberValue(lowPrVentedCalc.lowPressureVentedSteam, 3241.35, "Low Pressure Vented Steam");

        if(lowPrVentedCalc.makeupWaterVolumeFlowCalculationsDomain != null) {
            testNumberValue(lowPrVentedCalc.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlow, 6276.7573, "Makeup Water Volume Flow");
            testNumberValue(lowPrVentedCalc.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlowAnnual, 50214058.404, "Makeup Water Volume Flow Annual");
        }

        let expected = {
            density: 999.7,
            energyFlow: 264290095.231,
            massFlow: 6274883.9406,
            pressure: 0.101,
            quality: 0,
            specificVolume: 0.001,
            specificEnthalpy: 42.119,
            specificEntropy: 0.1511,
            temperature: 283.15
        };
        validateFluidProperties('Power Balance Checker Calculations Domain Makeup Water - Fluid Properties', lowPrVentedCalc.makeupWater, expected);

        expected = {
            density: 997.92,
            energyFlow: 619955082.577,
            massFlow: 6942819.171,
            pressure: 0.07,
            quality: 0,
            specificVolume: 0.001,
            specificEnthalpy: 89.294,
            specificEntropy: 0.314,
            temperature: 294.419
        };
        validateFluidProperties('Power Balance Checker Calculations Domain Makeup Water And Condensate Header Output Updated - Fluid Properties', lowPrVentedCalc.makeupWaterAndCondensateHeaderOutputUpdated, expected);
    }
}

function steamModeler() {
    let boilerInput = {
        fuelType: 1,
        fuel: 1,
        combustionEfficiency: 85,
        blowdownRate: 2,
        blowdownFlashed: true,
        preheatMakeupWater: true,
        steamTemperature: 644,
        deaeratorVentRate: 0.1,
        deaeratorPressure: 0.07,
        approachTemperature: 10,
    };

    let header1 = {
        pressure: 2.2,
        processSteamUsage: 2270000,
        condensationRecoveryRate: 10,
        heatLoss: 0.1,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 1,

        condensateReturnTemperature: 363,
        flashCondensateReturn: true,
    };
    let header2 = {
        pressure: 1.8,
        processSteamUsage: 2270000,
        condensationRecoveryRate: 10,
        heatLoss: 0.1,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 483.15,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    let header3 = {
        pressure: 1.5,
        processSteamUsage: 2270000,
        condensationRecoveryRate: 10,
        heatLoss: 0.1,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 483.15,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    let headerInput = {
        highPressureHeader: header1,
        mediumPressureHeader: header2,
        lowPressureHeader: header3,
    };

    let operationsInput = {
        sitePowerImport: 3600000,
        makeUpWaterTemperature: 283.15,
        operatingHoursPerYear: 8000,
        fuelCosts: 0.0000028,
        electricityCosts: 0.0000139,
        makeUpWaterCosts: 132,
    };

    let condensingTurbine = {
        isentropicEfficiency: 65,
        generationEfficiency: 98,
        condenserPressure: 0.1,
        operationType: Module.CondensingTurbineOperation.STEAM_FLOW,
        operationValue: 5100,
        useTurbine: true,
    };
    let highToLowTurbine = {
        isentropicEfficiency: 65,
        generationEfficiency: 98,
        condenserPressure: 0.1,
        operationType: Module.PressureTurbineOperation.STEAM_FLOW,
        operationValue1: 45000,
        operationValue2: 1,
        useTurbine: true,
    };
    let highToMediumTurbine = {
        isentropicEfficiency: 65,
        generationEfficiency: 98,
        condenserPressure: 3,
        operationType: Module.PressureTurbineOperation.POWER_RANGE,
        operationValue1: 800,
        operationValue2: 900,
        useTurbine: true,
    };
    let mediumToLowTurbine = {
        isentropicEfficiency: 30,
        generationEfficiency: 98,
        condenserPressure: 0.1,
        operationType: Module.PressureTurbineOperation.FLOW_RANGE,
        operationValue1: 40000,
        operationValue2: 46000,
        useTurbine: true,
    };
    let turbineInput = {
        condensingTurbine: condensingTurbine,
        highToLowTurbine: highToLowTurbine,
        highToMediumTurbine: highToMediumTurbine,
        mediumToLowTurbine: mediumToLowTurbine,
    };

    let modelerInput = {
        isBaselineCalc: true,
        baselinePowerDemand: 1,
        boilerInput: boilerInput,
        headerInput: headerInput,
        operationsInput: operationsInput,
        turbineInput: turbineInput,
    };

    let boilerInputObj = new Module.BoilerInput(boilerInput.fuelType, boilerInput.fuel, boilerInput.combustionEfficiency, boilerInput.blowdownRate, boilerInput.blowdownFlashed, boilerInput.preheatMakeupWater, boilerInput.steamTemperature, boilerInput.deaeratorVentRate, boilerInput.deaeratorPressure, boilerInput.approachTemperature);
    let highPressureHeaderObj = new Module.HeaderWithHighestPressure(header1.pressure, header1.processSteamUsage, header1.condensationRecoveryRate, header1.heatLoss, header1.condensateReturnTemperature, header1.flashCondensateReturn);
    let medPressureHeaderObj = new Module.HeaderNotHighestPressure(header2.pressure, header2.processSteamUsage, header2.condensationRecoveryRate, header2.heatLoss, header2.flashCondensateIntoHeader, header2.desuperheatSteamIntoNextHighest, header2.desuperheatSteamTemperature);
    let lowPressureHeaderObj = new Module.HeaderNotHighestPressure(header3.pressure, header3.processSteamUsage, header3.condensationRecoveryRate, header3.heatLoss, header3.flashCondensateIntoHeader, header3.desuperheatSteamIntoNextHighest, header3.desuperheatSteamTemperature);
    let headerInputObj = new Module.HeaderInput(highPressureHeaderObj, medPressureHeaderObj, lowPressureHeaderObj);
    let operationsInputObj = new Module.OperationsInput(operationsInput.sitePowerImport, operationsInput.makeUpWaterTemperature, operationsInput.operatingHoursPerYear, operationsInput.fuelCosts, operationsInput.electricityCosts, operationsInput.makeUpWaterCosts);

    let condensingTurbineObj = new Module.CondensingTurbine(condensingTurbine.isentropicEfficiency, condensingTurbine.generationEfficiency, condensingTurbine.condenserPressure, condensingTurbine.operationType, condensingTurbine.operationValue, condensingTurbine.useTurbine);
    let highToLowTurbineObj = new Module.PressureTurbine(highToLowTurbine.isentropicEfficiency, highToLowTurbine.generationEfficiency, highToLowTurbine.operationType, highToLowTurbine.operationValue1, highToLowTurbine.operationValue2, highToLowTurbine.useTurbine);
    let highToMediumTurbineObj = new Module.PressureTurbine(highToMediumTurbine.isentropicEfficiency, highToMediumTurbine.generationEfficiency, highToMediumTurbine.operationType, highToMediumTurbine.operationValue1, highToMediumTurbine.operationValue2, highToMediumTurbine.useTurbine);
    let mediumToLowTurbineObj = new Module.PressureTurbine(mediumToLowTurbine.isentropicEfficiency, mediumToLowTurbine.generationEfficiency, mediumToLowTurbine.operationType, mediumToLowTurbine.operationValue1, mediumToLowTurbine.operationValue2, mediumToLowTurbine.useTurbine);
    let turbineInputObj = new Module.TurbineInput(condensingTurbineObj, highToLowTurbineObj, highToMediumTurbineObj, mediumToLowTurbineObj);

    let steamModelerInput = new Module.SteamModelerInput(modelerInput.isBaselineCalc, modelerInput.baselinePowerDemand, boilerInputObj, headerInputObj, operationsInputObj, turbineInputObj)

    let modeler = new Module.SteamModeler();
    validateOutput(modeler.model(steamModelerInput));
    
    modeler.delete();
    boilerInputObj.delete();
    highPressureHeaderObj.delete();
    headerInputObj.delete();
    operationsInputObj.delete();
    condensingTurbineObj.delete();
    highToLowTurbineObj.delete();
    highToMediumTurbineObj.delete();
    mediumToLowTurbineObj.delete();
    turbineInputObj.delete();
    steamModelerInput.delete();
}

steamModeler();
