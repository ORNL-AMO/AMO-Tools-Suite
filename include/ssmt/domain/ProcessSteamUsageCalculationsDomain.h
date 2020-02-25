#ifndef AMO_TOOLS_SUITE_PROCESSSTEAMUSAGECALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_PROCESSSTEAMUSAGECALCULATIONSDOMAIN_H

class ProcessSteamUsage {
public:
    double pressure;
    double temperature;
    double energyFlow;
    double massFlow;
    double processUsage;

    friend std::ostream &operator<<(std::ostream &stream, const ProcessSteamUsage &domain) {
        stream << "ProcessSteamUsage["
               << "pressure=" << domain.pressure
               << ", temperature=" << domain.temperature
               << ", energyFlow=" << domain.energyFlow
               << ", massFlow=" << domain.massFlow
               << ", processUsage=" << domain.processUsage
               << "]";
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<ProcessSteamUsage> &domain) {
        if (domain == nullptr) {
            stream << "ProcessSteamUsage[nullptr]";
        } else {
            stream << *domain;
        }
        return stream;
    }
};

class ProcessSteamUsageCalculationsDomain {
public:
    ProcessSteamUsage highPressureProcessSteamUsage;
    std::shared_ptr<ProcessSteamUsage> lowPressureProcessUsagePtr;
    std::shared_ptr<ProcessSteamUsage> mediumPressureProcessUsagePtr;

    friend std::ostream &operator<<(std::ostream &stream, const ProcessSteamUsageCalculationsDomain &domain) {
        stream << "ProcessSteamUsageCalculationsDomain["
               << "highPressureProcessSteamUsage=" << domain.highPressureProcessSteamUsage
               << ", lowPressureProcessUsagePtr=" << domain.lowPressureProcessUsagePtr
               << ", mediumPressureProcessUsagePtr=" << domain.mediumPressureProcessUsagePtr
               << "]";
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_PROCESSSTEAMUSAGECALCULATIONSDOMAIN_H
