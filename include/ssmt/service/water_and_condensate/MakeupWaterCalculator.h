#ifndef AMO_TOOLS_SUITE_MAKEUPWATERCALCULATOR_H
#define AMO_TOOLS_SUITE_MAKEUPWATERCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/OperationsInput.h>

class MakeupWaterCalculator {
public:
    SteamSystemModelerTool::SteamPropertiesOutput calc(const OperationsInput &operationsInput) const;
};

#endif //AMO_TOOLS_SUITE_MAKEUPWATERCALCULATOR_H
