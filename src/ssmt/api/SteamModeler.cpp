#include "ssmt/api/SteamModeler.h"

SteamModelerOutput SteamModeler::model(const SteamModelerInput &steamModelerInput) {
    const bool isBaselineCalc = steamModelerInput.isBaselineCalc();
    const double baselinePowerDemand = steamModelerInput.getBaselinePowerDemand();
    const HeaderInput &headerInput = steamModelerInput.getHeaderInput();
    const BoilerInput &boilerInput = steamModelerInput.getBoilerInput();
    const TurbineInput &turbineInput = steamModelerInput.getTurbineInput();
    const OperationsInput &operationsInput = steamModelerInput.getOperationsInput();

    return modeler(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput, operationsInput);
}

SteamModelerOutput
SteamModeler::modeler(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
                    const BoilerInput &boilerInput, const TurbineInput &turbineInput,
                    const OperationsInput &operationsInput) {
    const std::string methodName = "SteamModeler::" + std::string(__func__) + ": ";

    logInputData(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput, operationsInput);

    logSection(methodName + "running calculations: begin");
    const SteamModelCalculationsDomain &steamModelCalculationsDomain =
            runModel(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput, operationsInput);
    logSection(methodName + "running calculations: end");

    logSection(methodName + "populating output from calculations results: begin");
    const SteamModelerOutput &steamModelerOutput = makeOutput(steamModelCalculationsDomain);
    logSection(methodName + "populating output from calculations results: end");

    // std::cout << methodName + "steamModelerOutput=" << steamModelerOutput << std::endl;

    return steamModelerOutput;
}

void
SteamModeler::logInputData(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
                           const BoilerInput &boilerInput, const TurbineInput &turbineInput,
                           const OperationsInput &operationsInput) {
    //keep this block or fix unused variable
    bool isBaselineCalc_ = isBaselineCalc; isBaselineCalc_ = isBaselineCalc_;
    double baselinePowerDemand_ = baselinePowerDemand; baselinePowerDemand_ = baselinePowerDemand_;
    HeaderInput headerInput_ = headerInput; headerInput_ =headerInput_;
    BoilerInput boilerInput_ = boilerInput; boilerInput_ = boilerInput_;
    TurbineInput turbineInput_ = turbineInput; turbineInput_ = turbineInput_;
    OperationsInput operationsInput_ = operationsInput; operationsInput_ = operationsInput_;
    //keep this block or fix unused variable

    logSection("SteamModeler::logInputData:");

    // std::cout
            // << "isBaselineCalc=" << isBaselineCalc
            // << ", baselinePowerDemand=" << baselinePowerDemand
            // << ", headerInput=" << headerInput
            // << ", boilerInput=" << boilerInput
            // << ", turbineInput=" << turbineInput
            // << ", operationsInput=" << operationsInput
            // << std::endl;
}

SteamModelCalculationsDomain
SteamModeler::runModel(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
                       const BoilerInput &boilerInput, const TurbineInput &turbineInput,
                       const OperationsInput &operationsInput) const {
    try {
        return steamModelRunner.run(isBaselineCalc, baselinePowerDemand, headerInput, boilerInput, turbineInput,
                                    operationsInput);
    } catch (std::exception &e) {
        logException(e, "SteamModeler::runModel: exception running the steam model: ");
        throw;
    }
}

SteamModelerOutput SteamModeler::makeOutput(const SteamModelCalculationsDomain &steamModelCalculationsDomain) const {
    try {
        return steamModelerOutputFactory.make(steamModelCalculationsDomain);
    } catch (std::exception &e) {
        logException(e, "SteamModeler::runModel: exception making steam model output: ");
        throw;
    }
}

void SteamModeler::logSection(const std::string &message) const {
    std::string message_ = message; message_ = message_;//keep this or fix unused variable
    // std::cout << "======== " << std::endl;
    // std::cout << "======== " << message << std::endl;
    // std::cout << "======== " << std::endl;
}

void SteamModeler::logException(const std::exception &e, const std::string &message) const {
    std::string message_ = message; message_ = message_;//keep this or fix unused variable
    std::exception e_ = e; e_ = e_;//keep this or fix unused variable
    // std::cout << "================================ " << std::endl;
    // std::cout << message << std::endl;
    // std::cout << e.what() << std::endl;
    // std::cout << "================================ " << std::endl;
}
