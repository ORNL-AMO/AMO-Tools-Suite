#ifndef AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/FlashTank.h>

class ReturnCondensateCalculationsDomain {
public:
    const std::shared_ptr<FlashTank> condensateFlashTank;
    const SteamSystemModelerTool::FluidProperties returnCondensateFlashed;

    friend std::ostream &operator<<(std::ostream &stream, const ReturnCondensateCalculationsDomain &domain) {
        stream << "ReturnCondensateCalculationsDomain["
               << "condensateFlashTank=" << domain.condensateFlashTank
               << ", returnCondensateFlashed=" << domain.returnCondensateFlashed
               << "]";
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H
