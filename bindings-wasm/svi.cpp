#include "vector"

#include "calculator/util/SludgeVolumeIndex.h"
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(svi_class)
{
    enum_<SludgeVolumeIndex::SVIParameter>("SVIParameter")
        .value("SVISN", SludgeVolumeIndex::SVIParameter::SVISN)
        .value("SVIGN", SludgeVolumeIndex::SVIParameter::SVIGN)
        .value("SVIGS", SludgeVolumeIndex::SVIParameter::SVIGS)
        .value("SVISS", SludgeVolumeIndex::SVIParameter::SVISS)
        .value("VoK", SludgeVolumeIndex::SVIParameter::VoK);

    class_<SludgeVolumeIndex::GraphDataPoint>("GraphDataPoint")
        .property("SolidsConcentration", &SludgeVolumeIndex::GraphDataPoint::SolidsConcentration)
        .property("SolidsFlux", &SludgeVolumeIndex::GraphDataPoint::SolidsFlux);

    register_vector<SludgeVolumeIndex::GraphDataPoint>("GraphDataV");

    class_<SludgeVolumeIndex::Output>("SludgeVolumeIndexOutput")
        .property("TotalAreaClarifier", &SludgeVolumeIndex::Output::TotalAreaClarifier)
        .property("SurfaceOverflow", &SludgeVolumeIndex::Output::SurfaceOverflow)
        .property("AppliedSolidsLoading", &SludgeVolumeIndex::Output::AppliedSolidsLoading)
        .property("RasConcentration", &SludgeVolumeIndex::Output::RasConcentration)
        .property("UnderFlowRateX2", &SludgeVolumeIndex::Output::UnderFlowRateX2)
        .property("UnderFlowRateY1", &SludgeVolumeIndex::Output::UnderFlowRateY1)
        .property("OverFlowRateX2", &SludgeVolumeIndex::Output::OverFlowRateX2)
        .property("OverFlowRateY2", &SludgeVolumeIndex::Output::OverFlowRateY2)
        .property("StatePointX", &SludgeVolumeIndex::Output::StatePointX)
        .property("StatePointY", &SludgeVolumeIndex::Output::StatePointY)
        .property("GraphData", &SludgeVolumeIndex::Output::GraphData);

    class_<SludgeVolumeIndex>("SludgeVolumeIndex")
        .constructor<SludgeVolumeIndex::SVIParameter, double, int, double, double, double, double, double>()
        .function("calculate", &SludgeVolumeIndex::calculate);
}
