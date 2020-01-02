#ifndef AMO_TOOLS_SUITE_STEAMREDUCER_H
#define AMO_TOOLS_SUITE_STEAMREDUCER_H

#include <ssmt/Turbine.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/TurbineFactory.h>

//TODO extract class
class SteamReducerOutput {
public:
    double remainingAdditionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated;

    friend std::ostream &operator<<(std::ostream &stream, const SteamReducerOutput &output) {
        stream << "Turbine["
               << "remainingAdditionalSteamNeeded=" << static_cast< int >(output.remainingAdditionalSteamNeeded)
               << ", highToLowPressureTurbineUpdated=" << output.highToLowPressureTurbineUpdated
               << ", highToLowPressureTurbineIdealUpdated=" << output.highToLowPressureTurbineIdealUpdated
               << "]";
        return stream;
    }
};

/**
 * Reduce steam allocation from one turbine to another for balancing the system.
 */
class SteamReducer {
public:
    /**
     * Reduce steam from the high to low turbine when additional steam is needed.
     * @return Amount of steam still needed by the system after taking steam from turbine.
     */
    SteamReducerOutput
    reduceSteamThroughHighToLowTurbine(const double additionalSteamNeeded, const PressureTurbine &highToLowTurbineInput,
                                       const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                       const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                                       const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                       const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const TurbineFactory turbineFactory = TurbineFactory();

    SteamReducerOutput
    reduceBalanceHeader(const double additionalSteamNeeded,
                        const PressureTurbine &highToLowTurbineInput,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                        const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

    SteamReducerOutput
    reducePowerRange(const double additionalSteamNeeded,
                     const PressureTurbine &highToLowTurbineInput,
                     const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                     const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                     const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                     const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

    SteamReducerOutput
    reduceFlowRange(const double additionalSteamNeeded,
                    const PressureTurbine &highToLowTurbineInput,
                    const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                    const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal,
                    const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

};

#endif //AMO_TOOLS_SUITE_STEAMREDUCER_H
