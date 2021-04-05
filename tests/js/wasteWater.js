const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'wasteWater' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
}

test('WasteWaterTreatment 1', function (t) {
    t.plan(32);
    t.type(bindings.WasteWaterTreatment, 'function');

    var inp = {
        Temperature: 20,
        So: 200,
        Volume: 1,
        FlowRate: 1,
        InertVSS: 40,
        OxidizableN: 35,
        Biomass: 0.85,
        InfluentTSS: 200,
        InertInOrgTSS: 20,
        EffluentTSS: 8,
        RASTSS: 10000,
        MLSSpar: 3000,
        FractionBiomass: 0.1,
        BiomassYeild: 0.6,
        HalfSaturation: 60,
        MicrobialDecay: 0.1,
        MaxUtilizationRate: 8,
        MaxDays: 72,
        TimeIncrement: 2,
        OperatingDO: 4.5,
        Alpha: 0.84,
        Beta: 0.92,
        SOTR: 2.7,
        Aeration: 150,
        Elevation: 200,
        OperatingTime: 24,
        TypeAerators: 1,
        Speed: 100,
        EnergyCostUnit: 0.09
    }

    var res = bindings.WasteWaterTreatment(inp);

    t.equal(rnd(res.TotalAverageDailyFlowRate), rnd(1.00));
    t.equal(rnd(res.VolumeInService), rnd(1.00));
    t.equal(rnd(res.InfluentBOD5Concentration), rnd(200.00));
    t.equal(rnd(res.InfluentBOD5MassLoading), rnd(1668.00));
    t.equal(rnd(res.SecWWOxidNLoad), rnd(291.90));
    t.equal(rnd(res.SecWWTSSLoad), rnd(1668.00));
    t.equal(rnd(res.FM_ratio), rnd(0.09));
    t.equal(rnd(res.SolidsRetentionTime), rnd(29.00));
    t.equal(rnd(res.MLSS), rnd(3082.50));
    t.equal(rnd(res.MLVSS), rnd(2301.12));
    t.equal(rnd(res.TSSSludgeProduction), rnd(819.76));
    t.equal(rnd(res.TSSInActivatedSludgeEffluent), rnd(66.72));
    t.equal(rnd(res.TotalOxygenRequirements), rnd(3135.09));
    t.equal(rnd(res.TotalOxygenReqWDenit), rnd(2698.14));
    t.equal(rnd(res.TotalOxygenSupplied), rnd(3394.16));
    t.equal(rnd(res.MixingIntensityInReactor), rnd(150.00));
    t.equal(rnd(res.RASFlowRate), rnd(0.45));
    t.equal(rnd(res.RASRecyclePercentage), rnd(44.56));
    t.equal(rnd(res.WASFlowRate), rnd(0.01));
    t.equal(rnd(res.RASTSSConcentration), rnd(10000.00));
    t.equal(rnd(res.TotalSludgeProduction), rnd(886.48));
    t.equal(rnd(res.ReactorDetentionTime), rnd(24.00));
    t.equal(rnd(res.VOLR), rnd(12.48));
    t.equal(rnd(res.EffluentCBOD5), rnd(3.95));
    t.equal(rnd(res.EffluentTSS), rnd(8.00));
    t.equal(rnd(res.EffluentAmmonia_N), rnd(0.35));
    t.equal(rnd(res.EffluentNO3_N), rnd(26.17));
    t.equal(rnd(res.EffluentNO3_N_W_Denit), rnd(7.85));
    t.equal(rnd(res.FieldOTR), rnd(0.94));
    t.equal(rnd(res.AeEnergy), rnd(70200));
    t.equal(rnd(res.AeCost), rnd(6318));

    console.log(" ");
    console.log("Calculations Table Begin");
    console.log(JSON.stringify(res.calculationsTable));
    console.log("Calculations Table End");
});



test('WasteWaterTreatment 2', function (t) {
    t.plan(32);
    t.type(bindings.WasteWaterTreatment, 'function');

    var inp = {
        Temperature: 26,
        So: 280,
        Volume: 9,
        FlowRate: 28,
        InertVSS: 30,
        OxidizableN: 60,
        Biomass: 0.85,
        InfluentTSS: 150,
        InertInOrgTSS: 15,
        EffluentTSS: 11,
        RASTSS: 10000,
        MLSSpar: 3300,
        FractionBiomass: 0.1,
        BiomassYeild: 0.6,
        HalfSaturation: 60,
        MicrobialDecay: 0.1,
        MaxUtilizationRate: 8,
        MaxDays: 22,
        TimeIncrement: .5,
        OperatingDO: 1.2,
        Alpha: 0.84,
        Beta: 0.92,
        SOTR: 3,
        Aeration: 2100,
        Elevation: 100,
        OperatingTime: 24,
        TypeAerators: 3,
        Speed: 100,
        EnergyCostUnit: 0.09
    }

    var res = bindings.WasteWaterTreatment(inp);

    t.equal(rnd(res.TotalAverageDailyFlowRate), rnd(28));
    t.equal(rnd(res.VolumeInService), rnd(9));
    t.equal(rnd(res.InfluentBOD5Concentration), rnd(280));
    t.equal(rnd(res.InfluentBOD5MassLoading), rnd(65385.6));
    t.equal(rnd(res.SecWWOxidNLoad), rnd(14011.2));
    t.equal(rnd(res.SecWWTSSLoad), rnd(35028));
    t.equal(rnd(res.FM_ratio), rnd(0.334191));
    t.equal(rnd(res.SolidsRetentionTime), rnd(6.5));
    t.equal(rnd(res.MLSS), rnd(3262.89));
    t.equal(rnd(res.MLVSS), rnd(2606.63));
    t.equal(rnd(res.TSSSludgeProduction), rnd(35110.18));
    t.equal(rnd(res.TSSInActivatedSludgeEffluent), rnd(2568.72));
    t.equal(rnd(res.TotalOxygenRequirements), rnd(98885.32));
    t.equal(rnd(res.TotalOxygenReqWDenit), rnd(86971.98));
    t.equal(rnd(res.TotalOxygenSupplied), rnd(99656.99));
    t.equal(rnd(res.MixingIntensityInReactor), rnd(233.333));
    t.equal(rnd(res.RASFlowRate), rnd(13.5609));
    t.equal(rnd(res.RASRecyclePercentage), rnd(48.4317));
    t.equal(rnd(res.WASFlowRate), rnd(0.420985));
    t.equal(rnd(res.RASTSSConcentration), rnd(10000.00));
    t.equal(rnd(res.TotalSludgeProduction), rnd(37678.9));
    t.equal(rnd(res.ReactorDetentionTime), rnd(7.71429));
    t.equal(rnd(res.VOLR), rnd(54.3426));
    t.equal(rnd(res.EffluentCBOD5), rnd(7.81034));
    t.equal(rnd(res.EffluentTSS), rnd(11));
    t.equal(rnd(res.EffluentAmmonia_N), rnd(14.6));
    t.equal(rnd(res.EffluentNO3_N), rnd(25.4827));
    t.equal(rnd(res.EffluentNO3_N_W_Denit), rnd(7.64481));
    t.equal(rnd(res.FieldOTR), rnd(1.98));
    t.equal(rnd(res.AeEnergy), rnd(982800));
    t.equal(rnd(res.AeCost), rnd(88452));

    console.log(" ");
    console.log("Calculations Table Begin");
    console.log(JSON.stringify(res.calculationsTable));
    console.log("Calculations Table End");
});


test('WasteWaterTreatment 3', function (t) {
    t.plan(32);
    t.type(bindings.WasteWaterTreatment, 'function');

    var inp = {
        Temperature: 27,
        So: 100,
        Volume: 5,
        FlowRate: 5,
        InertVSS: 70,
        OxidizableN: 50,
        Biomass: 0.2,
        InfluentTSS: 200,
        InertInOrgTSS: 40,
        EffluentTSS: 8,
        RASTSS: 10000,
        MLSSpar: 3000,
        FractionBiomass: 0.1,
        BiomassYeild: 0.6,
        HalfSaturation: 60,
        MicrobialDecay: 0.09,
        MaxUtilizationRate: 10,
        MaxDays: 36,
        TimeIncrement: 1,
        OperatingDO: 3,
        Alpha: 0.84,
        Beta: 0.92,
        SOTR: 3.7,
        Aeration: 120,
        Elevation: 1000,
        OperatingTime: 12,
        TypeAerators: 2,
        Speed: 100,
        EnergyCostUnit: 0.09
    }

    var res = bindings.WasteWaterTreatment(inp);

    t.equal(rnd(res.TotalAverageDailyFlowRate), rnd(5));
    t.equal(rnd(res.VolumeInService), rnd(5));
    t.equal(rnd(res.InfluentBOD5Concentration), rnd(100));
    t.equal(rnd(res.InfluentBOD5MassLoading), rnd(4170));
    t.equal(rnd(res.SecWWOxidNLoad), rnd(2085));
    t.equal(rnd(res.SecWWTSSLoad), rnd(8340));
    t.equal(rnd(res.FM_ratio), rnd(0.085086));
    t.equal(rnd(res.SolidsRetentionTime), rnd(12));
    t.equal(rnd(res.MLSS), rnd(2996.38));
    t.equal(rnd(res.MLVSS), rnd(1175.28));
    t.equal(rnd(res.TSSSludgeProduction), rnd(10078.83));
    t.equal(rnd(res.TSSInActivatedSludgeEffluent), rnd(333.6));
    t.equal(rnd(res.TotalOxygenRequirements), rnd(12828.9));
    t.equal(rnd(res.TotalOxygenReqWDenit), rnd(9465.71));
    t.equal(rnd(res.TotalOxygenSupplied), rnd(2361.7));
    t.equal(rnd(res.MixingIntensityInReactor), rnd(24));
    t.equal(rnd(res.RASFlowRate), rnd(2.13917));
    t.equal(rnd(res.RASRecyclePercentage), rnd(42.7833));
    t.equal(rnd(res.WASFlowRate), rnd(0.120849));
    t.equal(rnd(res.RASTSSConcentration), rnd(10000.00));
    t.equal(rnd(res.TotalSludgeProduction), rnd(10412.43));
    t.equal(rnd(res.ReactorDetentionTime), rnd(24));
    t.equal(rnd(res.VOLR), rnd(6.23831));
    t.equal(rnd(res.EffluentCBOD5), rnd(4.51688));
    t.equal(rnd(res.EffluentTSS), rnd(8));
    t.equal(rnd(res.EffluentAmmonia_N), rnd(.939091));
    t.equal(rnd(res.EffluentNO3_N), rnd(40.2857));
    t.equal(rnd(res.EffluentNO3_N_W_Denit), rnd(12.0857));
    t.equal(rnd(res.FieldOTR), rnd(1.640067));
    t.equal(rnd(res.AeEnergy), rnd(28080));
    t.equal(rnd(res.AeCost), rnd(2527.2));

    console.log(" ");
    console.log("Calculations Table Begin");
    console.log(JSON.stringify(res.calculationsTable));
    console.log("Calculations Table End");
});



test('WasteWaterTreatmentGivenSRT 1', function (t) {
    t.plan(32);
    t.type(bindings.WasteWaterTreatmentGivenSRT, 'function');

    var inp = {
        Temperature: 27,
        So: 100,
        Volume: 5,
        FlowRate: 5,
        InertVSS: 70,
        OxidizableN: 50,
        Biomass: 0.2,
        InfluentTSS: 200,
        InertInOrgTSS: 40,
        EffluentTSS: 8,
        RASTSS: 10000,
        MLSSpar: 3000,
        FractionBiomass: 0.1,
        BiomassYeild: 0.6,
        HalfSaturation: 60,
        MicrobialDecay: 0.09,
        MaxUtilizationRate: 10,
        // MaxDays: 36,
        // TimeIncrement: 1,
        OperatingDO: 3,
        Alpha: 0.84,
        Beta: 0.92,
        SOTR: 3.7,
        Aeration: 120,
        Elevation: 1000,
        OperatingTime: 12,
        TypeAerators: 2,
        Speed: 100,
        EnergyCostUnit: 0.09,
        DefinedSRT: 12
    }

    var res = bindings.WasteWaterTreatmentGivenSRT(inp);

    t.equal(rnd(res.TotalAverageDailyFlowRate), rnd(5));
    t.equal(rnd(res.VolumeInService), rnd(5));
    t.equal(rnd(res.InfluentBOD5Concentration), rnd(100));
    t.equal(rnd(res.InfluentBOD5MassLoading), rnd(4170));
    t.equal(rnd(res.SecWWOxidNLoad), rnd(2085));
    t.equal(rnd(res.SecWWTSSLoad), rnd(8340));
    t.equal(rnd(res.FM_ratio), rnd(0.085086));
    t.equal(rnd(res.SolidsRetentionTime), rnd(12));
    t.equal(rnd(res.MLSS), rnd(2996.38));
    t.equal(rnd(res.MLVSS), rnd(1175.28));
    t.equal(rnd(res.TSSSludgeProduction), rnd(10078.83));
    t.equal(rnd(res.TSSInActivatedSludgeEffluent), rnd(333.6));
    t.equal(rnd(res.TotalOxygenRequirements), rnd(12828.9));

    t.equal(rnd(res.TotalOxygenReqWDenit), rnd(9465.71));

    t.equal(rnd(res.TotalOxygenSupplied), rnd(2361.7));
    t.equal(rnd(res.MixingIntensityInReactor), rnd(24));
    t.equal(rnd(res.RASFlowRate), rnd(2.13917));
    t.equal(rnd(res.RASRecyclePercentage), rnd(42.7833));
    t.equal(rnd(res.WASFlowRate), rnd(0.120849));
    t.equal(rnd(res.RASTSSConcentration), rnd(10000.00));
    t.equal(rnd(res.TotalSludgeProduction), rnd(10412.43));
    t.equal(rnd(res.ReactorDetentionTime), rnd(24));
    t.equal(rnd(res.VOLR), rnd(6.23831));
    t.equal(rnd(res.EffluentCBOD5), rnd(4.51688));
    t.equal(rnd(res.EffluentTSS), rnd(8));
    t.equal(rnd(res.EffluentAmmonia_N), rnd(.939091));

    t.equal(rnd(res.EffluentNO3_N), rnd(40.2857));

    t.equal(rnd(res.EffluentNO3_N_W_Denit), rnd(12.0857));

    t.equal(rnd(res.FieldOTR), rnd(1.640067));
    t.equal(rnd(res.AeEnergy), rnd(28080));
    t.equal(rnd(res.AeCost), rnd(2527.2));
});



test('WasteWaterTreatmentGivenSRT 2', function (t) {
    t.plan(32);
    t.type(bindings.WasteWaterTreatmentGivenSRT, 'function');

    var inp = {
        Temperature: 20,
        So: 200,
        Volume: 1,
        FlowRate: 1,
        InertVSS: 40,
        OxidizableN: 35,
        Biomass: 0.85,
        InfluentTSS: 200,
        InertInOrgTSS: 20,
        EffluentTSS: 8,
        RASTSS: 10000,
        MLSSpar: 3000,
        FractionBiomass: 0.1,
        BiomassYeild: 0.6,
        HalfSaturation: 60,
        MicrobialDecay: 0.1,
        MaxUtilizationRate: 8,
        // MaxDays: 72,
        // TimeIncrement: 2,
        OperatingDO: 4.5,
        Alpha: 0.84,
        Beta: 0.92,
        SOTR: 2.7,
        Aeration: 150,
        Elevation: 200,
        OperatingTime: 24,
        TypeAerators: 1,
        Speed: 100,
        EnergyCostUnit: 0.09,
        DefinedSRT: 29.00
    }

    var res = bindings.WasteWaterTreatmentGivenSRT(inp);

    t.equal(rnd(res.TotalAverageDailyFlowRate), rnd(1.00));
    t.equal(rnd(res.VolumeInService), rnd(1.00));
    t.equal(rnd(res.InfluentBOD5Concentration), rnd(200.00));
    t.equal(rnd(res.InfluentBOD5MassLoading), rnd(1668.00));
    t.equal(rnd(res.SecWWOxidNLoad), rnd(291.90));
    t.equal(rnd(res.SecWWTSSLoad), rnd(1668.00));
    t.equal(rnd(res.FM_ratio), rnd(0.09));
    t.equal(rnd(res.SolidsRetentionTime), rnd(29.00));
    t.equal(rnd(res.MLSS), rnd(3082.50));
    t.equal(rnd(res.MLVSS), rnd(2301.12));
    t.equal(rnd(res.TSSSludgeProduction), rnd(819.76));
    t.equal(rnd(res.TSSInActivatedSludgeEffluent), rnd(66.72));
    t.equal(rnd(res.TotalOxygenRequirements), rnd(3135.09));
    t.equal(rnd(res.TotalOxygenReqWDenit), rnd(2698.14));
    t.equal(rnd(res.TotalOxygenSupplied), rnd(3394.16));
    t.equal(rnd(res.MixingIntensityInReactor), rnd(150.00));
    t.equal(rnd(res.RASFlowRate), rnd(0.45));
    t.equal(rnd(res.RASRecyclePercentage), rnd(44.56));
    t.equal(rnd(res.WASFlowRate), rnd(0.01));
    t.equal(rnd(res.RASTSSConcentration), rnd(10000.00));
    t.equal(rnd(res.TotalSludgeProduction), rnd(886.48));
    t.equal(rnd(res.ReactorDetentionTime), rnd(24.00));
    t.equal(rnd(res.VOLR), rnd(12.48));
    t.equal(rnd(res.EffluentCBOD5), rnd(3.95));
    t.equal(rnd(res.EffluentTSS), rnd(8.00));
    t.equal(rnd(res.EffluentAmmonia_N), rnd(0.35));
    t.equal(rnd(res.EffluentNO3_N), rnd(26.17));
    t.equal(rnd(res.EffluentNO3_N_W_Denit), rnd(7.85));
    t.equal(rnd(res.FieldOTR), rnd(0.94));
    t.equal(rnd(res.AeEnergy), rnd(70200));
    t.equal(rnd(res.AeCost), rnd(6318));
});



test('WasteWaterTreatmentGivenSRT 3', function (t) {
    t.plan(32);
    t.type(bindings.WasteWaterTreatmentGivenSRT, 'function');

    var inp = {
        Temperature: 26,
        So: 280,
        Volume: 9,
        FlowRate: 28,
        InertVSS: 30,
        OxidizableN: 60,
        Biomass: 0.85,
        InfluentTSS: 150,
        InertInOrgTSS: 15,
        EffluentTSS: 11,
        RASTSS: 10000,
        MLSSpar: 3300,
        FractionBiomass: 0.1,
        BiomassYeild: 0.6,
        HalfSaturation: 60,
        MicrobialDecay: 0.1,
        MaxUtilizationRate: 8,
        // MaxDays: 22,
        // TimeIncrement: .5,
        OperatingDO: 1.2,
        Alpha: 0.84,
        Beta: 0.92,
        SOTR: 3,
        Aeration: 2100,
        Elevation: 100,
        OperatingTime: 24,
        TypeAerators: 3,
        Speed: 100,
        EnergyCostUnit: 0.09,
        DefinedSRT: 6.5
    }

    var res = bindings.WasteWaterTreatmentGivenSRT(inp);

    t.equal(rnd(res.TotalAverageDailyFlowRate), rnd(28));
    t.equal(rnd(res.VolumeInService), rnd(9));
    t.equal(rnd(res.InfluentBOD5Concentration), rnd(280));
    t.equal(rnd(res.InfluentBOD5MassLoading), rnd(65385.6));
    t.equal(rnd(res.SecWWOxidNLoad), rnd(14011.2));
    t.equal(rnd(res.SecWWTSSLoad), rnd(35028));
    t.equal(rnd(res.FM_ratio), rnd(0.334191));
    t.equal(rnd(res.SolidsRetentionTime), rnd(6.5));
    t.equal(rnd(res.MLSS), rnd(3262.89));
    t.equal(rnd(res.MLVSS), rnd(2606.63));
    t.equal(rnd(res.TSSSludgeProduction), rnd(35110.18));
    t.equal(rnd(res.TSSInActivatedSludgeEffluent), rnd(2568.72));
    t.equal(rnd(res.TotalOxygenRequirements), rnd(98885.32));
    t.equal(rnd(res.TotalOxygenReqWDenit), rnd(86971.98));
    t.equal(rnd(res.TotalOxygenSupplied), rnd(99656.99));
    t.equal(rnd(res.MixingIntensityInReactor), rnd(233.333));
    t.equal(rnd(res.RASFlowRate), rnd(13.5609));
    t.equal(rnd(res.RASRecyclePercentage), rnd(48.4317));
    t.equal(rnd(res.WASFlowRate), rnd(0.420985));
    t.equal(rnd(res.RASTSSConcentration), rnd(10000.00));
    t.equal(rnd(res.TotalSludgeProduction), rnd(37678.9));
    t.equal(rnd(res.ReactorDetentionTime), rnd(7.71429));
    t.equal(rnd(res.VOLR), rnd(54.3426));
    t.equal(rnd(res.EffluentCBOD5), rnd(7.81034));
    t.equal(rnd(res.EffluentTSS), rnd(11));
    t.equal(rnd(res.EffluentAmmonia_N), rnd(14.6));
    t.equal(rnd(res.EffluentNO3_N), rnd(25.4827));
    t.equal(rnd(res.EffluentNO3_N_W_Denit), rnd(7.64481));
    t.equal(rnd(res.FieldOTR), rnd(1.98));
    t.equal(rnd(res.AeEnergy), rnd(982800));
    t.equal(rnd(res.AeCost), rnd(88452));
});
