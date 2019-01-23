#ifndef AMO_TOOLS_SUITE_HEADERINPUT_H
#define AMO_TOOLS_SUITE_HEADERINPUT_H

#include <iostream>
#include <list>
#include <memory>

class HeaderWithPressure {
public:
    HeaderWithPressure(double pressure, double processSteamUsage, double condensationRecoveryRate, double heatLoss,
                       bool flashCondensate);

    double getPressure() const;

    double getProcessSteamUsage() const;

    double getCondensationRecoveryRate() const;

    double getHeatLoss() const;

    bool isFlashCondensate() const;

protected:
    double pressure;
    double processSteamUsage;
    double condensationRecoveryRate;
    double heatLoss;
    bool flashCondensate;
};

class HeaderWithHighestPressure : public HeaderWithPressure {
public:
    HeaderWithHighestPressure(double pressure, double processSteamUsage, double condensationRecoveryRate,
                              double heatLoss, double condensateReturnTemperature, bool flashCondensateReturn);

    friend std::ostream &operator<<(std::ostream &stream, const HeaderWithHighestPressure &header);

    double getCondensateReturnTemperature() const;

private:
    double condensateReturnTemperature;
};

class HeaderNotHighestPressure : public HeaderWithPressure {
public:
    HeaderNotHighestPressure(double pressure, double processSteamUsage, double condensationRecoveryRate,
                             double heatLoss, bool flashCondensateIntoHeader, bool desuperheatSteamIntoNextHighest,
                             double desuperheatSteamTemperature);

    friend std::ostream &operator<<(std::ostream &stream, const HeaderNotHighestPressure &header);

    bool isDesuperheatSteamIntoNextHighest() const;

    double getDesuperheatSteamTemperature() const;

private:
    bool desuperheatSteamIntoNextHighest;
    double desuperheatSteamTemperature;
};

class HeaderInput {
public:
    HeaderInput(const HeaderWithHighestPressure &highPressureHeader,
                const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeader,
                const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeader);

    HeaderWithHighestPressure getHighPressureHeader() const;

    std::shared_ptr<HeaderNotHighestPressure> getLowPressureHeader() const;

    std::shared_ptr<HeaderNotHighestPressure> getMediumPressureHeader() const;

private:
    HeaderWithHighestPressure highPressureHeader;

    /** Optional; is nullptr when not present. */
    std::shared_ptr<HeaderNotHighestPressure> mediumPressureHeader;

    /** Optional; is nullptr when not present. */
    std::shared_ptr<HeaderNotHighestPressure> lowPressureHeader;
};

#endif //AMO_TOOLS_SUITE_HEADERINPUT_H
