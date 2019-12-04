#include "ssmt/service/medium_pressure_header/ReducedSteamException.h"

ReducedSteamException::ReducedSteamException(const std::string &actionMessage,
                                             const std::shared_ptr<Turbine> &highToLowPressureTurbineUpdated,
                                             const std::shared_ptr<Turbine> &highToLowPressureTurbineIdealUpdated)
        : actionMessage(actionMessage), highToLowPressureTurbineUpdated(highToLowPressureTurbineUpdated),
          highToLowPressureTurbineIdealUpdated(highToLowPressureTurbineIdealUpdated) {}

std::ostream &operator<<(std::ostream &stream, const ReducedSteamException &e) {
    return stream << "ReducedSteamException["
                  << "actionMessage=" << e.actionMessage
                  << "highToLowPressureTurbineUpdated=" << e.highToLowPressureTurbineUpdated
                  << "highToLowPressureTurbineIdealUpdated=" << e.highToLowPressureTurbineIdealUpdated
                  << "]";
}

const std::string &ReducedSteamException::getActionMessage() const {
    return actionMessage;
}

const std::shared_ptr<Turbine> &ReducedSteamException::getHighToLowPressureTurbineUpdated() const {
    return highToLowPressureTurbineUpdated;
}

const std::shared_ptr<Turbine> &ReducedSteamException::getHighToLowPressureTurbineIdealUpdated() const {
    return highToLowPressureTurbineIdealUpdated;
}
