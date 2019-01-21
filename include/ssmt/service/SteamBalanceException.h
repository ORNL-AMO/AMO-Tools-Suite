#ifndef AMO_TOOLS_SUITE_STEAMBALANCEEXCEPTION_H
#define AMO_TOOLS_SUITE_STEAMBALANCEEXCEPTION_H

#include <exception>
#include <iostream>

/**
 * Represents a situation in the calculations when incorrect amount of steam remains.
 * Typically need to start the model over with an adjusted initial mass flow amount.
 */
class SteamBalanceException : public std::exception {
public:
    /**
     * @param additionalSteamNeeded The additional amount of steam needed.
     * @param adjustedInitialSteam The adjusted amount of steam to use when re-running the model.
     */
    SteamBalanceException(double additionalSteamNeeded, double adjustedInitialSteam);

    friend std::ostream &operator<<(std::ostream &stream, const SteamBalanceException &e);

    double getAdditionalSteamNeeded() const;

    double getAdjustedInitialSteam() const;

private:
    double additionalSteamNeeded;
    double adjustedInitialSteam;
};

#endif //AMO_TOOLS_SUITE_STEAMBALANCEEXCEPTION_H
