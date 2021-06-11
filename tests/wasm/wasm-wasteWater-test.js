function calcWasteWaterTreatment(headerMsg, input, output, hasTable){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.TotalAverageDailyFlowRate), rnd(expected[0]), "TotalAverageDailyFlowRate");
        testNumberValue(rnd(results.VolumeInService), rnd(expected[1]), "VolumeInService");
        testNumberValue(rnd(results.InfluentBOD5Concentration), rnd(expected[2]), "InfluentBOD5Concentration");
        testNumberValue(rnd(results.InfluentBOD5MassLoading), rnd(expected[3]), "InfluentBOD5MassLoading");
        testNumberValue(rnd(results.SecWWOxidNLoad), rnd(expected[4]), "SecWWOxidNLoad");
        testNumberValue(rnd(results.SecWWTSSLoad), rnd(expected[5]), "SecWWTSSLoad");
        testNumberValue(rnd(results.FM_ratio), rnd(expected[6]), "FM_ratio");
        testNumberValue(rnd(results.SolidsRetentionTime), rnd(expected[7]), "SolidsRetentionTime");
        testNumberValue(rnd(results.MLSS), rnd(expected[8]), "MLSS");
        testNumberValue(rnd(results.MLVSS), rnd(expected[9]), "MLVSS");
        testNumberValue(rnd(results.TSSSludgeProduction), rnd(expected[10]), "TSSSludgeProduction");
        testNumberValue(rnd(results.TSSInActivatedSludgeEffluent), rnd(expected[11]), "TSSInActivatedSludgeEffluent");
        testNumberValue(rnd(results.TotalOxygenRequirements), rnd(expected[12]), "TotalOxygenRequirements");
        testNumberValue(rnd(results.TotalOxygenReqWDenit), rnd(expected[13]), "TotalOxygenReqWDenit");
        testNumberValue(rnd(results.TotalOxygenSupplied), rnd(expected[14]), "TotalOxygenSupplied");
        testNumberValue(rnd(results.MixingIntensityInReactor), rnd(expected[15]), "MixingIntensityInReactor");
        testNumberValue(rnd(results.RASFlowRate), rnd(expected[16]), "RASFlowRate");
        testNumberValue(rnd(results.RASRecyclePercentage), rnd(expected[17]), "RASRecyclePercentage");
        testNumberValue(rnd(results.WASFlowRate), rnd(expected[18]), "WASFlowRate");
        testNumberValue(rnd(results.RASTSSConcentration), rnd(expected[19]), "RASTSSConcentration");
        testNumberValue(rnd(results.TotalSludgeProduction), rnd(expected[20]), "TotalSludgeProduction");
        testNumberValue(rnd(results.ReactorDetentionTime), rnd(expected[21]), "ReactorDetentionTime");
        testNumberValue(rnd(results.VOLR), rnd(expected[22]), "VOLR");
        testNumberValue(rnd(results.EffluentCBOD5), rnd(expected[23]), "EffluentCBOD5");
        testNumberValue(rnd(results.EffluentTSS), rnd(expected[24]), "EffluentTSS");
        testNumberValue(rnd(results.EffluentAmmonia_N), rnd(expected[25]), "EffluentAmmonia_N");
        testNumberValue(rnd(results.EffluentNO3_N), rnd(expected[26]), "EffluentNO3_N");
        testNumberValue(rnd(results.EffluentNO3_N_W_Denit), rnd(expected[27]), "EffluentNO3_N_W_Denit");
        testNumberValue(rnd(results.AeEnergy), rnd(expected[28]), "AeEnergy");
        testNumberValue(rnd(results.AeCost), rnd(expected[29]), "AeCost");
        testNumberValue(rnd(results.FieldOTR), rnd(expected[30]), "FieldOTR");

        if(hasTable) {
            let str = 'Data Dump<br/>Begin Calculations Table<br/>[<br/>';
            for (let i = 0; i < results.calculationsTable.size(); i++) {
                str += i > 0 ? ',<br/>[' : '[';
                let calcTable = results.calculationsTable.get(i).getArray();
                for(let j = 0; j < calcTable.size(); j++){
                    if(j > 0) str += ', ';
                    str += calcTable.get(j).toFixed(2);
                }
                str += ']';
            }
            str += '<br/>]<br/>End Calculations Table';
            logMessage(str);
        }
    };

    logMessage(headerMsg, true);
    let instance = new Module.WasteWater_Treatment(
        input.Temperature, input.So, input.Volume, input.FlowRate, input.InertVSS, input.OxidizableN, input.Biomass,
        input.InfluentTSS, input.InertInOrgTSS, input.EffluentTSS, input.RASTSS, input.MLSSpar, input.FractionBiomass,
        input.BiomassYeild, input.HalfSaturation, input.MicrobialDecay, input.MaxUtilizationRate, input.MaxDays,
        input.TimeIncrement, input.OperatingDO, input.Alpha, input.Beta, input.SOTR, input.Aeration, input.Elevation,
        input.OperatingTime, input.TypeAerators, input.Speed, input.EnergyCostUnit, input.DefinedSRT);
    validate(hasTable ? instance.calculate() : instance.calculateGivenSRT(), output);
    instance.delete();
}

function wasteWaterTreatment(){
    let input = {
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
        EnergyCostUnit: 0.09,
        DefinedSRT: 1
    }
    calcWasteWaterTreatment('Waste Water Treatment: Test# 1', input,
        [1, 1, 200, 1668, 291.9, 1668, 0.09, 29, 3082.5, 2301.12, 819.76, 66.72, 3135.09, 2698.14, 3394.16,
            150, 0.45, 44.56, 0.01, 10000, 886.48, 24, 12.48, 3.95, 8, 0.35, 26.17, 7.85, 70200, 6318, 0.94], true);

    input = {
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
        EnergyCostUnit: 0.09,
        DefinedSRT: 1
    }
    calcWasteWaterTreatment('Waste Water Treatment: Test# 2', input,
        [28, 9, 280, 65385.6, 14011.2, 35028, 0.334191, 6.5, 3262.89, 2606.63, 35110.18, 2568.72, 98885.32, 86971.98, 99656.99, 233.333,
            13.5609, 48.4317, 0.420985, 10000, 37678.9, 7.71429, 54.3426, 7.81034, 11, 14.6, 25.4827, 7.64481, 982800, 88452, 1.98], true);

    input = {
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
        EnergyCostUnit: 0.09,
        DefinedSRT: 1
    }
    calcWasteWaterTreatment('Waste Water Treatment: Test# 3', input,
        [5, 5, 100, 4170, 2085, 8340, 0.085086, 12, 2996.38, 1175.28, 10078.83, 333.6, 12828.9, 9465.71, 2361.7, 24, 2.13917, 42.7833,
            0.120849, 10000, 10412.43, 24, 6.23831, 4.51688, 8, 0.939091, 40.2857, 12.0857, 28080, 2527.2, 1.640067], true);

    input = {
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
        EnergyCostUnit: 0.09,
        DefinedSRT: 12
    }
    calcWasteWaterTreatment('Waste Water Treatment Given SRT: Test# 1', input,
        [5, 5, 100, 4170, 2085, 8340, 0.085086, 12, 2996.38, 1175.28, 10078.83, 333.6, 12828.9, 9465.71, 2361.7, 24, 2.13917,
            42.7833, 0.120849, 10000, 10412.43, 24, 6.23831, 4.51688, 8, 0.939091, 40.2857, 12.0857, 28080, 2527.2, 1.640067]);

    input = {
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
        EnergyCostUnit: 0.09,
        DefinedSRT: 29.00
    }
    calcWasteWaterTreatment('Waste Water Treatment Given SRT: Test# 2', input,
        [1, 1, 200, 1668, 291.9, 1668, 0.09, 29, 3082.5, 2301.12, 819.76, 66.72, 3135.09, 2698.14,
            3394.16, 150, 0.45, 44.56, 0.01, 10000, 886.48, 24, 12.48, 3.95, 8, 0.35, 26.17, 7.85, 70200, 6318, 0.94]);

    input = {
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
        EnergyCostUnit: 0.09,
        DefinedSRT: 6.5
    }
    calcWasteWaterTreatment('Waste Water Treatment Given SRT: Test# 3', input,
        [28, 9, 280, 65385.6, 14011.2, 35028, 0.334191, 6.5, 3262.89, 2606.63, 35110.18, 2568.72, 98885.32, 86971.98, 99656.99,
            233.333, 13.5609, 48.4317, 0.420985, 10000, 37678.9, 7.71429, 54.3426, 7.81034, 11, 14.6, 25.4827, 7.64481, 982800, 88452, 1.98]);
}

wasteWaterTreatment();