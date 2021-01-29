#ifndef AMO_TOOLS_SUITE_SLUDGEVOLUMEINDEX_H
#define AMO_TOOLS_SUITE_SLUDGEVOLUMEINDEX_H

class SludgeVolumeIndex {
public:
    enum SVIParameter {
        SVISN,
        SVIGN,
        SVIGS,
        SVISS,
        VoK
    };

    struct GraphDataPoint
    {
        GraphDataPoint(double SolidsConcentration, double SolidsFlux) : SolidsConcentration(SolidsConcentration), SolidsFlux(SolidsFlux){}

        GraphDataPoint() = default;
        double SolidsConcentration = 0, SolidsFlux = 0;
    };

    struct Output
    {
        Output(double TotalAreaClarifier , double SurfaceOverflow , double AppliedSolidsLoading , double RasConcentration,
               double UnderFlowRateX2, double UnderFlowRateY1, double OverFlowRateX2, double OverFlowRateY2, double  StatePointX, double StatePointY,
               std::vector<GraphDataPoint> GraphData) :
            TotalAreaClarifier(TotalAreaClarifier), SurfaceOverflow(SurfaceOverflow), AppliedSolidsLoading(AppliedSolidsLoading), RasConcentration(RasConcentration),
            UnderFlowRateX2(UnderFlowRateX2), UnderFlowRateY1(UnderFlowRateY1), OverFlowRateX2(OverFlowRateX2), OverFlowRateY2(OverFlowRateY2), StatePointX(StatePointX), StatePointY(StatePointY), GraphData(GraphData) {}

        Output() = default;
        double TotalAreaClarifier = 0, SurfaceOverflow = 0, AppliedSolidsLoading = 0, RasConcentration = 0,
                UnderFlowRateX2 = 0, UnderFlowRateY1 = 0, OverFlowRateX2 = 0, OverFlowRateY2 = 0, StatePointX = 0, StatePointY = 0;
        std::vector<GraphDataPoint> GraphData;
    };

    SludgeVolumeIndex(SVIParameter sviParameter, double sviValue, int numberOfClarifiers, double areaOfClarifier, double MLSS, double influentFlow, double rasFlow, double sludgeSettlingVelocity) :
            sviParameter(sviParameter), sviValue(sviValue), numberOfClarifiers(numberOfClarifiers), areaOfClarifier(areaOfClarifier), MLSS(MLSS), influentFlow(influentFlow), rasFlow(rasFlow), sludgeSettlingVelocity(sludgeSettlingVelocity) {}

    Output calculate();

private:
    SVIParameter sviParameter = SVIParameter::SVISN;
    double sviValue = 0;
    int numberOfClarifiers = 0;
    double areaOfClarifier = 0;
    double MLSS = 0;
    double influentFlow = 0;
    double rasFlow = 0;
    double sludgeSettlingVelocity = 0;

    static double Round(double value) { return (float)((int)(value * 100 + .5)) / 100; }
};
#endif //AMO_TOOLS_SUITE_SLUDGEVOLUMEINDEX_H
