/**
 * @file
 * @brief Contains the implementation of Bio-Tiger, waste water treatment simulation.
 *
 * 
 *
 * @author Mark Root, Mohsen Maniat
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_WASTEWATERTREATMENT_H
#define AMO_TOOLS_SUITE_WASTEWATERTREATMENT_H

/**
 * 
 * 
 */
class WasteWaterTreatment
{
public:
    /**
     * Output
     * 
     * 
     * */
    struct Output
    {
        Output(
            double TotalAverageDailyFlowRate,
            double VolumeInService,
            double InfluentBOD5Concentration,
            double InfluentBOD5MassLoading,
            double SecWWOxidNLoad,
            double SecWWTSSLoad,
            double FM_ratio,
            double SolidsRetentionTime,
            double MLSS,
            double MLVSS,
            double TSSSludgeProduction,
            double TSSInActivatedSludgeEffluent,
            double TotalOxygenRequirements,
            double TotalOxygenReqWDenit,
            double TotalOxygenSupplied,
            double MixingIntensityInReactor,
            double RASFlowRate,
            double RASRecyclePercentage,
            double WASFlowRate,
            double RASTSSConcentration,
            double TotalSludgeProduction,
            double ReactorDetentionTime,
            double VOLR,
            double EffluentCBOD5,
            double EffluentTSS,
            double EffluentAmmonia_N,
            double EffluentNO3_N,
            double EffluentNO3_N_W_Denit,

            double AeEnergy,
            double AeCost,
            double FieldOTR) : TotalAverageDailyFlowRate(TotalAverageDailyFlowRate),
                               VolumeInService(VolumeInService),
                               InfluentBOD5Concentration(InfluentBOD5Concentration),
                               InfluentBOD5MassLoading(InfluentBOD5MassLoading),
                               SecWWOxidNLoad(SecWWOxidNLoad),
                               SecWWTSSLoad(SecWWTSSLoad),
                               FM_ratio(FM_ratio),
                               SolidsRetentionTime(SolidsRetentionTime),
                               MLSS(MLSS),
                               MLVSS(MLVSS),
                               TSSSludgeProduction(TSSSludgeProduction),
                               TSSInActivatedSludgeEffluent(TSSInActivatedSludgeEffluent),
                               TotalOxygenRequirements(TotalOxygenRequirements),
                               TotalOxygenReqWDenit(TotalOxygenReqWDenit),
                               TotalOxygenSupplied(TotalOxygenSupplied),
                               MixingIntensityInReactor(MixingIntensityInReactor),
                               RASFlowRate(RASFlowRate),
                               RASRecyclePercentage(RASRecyclePercentage),
                               WASFlowRate(WASFlowRate),
                               RASTSSConcentration(RASTSSConcentration),
                               TotalSludgeProduction(TotalSludgeProduction),
                               ReactorDetentionTime(ReactorDetentionTime),
                               VOLR(VOLR),
                               EffluentCBOD5(EffluentCBOD5),
                               EffluentTSS(EffluentTSS),
                               EffluentAmmonia_N(EffluentAmmonia_N),
                               EffluentNO3_N(EffluentNO3_N),
                               EffluentNO3_N_W_Denit(EffluentNO3_N_W_Denit),
                               AeEnergy(AeEnergy),
                               AeCost(AeCost),
                               FieldOTR(FieldOTR)
        {
        }

        double TotalAverageDailyFlowRate;
        double VolumeInService;
        double InfluentBOD5Concentration;
        double InfluentBOD5MassLoading;
        double SecWWOxidNLoad;
        double SecWWTSSLoad;
        double FM_ratio;
        double SolidsRetentionTime;
        double MLSS;
        double MLVSS;
        double TSSSludgeProduction;
        double TSSInActivatedSludgeEffluent;
        double TotalOxygenRequirements;
        double TotalOxygenReqWDenit;
        double TotalOxygenSupplied;
        double MixingIntensityInReactor;
        double RASFlowRate;
        double RASRecyclePercentage;
        double WASFlowRate;
        double RASTSSConcentration;
        double TotalSludgeProduction;
        double ReactorDetentionTime;
        double VOLR;
        double EffluentCBOD5;
        double EffluentTSS;
        double EffluentAmmonia_N;
        double EffluentNO3_N;
        double EffluentNO3_N_W_Denit;

        double AeEnergy;
        double AeCost;
        double FieldOTR;
    };

    /**
     *
     * Constructor
     *
     *
     *
     * */
    WasteWaterTreatment(
        double Temperature,
        double So,
        double Volume,
        double FlowRate,
        double InertVSS,
        double OxidizableN,
        double Biomass,
        double InfluentTSS,
        double InertInOrgTSS,
        double EffluentTSS,
        double RASTSS,
        double MLSSpar,
        double FractionBiomass,
        double BiomassYeild,
        double HalfSaturation,
        double MicrobialDecay,
        double MaxUtilizationRate,
        double MaxDays,
        double TimeIncrement,
        double OperatingDO,
        double Alpha,
        double Beta,
        double SOTR,
        double Aeration,
        double Elevation,
        double OperatingTime,
        int TypeAerators,
        double Speed,
        double EnergyCostUnit)
        : Temperature(Temperature),
          So(So),
          Volume(Volume),
          FlowRate(FlowRate),
          InertVSS(InertVSS),
          OxidizableN(OxidizableN),
          Biomass(Biomass),
          InfluentTSS(InfluentTSS),
          InertInOrgTSS(InertInOrgTSS),
          EffluentTSS(EffluentTSS),
          MLSSpar(MLSSpar),
          FractionBiomass(FractionBiomass),
          BiomassYeild(BiomassYeild),
          HalfSaturation(HalfSaturation),
          MicrobialDecay(MicrobialDecay),
          MaxUtilizationRate(MaxUtilizationRate),
          MaxDays(MaxDays),
          TimeIncrement(TimeIncrement),
          OperatingDO(OperatingDO),
          Alpha(Alpha),
          Beta(Beta),
          SOTR(SOTR),
          Aeration(Aeration),
          Elevation(Elevation),
          OperatingTime(OperatingTime),
          TypeAerators(TypeAerators),
          Speed(Speed),
          EnergyCostUnit(EnergyCostUnit)
    {
    }

private:
    double Temperature;
    double So;
    double Volume;
    double FlowRate;
    double InertVSS;
    double OxidizableN;
    double Biomass;
    double InfluentTSS;
    double InertInOrgTSS;
    double EffluentTSS;
    double RASTSS;
    double MLSSpar;
    double FractionBiomass;
    double BiomassYeild;
    double HalfSaturation;
    double MicrobialDecay;
    double MaxUtilizationRate;
    double MaxDays;
    double TimeIncrement;

    double OperatingDO;
    double Alpha;
    double Beta;
    double SOTR;
    double Aeration;
    double Elevation;
    double OperatingTime;
    int TypeAerators;
    double Speed;
    double EnergyCostUnit;
};
#endif //AMO_TOOLS_SUITE_WASTEWATERTREATMENT_H
