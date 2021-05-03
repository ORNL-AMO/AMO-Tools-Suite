/**
 * @file
 * @brief State point analysis for rate of activated sludge.
 *
 *
 *
 * @author Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#include <vector>
#include <cmath>
#include "calculator/util/SludgeVolumeIndex.h"

using namespace std;

SludgeVolumeIndex::Output SludgeVolumeIndex::calculate(){
    double sviParamAlpha = 0, sviParamBeta = 1, sviParamDelta = 0, sviParamGamma = 1;
    switch (sviParameter) {
        case SVIGN: sviParamAlpha = 0.351; sviParamBeta = 0.58; sviParamDelta = 6.02; sviParamGamma = 18.2; break;
        case SVIGS: sviParamAlpha = 0.245; sviParamBeta = 2.96; sviParamDelta = 10.73; sviParamGamma = 24.3; break;
        case SVISN: sviParamAlpha = 0.261; sviParamBeta = 1.7; sviParamDelta = 3.7; sviParamGamma = 14.9; break;
        case SVISS: sviParamAlpha = 0.211; sviParamBeta = 2.36; sviParamDelta = 5.93; sviParamGamma = 14.6; break;
        case VoK: sviParamAlpha = 0; sviParamBeta = 1; sviParamDelta = 0; sviParamGamma = 1; break;
    }

    double overflowLineY2 = 1.25 * sviParamGamma * sludgeSettlingVelocity * exp(-1 * sviParamDelta * sviValue - 1) / (sviParamAlpha + sviParamBeta * sviValue);
    double totalClarifierArea = numberOfClarifiers * areaOfClarifier;
    double surfaceOverflow = influentFlow / totalClarifierArea;
    double appliedSolidsLoading = (influentFlow+rasFlow) * MLSS / (totalClarifierArea);
    double rasConcentration = (appliedSolidsLoading * totalClarifierArea / rasFlow);

    int dataPointsCount = 151;
    std::vector<GraphDataPoint> graphData(dataPointsCount);
    for(int i = 0; i < dataPointsCount; i++) {
        graphData[i].SolidsConcentration = i/10.0;
        graphData[i].SolidsFlux = Round(graphData[i].SolidsConcentration * sviParamGamma * sludgeSettlingVelocity * exp(-1 * sviParamDelta * sviValue - (sviParamAlpha + sviParamBeta * sviValue) * graphData[i].SolidsConcentration));
    }

    return Output(totalClarifierArea, surfaceOverflow, appliedSolidsLoading, rasConcentration,
                  rasConcentration * 1000, appliedSolidsLoading,
                  overflowLineY2 * totalClarifierArea * 1000 / influentFlow, overflowLineY2,
                  MLSS * 1000, MLSS * influentFlow / totalClarifierArea, graphData);
}