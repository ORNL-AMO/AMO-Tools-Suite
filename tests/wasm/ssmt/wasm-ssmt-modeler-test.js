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
        let prvWith = PrvCastDesuperheating.Cast(prv);
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
    }
}

function validateOperations(results) {
    SectionHead('Energy And Cost Calculations Domain');

    testNumberValue(results.energyAndCostCalculationsDomain.powerGenerated, 1, "powerGenerated");
    testNumberValue(results.energyAndCostCalculationsDomain.boilerFuelCost, 3270792.6312980186, "boilerFuelCost");
    testNumberValue(results.energyAndCostCalculationsDomain.makeupWaterCost, 62865.242016338656, "makeupWaterCost");
    testNumberValue(results.energyAndCostCalculationsDomain.totalOperatingCost, 5335257.873314357, "totalOperatingCost");
    testNumberValue(results.energyAndCostCalculationsDomain.powerGenerationCost, 2001600.0000000002, "powerGenerationCost");
    testNumberValue(results.energyAndCostCalculationsDomain.boilerFuelUsage, 597077880850.3137, "boilerFuelUsage");
    testNumberValue(results.energyAndCostCalculationsDomain.sitePowerImport, 18000000, "sitePowerImport");
    testNumberValue(results.energyAndCostCalculationsDomain.powerDemand, 18000001, "powerDemand");
    testNumberValue(results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlow, 11.906295836427775, "makeupWaterVolumeFlow");
    testNumberValue(results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain.makeupWaterVolumeFlowAnnual, 95250.3666914222, "makeupWaterVolumeFlowAnnual");
}

function validateBoiler(results){
    SectionHead('Boiler');

    let expected = {
        pressure: 1.136,
        temperature: 514.2,
        specificEnthalpy: 2917.838793476974,
        specificEntropy: 6.8211883441380285,
        quality: 1,
        specificVolume: 0.19960611293064956,
        massFlow: 26261.30665156052,
        energyFlow: 76626259.31531818,
    };
    validateFluidProperties('Boiler Steam', results.boiler.getSteamProperties(), expected);

    expected = {
        pressure: 1.136,
        temperature: 458.65273574845287,
        specificEnthalpy: 787.5557825431341,
        specificEntropy: 2.1926588668498703,
        quality: 0,
        specificVolume: 0.001135002372530348,
        massFlow: 535.9450337053167,
        energyFlow: 422086.61041989713,
    };
    validateFluidProperties('Boiler Blowdown', results.boiler.getBlowdownProperties(), expected);

    expected = {
        pressure: 0.204747,
        temperature: 394.1047658380901,
        specificEnthalpy: 507.8439104587324,
        specificEntropy: 1.5381113180769446,
        quality: 0,
        specificVolume: 0.0010611946777477246,
        massFlow: 26797.251685265837,
        energyFlow: 13608821.08539226,
    };
    validateFluidProperties('Boiler Feed water', results.boiler.getFeedwaterProperties(), expected);

    testNumberValue(results.boiler.getBoilerEnergy(), 63439524.84034582, "boilerEnergy");
    testNumberValue(results.boiler.getFuelEnergy(), 74634735.10628921, "fuelEnergy");
    testNumberValue(results.boiler.getBlowdownRate(), 2, "blowdownRate");
    testNumberValue(results.boiler.getCombustionEfficiency(), 85, "combustionEff");
}

function validateDeaerator(results){
    SectionHead('Deaerator');

    let expected = {
        energyFlow: 13608821.09,
        massFlow: 26797.25169,
        pressure: 0.204747,
        quality: 0,
        specificEnthalpy: 507.8439105,
        specificEntropy: 1.538111318,
        temperature: 394.1047658,
        specificVolume: 0.001061195
    };
    validateFluidProperties('Deaerator Feed water', results.deaerator.getFeedwaterProperties(), expected);

    expected = {
        energyFlow: 9413116.877,
        massFlow: 3229.287182,
        pressure: 1.136,
        quality: 1,
        specificEnthalpy: 2914.920955,
        specificEntropy: 6.815506757,
        specificVolume: 0.199008043,
        temperature: 512.9220161
    };
    validateFluidProperties('Deaerator Inlet Steam', results.deaerator.getInletSteamProperties(), expected);

    expected = {
        energyFlow: 4268252.883,
        massFlow: 23594.76175,
        pressure: 0.204747,
        quality: 0,
        specificEnthalpy: 180.8983251,
        specificEntropy: 0.614238341,
        specificVolume: 0.001009054,
        temperature: 316.3049435
    };
    validateFluidProperties('Deaerator Inlet Water', results.deaerator.getInletWaterProperties(), expected);

    expected = {
        energyFlow: 72548.67398,
        massFlow: 26.79725169,
        pressure: 0.204747,
        quality: 1,
        specificEnthalpy: 2707.317707,
        specificEntropy: 7.119028215,
        specificVolume: 0.866496191,
        temperature: 394.1047658
    };
    validateFluidProperties('Deaerator Vented Steam', results.deaerator.getVentedSteamProperties(), expected);
}

function validateHeatExchanger(results){
    let  heatExchangerOutput = results.makeupWaterAndCondensateHeaderCalculationsDomain.heatExchangerOutput;

    if(heatExchangerOutput == null) return;

    let expected = {
        pressure:0.101325,
        temperature:290.69887071203436,
        specificEnthalpy:73.75333181427386,
        specificEntropy:0.26133728484659247,
        quality:0,
        specificVolume:0.0010013222396414172,
        massFlow:11902.742285390581,
        energyFlow:877866.9012742
    };
    validateFluidProperties('HeatExchanger - Cold Outlet', heatExchangerOutput.coldOutlet, expected);

    expected = {
        pressure:1.136,
        temperature:293.15,
        specificEnthalpy:84.9863423364548,
        specificEntropy:0.2962677232029907,
        quality:0,
        specificVolume:0.0010013228612033836,
        massFlow:535.9450337053167,
        energyFlow:45548.008108002854
    };
    validateFluidProperties('HeatExchanger - Hot Outlet', heatExchangerOutput.hotOutlet, expected);
}

function validateCombinedCondensate(results){
    let expected = {
        pressure:1.136,
        temperature:458.65273574845287,
        specificEnthalpy:787.5557825431341,
        specificEntropy:2.1926588668498703,
        quality:0,
        specificVolume:0.001135002372530348,
        massFlow:11340,
        energyFlow:8930882.57403914
    };
    validateFluidProperties('Combined Condensate', results.makeupWaterAndCondensateHeaderCalculationsDomain.combinedCondensate, expected);
}

function validateReturnCondensate(results){
    let expected = {
        pressure:1.136,
        temperature:338.6999999999999,
        specificEnthalpy:275.300414292446,
        specificEntropy:0.8997137118482235,
        quality:0,
        specificVolume:0.001019660335144356,
        massFlow:11340,
        energyFlow:3121906.698076338
    };
    validateFluidProperties('Return Condensate', results.makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensate, expected);
}

function validateProcessSteamUsage(results){
    let expected = {
        pressure: 1.136,
        temperature: 512.922016091814,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        quality: undefined,
        specificVolume: undefined,
        massFlow: 22680,
        energyFlow: 66110407.252221674,
        processUsage:48248642.10414339
    };
    validateFluidProperties('High Pressure Process Steam Usage', results.processSteamUsageCalculationsDomain.highPressureProcessSteamUsage, expected);

    let steamUsage = results.processSteamUsageCalculationsDomain.mediumPressureProcessUsagePtr;
    if(steamUsage != null) {
        expected = {
            pressure: 1.136,
            temperature: 512.922016091814,
            specificEnthalpy: undefined,
            specificEntropy: undefined,
            quality: undefined,
            specificVolume: undefined,
            massFlow: 22680,
            energyFlow: 66110407.252221674,
            processUsage:48248642.10414339
        };
        validateFluidProperties('Medium Pressure Process Steam Usage', steamUsage, expected);
    }

    steamUsage = results.processSteamUsageCalculationsDomain.lowPressureProcessUsagePtr;
    if(steamUsage != null) {
        expected = {
            pressure: 1.136,
            temperature: 512.922016091814,
            specificEnthalpy: undefined,
            specificEntropy: undefined,
            quality: undefined,
            specificVolume: undefined,
            massFlow: 22680,
            energyFlow: 66110407.252221674,
            processUsage:48248642.10414339
        };
        validateFluidProperties('Low Pressure Process Steam Usage', steamUsage, expected);
    }
}

function validateCondensate(results){
    let expected = {
        pressure:1.136,
        temperature:458.65273574845287,
        specificEnthalpy:787.5557825431341,
        specificEntropy:2.1926588668498703,
        quality:0,
        specificVolume:0.001135002372530348,
        massFlow:11340,
        energyFlow:8930882.57403914
    };
    validateFluidProperties('High Pressure Condensate', results.highPressureHeaderCalculationsDomain.highPressureCondensate, expected);

    if(results.mediumPressureHeaderCalculationsDomain != null) {
        expected = {
            pressure: 1.136,
            temperature: 458.65273574845287,
            specificEnthalpy: 787.5557825431341,
            specificEntropy: 2.1926588668498703,
            quality: 0,
            specificVolume: 0.001135002372530348,
            massFlow: 11340,
            energyFlow: 8930882.57403914
        };
        validateFluidProperties('Medium Pressure Condensate', results.mediumPressureHeaderCalculationsDomain.mediumPressureCondensate, expected);
    }

    if(results.lowPressureHeaderCalculationsDomain != null) {
        expected = {
            pressure: 1.136,
            temperature: 458.65273574845287,
            specificEnthalpy: 787.5557825431341,
            specificEntropy: 2.1926588668498703,
            quality: 0,
            specificVolume: 0.001135002372530348,
            massFlow: 11340,
            energyFlow: 8930882.57403914
        };
        validateFluidProperties('Low Pressure Condensate', results.lowPressureHeaderCalculationsDomain.lowPressureCondensate, expected);
    }
}

function validateHeaderHeatLoss(results){
    let expectedInlet = {
        pressure:1.136,
        temperature:514.1999999999996,
        specificEnthalpy:2917.8387934769735,
        specificEntropy:6.821188344138027,
        quality:1,
        specificVolume:0.1996061129306493,
        massFlow:26261.30665156052,
        energyFlow:76626259.31531817
    };
    let expectedOutlet = {
        pressure:1.136,
        temperature:512.922016091814,
        specificEnthalpy:2914.9209546834954,
        specificEntropy:6.81550675722266,
        quality:1,
        specificVolume:0.19900804292495916,
        massFlow:26261.30665156052,
        energyFlow:76549633.05600286
    };
    validateHeatLoss('High', results.highPressureHeaderCalculationsDomain.highPressureHeaderHeatLoss, 76626.25931531191, expectedInlet, expectedOutlet);

    if(results.mediumPressureHeaderCalculationsDomain != null) {
        expectedInlet = {
            pressure:1.136,
            temperature:514.1999999999996,
            specificEnthalpy:2917.8387934769735,
            specificEntropy:6.821188344138027,
            quality:1,
            specificVolume:0.1996061129306493,
            massFlow:26261.30665156052,
            energyFlow:76626259.31531817
        };
        expectedOutlet = {
            pressure:1.136,
            temperature:512.922016091814,
            specificEnthalpy:2914.9209546834954,
            specificEntropy:6.81550675722266,
            quality:1,
            specificVolume:0.19900804292495916,
            massFlow:26261.30665156052,
            energyFlow:76549633.05600286
        };
        validateHeatLoss('High', results.mediumPressureHeaderCalculationsDomain.mediumPressureHeaderHeatLoss, 76626.25931531191, expectedInlet, expectedOutlet);
    }

    if(results.lowPressureHeaderCalculationsDomain != null) {
        expectedInlet = {
            pressure:1.136,
            temperature:514.1999999999996,
            specificEnthalpy:2917.8387934769735,
            specificEntropy:6.821188344138027,
            quality:1,
            specificVolume:0.1996061129306493,
            massFlow:26261.30665156052,
            energyFlow:76626259.31531817
        };
        expectedOutlet = {
            pressure:1.136,
            temperature:512.922016091814,
            specificEnthalpy:2914.9209546834954,
            specificEntropy:6.81550675722266,
            quality:1,
            specificVolume:0.19900804292495916,
            massFlow:26261.30665156052,
            energyFlow:76549633.05600286
        };
        validateHeatLoss('High', results.lowPressureHeaderCalculationsDomain.lowPressureHeaderHeatLoss, 76626.25931531191, expectedInlet, expectedOutlet);
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
        pressure: 1.136,
        temperature: 512.922016091814,
        specificEnthalpy: 2914.9209546834954,
        specificEntropy: 6.81550675722266,
        quality: 1,
        specificVolume: 0.19900804292495916,
        massFlow: 26261.30665156052,
        energyFlow: 76549633.05600286,
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
        massFlow: 11902.742285390581,
        energyFlow: 501328.2989622743,
    };
    validateFluidProperties('Makeup Water', results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWater, expected);
}

function validateMakeupWaterAndCondensate(results){
    let expected = {
        pressure: 0.204747,
        temperature: 316.30494350601737,
        specificEnthalpy: 180.8983251038269,
        specificEntropy: 0.6142383405729469,
        quality: 0,
        specificVolume: 0.0010090535069731171,
        massFlow: 23594.761880492584,
        energyFlow: 4268252.905404726,
    };
    validateFluidProperties('Makeup Water And Condensate', results.makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput, expected);
}

function validateCondensingTurbine(results){
    let expected = {
        energyOut: 100,
        generatorEfficiency: 1,
        inletEnergyFlow: 1026109.2942220301,
        inletPressure: 1.136,
        inletQuality: 1,
        inletVolume: 0.199008042924959,
        inletSpecificEnthalpy: 2914.920954683495,
        inletSpecificEntropy: 6.815506757222659,
        inletTemperature: 512.9220160918137,
        isentropicEfficiency: 1,
        massFlow: 352.01959510200373,
        outletEnergyFlow: 1026009.2942220301,
        outletPressure: 1,
        outletQuality: 1,
        outletVolume: 0.22607153693359688,
        outletSpecificEnthalpy: 2914.636879588268,
        outletSpecificEntropy: 6.871299121498748,
        outletTemperature: 510.32081495211025,
        powerOut: 1,
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
        energyOut:100,
        generatorEfficiency:1,
        inletEnergyFlow:10261.092942223258,
        inletPressure:1.136,
        inletQuality:1,
        inletVolume:0.199008042924959,
        inletSpecificEnthalpy:2914.920954683495,
        inletSpecificEntropy:6.815506757222659,
        inletTemperature:512.9220160918137,
        isentropicEfficiency:100,
        massFlow:3.520195951021052,
        outletEnergyFlow:10161.092942223258,
        outletPressure:1,
        outletQuality:1,
        outletVolume:0.21951743334913756,
        outletSpecificEnthalpy:2886.51344516091,
        outletSpecificEntropy:6.815506757222662,
        outletTemperature:497.91639145694285,
        powerOut:1,
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
        energyOut: undefined,
        generatorEfficiency: undefined,
        inletEnergyFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        isentropicEfficiency: undefined,
        massFlow: undefined,
        outletEnergyFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
        powerOut: undefined,
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
        energyOut: undefined,
        generatorEfficiency: undefined,
        inletEnergyFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        isentropicEfficiency: undefined,
        massFlow: undefined,
        outletEnergyFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
        powerOut: undefined,
        outletIdealPressure: undefined,
        outletIdealTemperature: undefined,
        outletIdealSpecificEnthalpy: undefined,
        outletIdealSpecificEntropy: undefined,
        outletIdealQuality: undefined,
        outletIdealVolume: undefined,
    };
    validateTurbineOutput('High Pressure To Medium Pressure Turbine Ideal', results.highPressureHeaderCalculationsDomain.highToMediumPressureTurbineIdle, expected);
}

function validateHighPressureToLowPressureTurbine(results){
    let expected = {
        energyOut: undefined,
        generatorEfficiency: undefined,
        inletEnergyFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        isentropicEfficiency: undefined,
        massFlow: undefined,
        outletEnergyFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
        powerOut: undefined,
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
        energyOut: undefined,
        generatorEfficiency: undefined,
        inletEnergyFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        isentropicEfficiency: undefined,
        massFlow: undefined,
        outletEnergyFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
        powerOut: undefined,
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
        energyOut: undefined,
        generatorEfficiency: undefined,
        inletEnergyFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        isentropicEfficiency: undefined,
        massFlow: undefined,
        outletEnergyFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
        powerOut: undefined,
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
        energyOut: undefined,
        generatorEfficiency: undefined,
        inletEnergyFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        isentropicEfficiency: undefined,
        massFlow: undefined,
        outletEnergyFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
        powerOut: undefined,
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
        pressure: undefined,
        temperature: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        quality: undefined,
        specificVolume: undefined,
        massFlow: undefined,
        energyFlow: undefined,
    };
    if(results.mediumPressureHeaderCalculationsDomain != null)
        validateFluidProperties('Medium Pressure Header Steam', results.mediumPressureHeaderCalculationsDomain.mediumPressureHeaderOutput, expected);
}

function validateLowPressureHeaderSteam(results){
    let expected = {
        pressure: undefined,
        temperature: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        quality: undefined,
        specificVolume: undefined,
        massFlow: undefined,
        energyFlow: undefined,
    };
    if(results.lowPressureHeaderCalculationsDomain != null)
        validateFluidProperties('Low Pressure Header Steam', results.lowPressureHeaderCalculationsDomain.lowPressureHeaderOutput, expected);
}

function validateHighPressureToMediumPressurePrv(results){
    let expected = {
        feedwaterEnergyFlow: undefined,
        feedwaterMassFlow: undefined,
        feedwaterPressure: undefined,
        feedwaterQuality: undefined,
        feedwaterVolume: undefined,
        feedwaterSpecificEnthalpy: undefined,
        feedwaterSpecificEntropy: undefined,
        feedwaterTemperature: undefined,
        inletEnergyFlow: undefined,
        inletMassFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        outletEnergyFlow: undefined,
        outletMassFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
    };
    if(results.mediumPressureHeaderCalculationsDomain != null)
        validatePrvOutput('High Pressure To Medium Pressure Prv', results.mediumPressureHeaderCalculationsDomain.highToMediumPressurePrv, expected);
}

function validateMediumPressureToLowPressurePrv(results){
    let expected = {
        feedwaterEnergyFlow: undefined,
        feedwaterMassFlow: undefined,
        feedwaterPressure: undefined,
        feedwaterQuality: undefined,
        feedwaterVolume: undefined,
        feedwaterSpecificEnthalpy: undefined,
        feedwaterSpecificEntropy: undefined,
        feedwaterTemperature: undefined,
        inletEnergyFlow: undefined,
        inletMassFlow: undefined,
        inletPressure: undefined,
        inletQuality: undefined,
        inletVolume: undefined,
        inletSpecificEnthalpy: undefined,
        inletSpecificEntropy: undefined,
        inletTemperature: undefined,
        outletEnergyFlow: undefined,
        outletMassFlow: undefined,
        outletPressure: undefined,
        outletQuality: undefined,
        outletVolume: undefined,
        outletSpecificEnthalpy: undefined,
        outletSpecificEntropy: undefined,
        outletTemperature: undefined,
    };
    if(results.lowPressureHeaderCalculationsDomain != null)
        validatePrvOutput('Medium Pressure To Low Pressure Prv', results.lowPressureHeaderCalculationsDomain.lowPressurePrv, expected);
}

function validateBlowdownFlashTank(results){
    if(results.blowdownFlashTank != null) {
        let expected = {
            energyFlow: 422086.61041989713,
            massFlow: 535.9450337053167,
            pressure: 1.136,
            quality: 0,
            specificVolume: 0.001135002372530348,
            specificEnthalpy: 787.5557825431341,
            specificEntropy: 2.1926588668498703,
            temperature: 458.65273574845287
        };
        validateFluidProperties('Blowdown Flash Tank - inletWater', results.blowdownFlashTank.getInletWaterProperties(), expected);

        expected = {
            energyFlow: 0,
            massFlow: 0,
            pressure: 1.136,
            quality: 1,
            specificVolume: 0.17205143404254775,
            specificEnthalpy: 2781.8312880011326,
            specificEntropy: 6.540793415910698,
            temperature: 458.65273574845287
        };
        validateFluidProperties('Blowdown Flash Tank - outletGas', results.blowdownFlashTank.getOutletGasSaturatedProperties(), expected);

        expected = {
            energyFlow: 422086.61041989713,
            massFlow: 535.9450337053167,
            pressure: 1.136,
            quality: 0,
            specificVolume: 0.001135002372530348,
            specificEnthalpy: 787.5557825431341,
            specificEntropy: 2.1926588668498703,
            temperature: 458.65273574845287
        };
        validateFluidProperties('Blowdown Flash Tank - outletLiquid', results.blowdownFlashTank.getOutletLiquidSaturatedProperties(), expected);
    }
}

function validateCondensateFlashTank(results){
    let flashTank = results.makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensateCalculationsDomain.condensateFlashTank;

    if(flashTank == null) return;

    let expected = {
        energyFlow: 3121906.698076338,
        massFlow: 11340,
        pressure: 1.136,
        quality: 0,
        specificVolume: 0.001019660335144356,
        specificEnthalpy: 275.300414292446,
        specificEntropy: 0.8997137118482235,
        temperature: 338.6999999999999
    };
    validateFluidProperties('Condensate Flash Tank - inletWater', flashTank.getInletWaterProperties(), expected);

    expected = {
        energyFlow: 0,
        massFlow: 0,
        pressure: 0.204747,
        quality: 1,
        specificVolume: 0.8664961907839751,
        specificEnthalpy: 2707.3177066592766,
        specificEntropy: 7.11902821487601,
        temperature: 394.1047658380901
    };
    validateFluidProperties('Condensate Flash Tank - outletGas', flashTank.getOutletGasSaturatedProperties(), expected);

    expected = {
        energyFlow: 3121906.698076338,
        massFlow: 11340,
        pressure: 1.136,
        quality: 0,
        specificVolume: 0.001019660335144356,
        specificEnthalpy: 275.300414292446,
        specificEntropy: 0.8997137118482235,
        temperature: 338.6999999999999
    };
    validateFluidProperties('Condensate Flash Tank - outletLiquid', flashTank.getOutletLiquidSaturatedProperties(), expected);
}

function validateHighPressureCondensateFlashTank(results){
    let flashTank = results.highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;

    if(flashTank == null) return;

    let expected = {
        energyFlow: undefined,
        massFlow: undefined,
        pressure: undefined,
        quality: undefined,
        specificVolume: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        temperature: undefined
    };
    validateFluidProperties('High Pressure Condensate Flash Tank - inletWater', flashTank.getInletWaterProperties(), expected);

    expected = {
        energyFlow: undefined,
        massFlow: undefined,
        pressure: undefined,
        quality: undefined,
        specificVolume: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        temperature: undefined
    };
    validateFluidProperties('High Pressure Condensate Flash Tank - outletGas', flashTank.getOutletGasSaturatedProperties(), expected);

    expected = {
        energyFlow: undefined,
        massFlow: undefined,
        pressure: undefined,
        quality: undefined,
        specificVolume: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        temperature: undefined
    };
    validateFluidProperties('High Pressure Condensate Flash Tank - outletLiquid', flashTank.getOutletLiquidSaturatedProperties(), expected);
}

function validateMediumPressureCondensateFlashTank(results){
    if(results.lowPressureHeaderCalculationsDomain == null) return;

    let flashTank = results.lowPressureHeaderCalculationsDomain.lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;

    if(flashTank == null) return;

    let expected = {
        energyFlow: undefined,
        massFlow: undefined,
        pressure: undefined,
        quality: undefined,
        specificVolume: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        temperature: undefined
    };
    validateFluidProperties('Medium Pressure Condensate Flash Tank - inletWater', flashTank.getInletWaterProperties(), expected);

    expected = {
        energyFlow: undefined,
        massFlow: undefined,
        pressure: undefined,
        quality: undefined,
        specificVolume: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        temperature: undefined
    };
    validateFluidProperties('Medium Pressure Condensate Flash Tank - outletGas', flashTank.getOutletGasSaturatedProperties(), expected);

    expected = {
        energyFlow: undefined,
        massFlow: undefined,
        pressure: undefined,
        quality: undefined,
        specificVolume: undefined,
        specificEnthalpy: undefined,
        specificEntropy: undefined,
        temperature: undefined
    };
    validateFluidProperties('Medium Pressure Condensate Flash Tank - outletLiquid', flashTank.getOutletLiquidSaturatedProperties(), expected);
}

function steamModeler() {
    let boilerInput = {
        fuelType: 1,
        fuel: 1,
        combustionEfficiency: 85,
        blowdownRate: 2,
        blowdownFlashed: true,
        preheatMakeupWater: true,
        steamTemperature: 514.2,
        deaeratorVentRate: 0.1,
        deaeratorPressure: 0.204747,
        approachTemperature: 10,
    };

    let header1 = {
        pressure: 1.136,
        processSteamUsage: 22680,
        condensationRecoveryRate: 50,
        heatLoss: 0.1,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 1,

        condensateReturnTemperature: 338.7,
        flashCondensateReturn: true,
    };
    let header2 = {
        pressure: 2,
        processSteamUsage: 2,
        condensationRecoveryRate: 2,
        heatLoss: 2,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 338.7,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    let header3 = {
        pressure: 3,
        processSteamUsage: 3,
        condensationRecoveryRate: 3,
        heatLoss: 3,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 338.7,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    let headerInput = {
        highPressureHeader: header1,
        mediumPressureHeader: null,
        lowPressureHeader: null,
    };

    let operationsInput = {
        sitePowerImport: 18000000,
        makeUpWaterTemperature: 283.15,
        operatingHoursPerYear: 8000,
        fuelCosts: 0.000005478,
        electricityCosts: 1.39E-05,
        makeUpWaterCosts: 0.66,
    };

    let condensingTurbine = {
        isentropicEfficiency: 1,
        generationEfficiency: 1,
        condenserPressure: 1,
        operationType: Module.CondensingTurbineOperation.POWER_GENERATION,
        operationValue: 1,
        useTurbine: true,
    };
    let highToLowTurbine = {
        isentropicEfficiency: 2,
        generationEfficiency: 2,
        condenserPressure: 2,
        operationType: Module.PressureTurbineOperation.BALANCE_HEADER,
        operationValue1: 2,
        operationValue2: 2,
        useTurbine: true,
    };
    let highToMediumTurbine = {
        isentropicEfficiency: 3,
        generationEfficiency: 3,
        condenserPressure: 3,
        operationType: Module.PressureTurbineOperation.POWER_RANGE,
        operationValue1: 3,
        operationValue2: 3,
        useTurbine: true,
    };
    let mediumToLowTurbine = {
        isentropicEfficiency: 4,
        generationEfficiency: 4,
        condenserPressure: 4,
        operationType: Module.PressureTurbineOperation.FLOW_RANGE,
        operationValue1: 4,
        operationValue2: 4,
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
    let headerInputObj = new Module.HeaderInput(highPressureHeaderObj, null, null);
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
