#ifndef AMO_TOOLS_SUITE_PROCESSSTEAMUSAGECALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_PROCESSSTEAMUSAGECALCULATIONSDOMAIN_H

class ProcessSteamUsage {
public:
    double pressure;
    double temperature;
    double energyFlow;
    double massFlow;
    double processUsage;
};

class ProcessSteamUsageCalculationsDomain {
public:
    ProcessSteamUsage highPressureProcessSteamUsage;
    std::shared_ptr<ProcessSteamUsage> lowPressureProcessUsagePtr;
    std::shared_ptr<ProcessSteamUsage> mediumPressureProcessUsagePtr;
};

#endif //AMO_TOOLS_SUITE_PROCESSSTEAMUSAGECALCULATIONSDOMAIN_H
