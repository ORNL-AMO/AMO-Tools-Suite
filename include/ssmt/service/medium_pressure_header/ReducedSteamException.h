#ifndef AMO_TOOLS_SUITE_REDUCEDSTEAMEXCEPTION_H
#define AMO_TOOLS_SUITE_REDUCEDSTEAMEXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include <ssmt/Turbine.h>

/**
 * Represents a situation in calculating when had to take steam from one to use in another to balance the system.
 */
class ReducedSteamException : public std::exception {
public:
    ReducedSteamException(const std::string &actionMessage,
                          const std::shared_ptr<Turbine> &highToLowPressureTurbineUpdated,
                          const std::shared_ptr<Turbine> &highToLowPressureTurbineIdealUpdated);

    friend std::ostream &operator<<(std::ostream &stream, const ReducedSteamException &e);

    const std::string &getActionMessage() const;

    const std::shared_ptr<Turbine> &getHighToLowPressureTurbineUpdated() const;

    const std::shared_ptr<Turbine> &getHighToLowPressureTurbineIdealUpdated() const;

private:
    std::string actionMessage;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
    std::shared_ptr<Turbine> highToLowPressureTurbineIdealUpdated;
};

#endif //AMO_TOOLS_SUITE_REDUCEDSTEAMEXCEPTION_H
