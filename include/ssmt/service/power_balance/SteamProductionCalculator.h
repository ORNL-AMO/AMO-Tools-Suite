#ifndef AMO_TOOLS_SUITE_STEAMPRODUCTIONCALCULATOR_H
#define AMO_TOOLS_SUITE_STEAMPRODUCTIONCALCULATOR_H

#include <memory>
#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/PRV.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>

class SteamProductionCalculator {
public:
    double calc(const int headerCountInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                    const BoilerInput &boilerInput,
                    const std::shared_ptr<FlashTank> &blowdownFlashTank,
                    const Boiler &boiler,
                    const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                    const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    double calcFlashTankAdditionalSteam(const int headerCountInput, const BoilerInput &boilerInput,
                                            const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                            const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                            const std::shared_ptr<FlashTank> &blowdownFlashTank,
                                            const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                                            const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double calcPrvAdditionalSteam(const int headerCountInput,
                                      const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                      const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                                      const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

    double
    addPrvMassFlow(double prvAdditionalSteam, const std::shared_ptr<PrvWithoutDesuperheating> &prv) const;
};

#endif //AMO_TOOLS_SUITE_STEAMPRODUCTIONCALCULATOR_H
