const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'wasteWater' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
}

test('WasteWaterTreatment', function (t) {
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
        SOTR:  2.7,
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
});