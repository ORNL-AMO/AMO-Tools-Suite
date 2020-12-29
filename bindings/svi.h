#include <nan.h>
#include <node.h>
#include <string>
#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include "./NanDataConverters.h"
#include "calculator/util/SludgeVolumeIndex.h"

using namespace Nan;
using namespace v8;

NAN_METHOD(svi)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const int sviParameter = getDouble("sviParameter", inp);
        const double sviValue = getDouble("sviValue", inp);
        const int numberOfClarifiers = getDouble("numberOfClarifiers", inp);
        const double areaOfClarifier = getDouble("areaOfClarifier", inp);
        const double MLSS = getDouble("MLSS", inp);
        const double influentFlow = getDouble("influentFlow", inp);
        const double rasFlow = getDouble("rasFlow", inp);
        const double sludgeSettlingVelocity = getDouble("sludgeSettlingVelocity", inp);

        SludgeVolumeIndex::SVIParameter parm;
        switch (sviParameter) {
            case 0: parm = SludgeVolumeIndex::SVIParameter::SVISN; break;
            case 1: parm = SludgeVolumeIndex::SVIParameter::SVIGN; break;
            case 2: parm = SludgeVolumeIndex::SVIParameter::SVIGS; break;
            case 3: parm = SludgeVolumeIndex::SVIParameter::SVISS; break;
            case 4: parm = SludgeVolumeIndex::SVIParameter::VoK; break;
        }

        auto output = SludgeVolumeIndex(parm, sviValue, numberOfClarifiers, areaOfClarifier, MLSS, influentFlow, rasFlow, sludgeSettlingVelocity).calculate();
        setR("TotalAreaClarifier", output.TotalAreaClarifier);
        setR("SurfaceOverflow", output.SurfaceOverflow);
        setR("AppliedSolidsLoading", output.AppliedSolidsLoading);
        setR("RasConcentration", output.RasConcentration);
        setR("UnderFlowRateX2", output.UnderFlowRateX2);
        setR("UnderFlowRateY1", output.UnderFlowRateY1);
        setR("OverFlowRateX2", output.OverFlowRateX2);
        setR("OverFlowRateY2", output.OverFlowRateY2);
        setR("StatePointX", output.StatePointX);
        setR("StatePointY", output.StatePointY);

        auto graphData = output.GraphData;
        auto graphDataPoints = New<Array>(graphData.size());
        for (unsigned i = 0; i < graphDataPoints->Length(); i++)
        {
            auto ctArray = New<Array>(2);
            ctArray->Set(Nan::GetCurrentContext(), 0, New(graphData[i].SolidsConcentration));
            ctArray->Set(Nan::GetCurrentContext(), 1, New(graphData[i].SolidsFlux));

            graphDataPoints->Set(Nan::GetCurrentContext(), i, ctArray);
        }
        Nan::Set(r, New("graphData").ToLocalChecked(), graphDataPoints);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in SludgeVolumeIndex - calculator: " + what).c_str());
    }
}