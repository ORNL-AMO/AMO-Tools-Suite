#include "ssmt/service/SteamBalanceException.h"

SteamBalanceException::SteamBalanceException(double additionalSteamNeeded, double adjustedInitialSteam)
        : additionalSteamNeeded(additionalSteamNeeded), adjustedInitialSteam(adjustedInitialSteam) {}

std::ostream &operator<<(std::ostream &stream, const SteamBalanceException &e) {
    return stream << "SteamBalanceException["
                  << "additionalSteamNeeded=" << e.getAdditionalSteamNeeded()
                  << ", adjustedInitialSteam=" << e.getAdjustedInitialSteam() << "]";
}

double SteamBalanceException::getAdditionalSteamNeeded() const {
    return additionalSteamNeeded;
}

double SteamBalanceException::getAdjustedInitialSteam() const {
    return adjustedInitialSteam;
}
