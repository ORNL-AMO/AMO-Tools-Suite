/**
 * @file
 * @brief Contains the class definition for Bio-Tiger waste water treatment simulation.
 *
 * 
 *
 * @author Mark Root (mroot)
 * @author Mohsen Maniat
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_WASTEWATERTREATMENT_H
#define AMO_TOOLS_SUITE_WASTEWATERTREATMENT_H


#include <vector>
class WasteWaterTreatment
{
public:
    struct CalculationsTable
    {
        CalculationsTable(
            double Se,
            double HeterBio,
            double CellDeb,
            double InterVes,
            double MLVSS,
            double MLSS,
            double BiomassProd,
            double SludgeProd,
            double SolidProd,
            double Effluent,
            double IntentWaste,
            double OxygenRqd,
            double FlowMgd,
            double NRemoved,
            double NRemovedMgl,
            double NitO2Dem,
            double O2Reqd,
            double EffNH3N,
            double EffNo3N,
            double TotalO2Rqd,
            double WAS,
            double EstimatedEff,
            double EstimRas,
            double FmRatio,
            double Diff_MLSS,
            double SRT) : Se(Se),
                          HeterBio(HeterBio),
                          CellDeb(CellDeb),
                          InterVes(InterVes),
                          MLVSS(MLVSS),
                          MLSS(MLSS),
                          BiomassProd(BiomassProd),
                          SludgeProd(SludgeProd),
                          Effluent(Effluent),
                          IntentWaste(IntentWaste),
                          OxygenRqd(OxygenRqd),
                          FlowMgd(FlowMgd),
                          NRemoved(NRemoved),
                          NRemovedMgl(NRemovedMgl),
                          NitO2Dem(NitO2Dem),
                          O2Reqd(O2Reqd),
                          EffNH3N(EffNH3N),
                          EffNo3N(EffNo3N),
                          TotalO2Rqd(TotalO2Rqd),
                          WAS(WAS),
                          EstimatedEff(EstimatedEff),
                          EstimRas(EstimRas),
                          FmRatio(FmRatio),
                          Diff_MLSS(Diff_MLSS),
                          SRT(SRT)
        {
        }
        CalculationsTable() = default;
        double Se;
        double HeterBio;
        double CellDeb;
        double InterVes;
        double MLVSS;
        double MLSS;
        double BiomassProd;
        double SludgeProd;
        double SolidProd;
        double Effluent;
        double IntentWaste;
        double OxygenRqd;
        double FlowMgd;
        double NRemoved;
        double NRemovedMgl;
        double NitO2Dem;
        double O2Reqd;
        double EffNH3N;
        double EffNo3N;
        double TotalO2Rqd;
        double WAS;
        double EstimatedEff;
        double EstimRas;
        double FmRatio;
        double Diff_MLSS;
        double SRT;

        std::vector<double> getArray() {
            std::vector<double> array{
                Se,
                HeterBio,
                CellDeb,
                InterVes,
                MLVSS,
                MLSS,
                BiomassProd,
                SludgeProd,
                SolidProd,
                Effluent,
                IntentWaste,
                OxygenRqd,
                FlowMgd,
                NRemoved,
                NRemovedMgl,
                NitO2Dem,
                O2Reqd,
                EffNH3N,
                EffNo3N,
                TotalO2Rqd,
                WAS,
                EstimatedEff,
                EstimRas,
                FmRatio,
                Diff_MLSS,
                SRT
            };
            return array;
        };
    };
public:
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
            double FieldOTR,
            std::vector<CalculationsTable> calculationsTable) : TotalAverageDailyFlowRate(TotalAverageDailyFlowRate),
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
                               FieldOTR(FieldOTR),
                               calculationsTable(calculationsTable)
        {
        }
        Output() = default;
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
        std::vector<CalculationsTable> calculationsTable;
    };


	/**
	 * @param Temperature, double
	 * @param So, double
	 * @param Volume, double
	 * @param FlowRate, double
	 * @param InertVSS, double
	 * @param Biomass, double
	 * @param InfluentTSS, double
	 * @param InertInOrgTSS, double
	 * @param EffluentTSS, double
	 * @param RASTSS, double
	 * @param MLSSpar, double
	 * @param FractionBiomass, double
	 * @param BiomassYeild, double
	 * @param HalfSaturation, double
	 * @param MicrobialDecay, double
	 * @param MaxUtilizationRate, double
	 * @param MaxDays, double
	 * @param TimeIncrement, double
	 * @param OperatingDO, double
	 * @param Alpha, double
	 * @param Beta, double
	 * @param SOTR, double
	 * @param Aeration, double
	 * @param Elevation, double
	 * @param OperatingTime, double
	 * @param TypeAerators, double
	 * @param Speed, double
	 * @param EnergyCostUnit, double
     * @return WasteWaterTreatment::Output results from calculat() function
     * 
	 */
public:
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
          RASTSS(RASTSS),
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
          EnergyCostUnit(EnergyCostUnit){};

    Output calculate();

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
