#ifndef AMO_TOOLS_SUITE_STEAMMODELEROUTPUTDATAMAPPER_H
#define AMO_TOOLS_SUITE_STEAMMODELEROUTPUTDATAMAPPER_H

#include "../NanDataConverters.h"
#include <ssmt/api/SteamModelerOutput.h>

class SteamModelerOutputDataMapper {
public:
    const void map(const SteamModelerOutput &steamModelerOutput) {
        std::cout << "SteamModelerOutputDataMapper::map: begin" << std::endl;

        // always in output
        mapOperations();
        mapBoiler();
        mapDeaerator();
        mapFeedwater();
        mapHighPressureHeaderSteam();
        mapBlowdown();
        mapCondensate();
        mapMakeupWater();
        mapMakeupWaterAndCondensate();
        mapHighPressureProcessSteamUsage();

        // optional turbines 0-4
        mapCondensingTurbine();
        mapHighPressureToMediumPressureTurbine();
        mapHighPressureToLowPressureTurbine();
        mapMediumPressureToLowPressureTurbine();

        //additional headers
        mapMediumPressureHeaderSteam();
        mapLowPressureHeaderSteam();

        //0-2 PRV
        mapHighPressureToMediumPressurePrv();
        mapMediumPressureToLowPressurePrv();

        //0-4 flash tanks
        mapBlowdownFlashTank();
        mapCondensateFlashTank();
        mapHighPressureCondensateFlashTank();
        mapMediumPressureCondensateFlashTank();

        mapVentedSteam();

        // not used: mapHeader();
        // not used (part of unused headerOutputObj): mapHeatLoss();

        std::cout << "SteamModelerOutputDataMapper::map: end" << std::endl;
    }

private:
    static void logMappingStart(const std::string &methodName) {
        std::cout << "==== " << methodName << ": begin" << std::endl;
    }

    static void logCommonStart(const std::string &methodName, const std::string &outputName) {
        std::cout << methodName << ": begin: outputName=" << outputName << std::endl;
    }

    void mapOperations() {
        logMappingStart(__func__);

        Local <String> localName = Nan::New<String>("operationsOutput").ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        double powerBalanceGeneration = 0;
        double powerBalanceDemand = 0;
        double powerBalanceImport = 0;
        double powerBalanceUnitCost = 0;
        double powerBalanceUnitCostPerYear = 0;
        double fuelBalanceBoiler = 0;
        double fuelBalanceUnitCost = 0;
        double fuelBalanceUnitCostPerYear = 0;
        double makeupWaterFlow = 0;
        double makeupWaterFlowRate = 0;
        double makeupWaterUnitCost = 0;
        double makeupWaterUnitCostPerYear = 0;
        double totalOperatingCostPerYear = 0;
        double highPressureCost = 0;
        double mediumPressureCost = 0;
        double lowPressureCost = 0;

        setRobject("powerBalanceGeneration", powerBalanceGeneration, object);
        setRobject("powerBalanceDemand", powerBalanceDemand, object);
        setRobject("powerBalanceImport", powerBalanceImport, object);
        setRobject("powerBalanceUnitCost", powerBalanceUnitCost, object);
        setRobject("powerBalanceUnitCostPerYear", powerBalanceUnitCostPerYear, object);
        setRobject("fuelBalanceBoiler", fuelBalanceBoiler, object);
        setRobject("fuelBalanceUnitCost", fuelBalanceUnitCost, object);
        setRobject("fuelBalanceUnitCostPerYear", fuelBalanceUnitCostPerYear, object);
        setRobject("makeupWaterFlow", makeupWaterFlow, object);
        setRobject("makeupWaterFlowRate", makeupWaterFlowRate, object);
        setRobject("makeupWaterUnitCost", makeupWaterUnitCost, object);
        setRobject("makeupWaterUnitCostPerYear", makeupWaterUnitCostPerYear, object);
        setRobject("totalOperatingCostPerYear", totalOperatingCostPerYear, object);
        setRobject("highPressureCost", highPressureCost, object);
        setRobject("mediumPressureCost", mediumPressureCost, object);
        setRobject("lowPressureCost", lowPressureCost, object);
    }

    void mapBoiler() {
        logMappingStart(__func__);

        Local <String> localName = Nan::New<String>("boilerOutput").ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        double steamPressure = 0;
        double steamTemperature = 0;
        double steamSpecificEnthalpy = 0;
        double steamSpecificEntropy = 0;
        double steamQuality = 0;
        double steamVolume = 0;
        double steamMassFlow = 0;
        double steamEnergyFlow = 0;

        double blowdownPressure = 0;
        double blowdownTemperature = 0;
        double blowdownSpecificEnthalpy = 0;
        double blowdownSpecificEntropy = 0;
        double blowdownQuality = 0;
        double blowdownVolume = 0;
        double blowdownMassFlow = 0;
        double blowdownEnergyFlow = 0;

        double feedwaterPressure = 0;
        double feedwaterTemperature = 0;
        double feedwaterSpecificEnthalpy = 0;
        double feedwaterSpecificEntropy = 0;
        double feedwaterQuality = 0;
        double feedwaterVolume = 0;
        double feedwaterMassFlow = 0;
        double feedwaterEnergyFlow = 0;

        double boilerEnergy = 0;
        double fuelEnergy = 0;
        double blowdownRate = 0;
        double combustionEff = 0;

        setRobject("steamPressure", steamPressure, object);
        setRobject("steamTemperature", steamTemperature, object);
        setRobject("steamSpecificEnthalpy", steamSpecificEnthalpy, object);
        setRobject("steamSpecificEntropy", steamSpecificEntropy, object);
        setRobject("steamQuality", steamQuality, object);
        setRobject("steamVolume", steamVolume, object);
        setRobject("steamMassFlow", steamMassFlow, object);
        setRobject("steamEnergyFlow", steamEnergyFlow, object);

        setRobject("blowdownPressure", blowdownPressure, object);
        setRobject("blowdownTemperature", blowdownTemperature, object);
        setRobject("blowdownSpecificEnthalpy", blowdownSpecificEnthalpy, object);
        setRobject("blowdownSpecificEntropy", blowdownSpecificEntropy, object);
        setRobject("blowdownQuality", blowdownQuality, object);
        setRobject("blowdownVolume", blowdownVolume, object);
        setRobject("blowdownMassFlow", blowdownMassFlow, object);
        setRobject("blowdownEnergyFlow", blowdownEnergyFlow, object);

        setRobject("feedwaterPressure", feedwaterPressure, object);
        setRobject("feedwaterTemperature", feedwaterTemperature, object);
        setRobject("feedwaterSpecificEnthalpy", feedwaterSpecificEnthalpy, object);
        setRobject("feedwaterSpecificEntropy", feedwaterSpecificEntropy, object);
        setRobject("feedwaterQuality", feedwaterQuality, object);
        setRobject("feedwaterVolume", feedwaterVolume, object);
        setRobject("feedwaterMassFlow", feedwaterMassFlow, object);
        setRobject("feedwaterEnergyFlow", feedwaterEnergyFlow, object);

        setRobject("boilerEnergy", boilerEnergy, object);
        setRobject("fuelEnergy", fuelEnergy, object);
        setRobject("blowdownRate", blowdownRate, object);
        setRobject("combustionEff", combustionEff, object);
    }

    void mapSteamProperties(const std::string &outputName) {
        logCommonStart(__func__, outputName);

        Local <String> localName = Nan::New<String>(outputName).ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        const double pressure = 0;
        const double temperature = 0;
        const double specificEnthalpy = 0;
        const double specificEntropy = 0;
        const double quality = 0;
        const double specificVolume = 0;
        //SteamProperties() function call does not have these fields
        //these fields will be set during the SSMT calculation
        //and will need to be apart of objects with this type
        const double massFlow = 0;
        const double energyFlow = 0;

        setRobject("pressure", pressure, object);
        setRobject("temperature", temperature, object);
        setRobject("specificEnthalpy", specificEnthalpy, object);
        setRobject("specificEntropy", specificEntropy, object);
        setRobject("quality", quality, object);
        setRobject("specificVolume", specificVolume, object);
        setRobject("massFlow", massFlow, object);
        setRobject("energyFlow", energyFlow, object);
    }

    void mapFeedwater() {
        logMappingStart(__func__);
        mapSteamProperties("feedwater");
    }

    void mapHighPressureHeaderSteam() {
        logMappingStart(__func__);
        mapSteamProperties("highPressureHeaderSteam");
    }

    void mapBlowdown() {
        logMappingStart(__func__);
        mapSteamProperties("blowdown");
    }

    void mapCondensate() {
        logMappingStart(__func__);
        mapSteamProperties("condensate");
    }

    void mapMakeupWater() {
        logMappingStart(__func__);
        mapSteamProperties("makeupWater");
    }

    void mapMakeupWaterAndCondensate() {
        logMappingStart(__func__);
        mapSteamProperties("makeupWaterAndCondensate");
    }

    void mapHighPressureProcessSteamUsage() {
        logMappingStart(__func__);
        mapSteamProperties("highPressureProcessSteamUsage");
    }

    void mapMediumPressureHeaderSteam() {
        logMappingStart(__func__);
        mapSteamProperties("mediumPressureHeaderSteam");
    }

    void mapLowPressureHeaderSteam() {
        logMappingStart(__func__);
        mapSteamProperties("lowPressureHeaderSteam");
    }

    void mapVentedSteam() {
        logMappingStart(__func__);
        mapSteamProperties("ventedSteam");
    }

    void mapDeaerator() {
        logMappingStart(__func__);

        Local <String> localName = Nan::New<String>("deaeratorOutput").ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        double feedwaterEnergyFlow = 0;
        double feedwaterMassFlow = 0;
        double feedwaterPressure = 0;
        double feedwaterQuality = 0;
        double feedwaterSpecificEnthalpy = 0;
        double feedwaterSpecificEntropy = 0;
        double feedwaterVolume = 0;
        double feedwaterTemperature = 0;
        double inletSteamEnergyFlow = 0;
        double inletSteamMassFlow = 0;
        double inletSteamPressure = 0;
        double inletSteamQuality = 0;
        double inletSteamSpecificEnthalpy = 0;
        double inletSteamSpecificEntropy = 0;
        double inletSteamVolume = 0;
        double inletSteamTemperature = 0;
        double inletWaterEnergyFlow = 0;
        double inletWaterMassFlow = 0;
        double inletWaterPressure = 0;
        double inletWaterQuality = 0;
        double inletWaterSpecificEnthalpy = 0;
        double inletWaterSpecificEntropy = 0;
        double inletWaterVolume = 0;
        double inletWaterTemperature = 0;
        double ventedSteamEnergyFlow = 0;
        double ventedSteamMassFlow = 0;
        double ventedSteamPressure = 0;
        double ventedSteamQuality = 0;
        double ventedSteamSpecificEnthalpy = 0;
        double ventedSteamSpecificEntropy = 0;
        double ventedSteamVolume = 0;
        double ventedSteamTemperature = 0;

        setRobject("feedwaterEnergyFlow", feedwaterEnergyFlow, object);
        setRobject("feedwaterMassFlow", feedwaterMassFlow, object);
        setRobject("feedwaterPressure", feedwaterPressure, object);
        setRobject("feedwaterQuality", feedwaterQuality, object);
        setRobject("feedwaterSpecificEnthalpy", feedwaterSpecificEnthalpy, object);
        setRobject("feedwaterSpecificEntropy", feedwaterSpecificEntropy, object);
        setRobject("feedwaterVolume", feedwaterVolume, object);
        setRobject("feedwaterTemperature", feedwaterTemperature, object);
        setRobject("inletSteamEnergyFlow", inletSteamEnergyFlow, object);
        setRobject("inletSteamMassFlow", inletSteamMassFlow, object);
        setRobject("inletSteamPressure", inletSteamPressure, object);
        setRobject("inletSteamQuality", inletSteamQuality, object);
        setRobject("inletSteamSpecificEnthalpy", inletSteamSpecificEnthalpy, object);
        setRobject("inletSteamSpecificEntropy", inletSteamSpecificEntropy, object);
        setRobject("inletSteamVolume", inletSteamVolume, object);
        setRobject("inletSteamTemperature", inletSteamTemperature, object);
        setRobject("inletWaterEnergyFlow", inletWaterEnergyFlow, object);
        setRobject("inletWaterMassFlow", inletWaterMassFlow, object);
        setRobject("inletWaterPressure", inletWaterPressure, object);
        setRobject("inletWaterQuality", inletWaterQuality, object);
        setRobject("inletWaterSpecificEnthalpy", inletWaterSpecificEnthalpy, object);
        setRobject("inletWaterSpecificEntropy", inletWaterSpecificEntropy, object);
        setRobject("inletWaterVolume", inletWaterVolume, object);
        setRobject("inletWaterTemperature", inletWaterTemperature, object);
        setRobject("ventedSteamEnergyFlow", ventedSteamEnergyFlow, object);
        setRobject("ventedSteamMassFlow", ventedSteamMassFlow, object);
        setRobject("ventedSteamPressure", ventedSteamPressure, object);
        setRobject("ventedSteamQuality", ventedSteamQuality, object);
        setRobject("ventedSteamSpecificEnthalpy", ventedSteamSpecificEnthalpy, object);
        setRobject("ventedSteamSpecificEntropy", ventedSteamSpecificEntropy, object);
        setRobject("ventedSteamVolume", ventedSteamVolume, object);
        setRobject("ventedSteamTemperature", ventedSteamTemperature, object);
    }

    void mapFlashTank(const std::string &outputName) {
        logCommonStart(__func__, outputName);

        Local <String> localName = Nan::New<String>(outputName).ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        double inletWaterEnergyFlow = 0;
        double inletWaterMassFlow = 0;
        double inletWaterPressure = 0;
        double inletWaterQuality = 0;
        double inletWaterVolume = 0;
        double inletWaterSpecificEnthalpy = 0;
        double inletWaterSpecificEntropy = 0;
        double inletWaterTemperature = 0;
        double outletGasEnergyFlow = 0;
        double outletGasMassFlow = 0;
        double outletGasPressure = 0;
        double outletGasQuality = 0;
        double outletGasVolume = 0;
        double outletGasSpecificEnthalpy = 0;
        double outletGasSpecificEntropy = 0;
        double outletGasTemperature = 0;
        double outletLiquidEnergyFlow = 0;
        double outletLiquidMassFlow = 0;
        double outletLiquidPressure = 0;
        double outletLiquidQuality = 0;
        double outletLiquidVolume = 0;
        double outletLiquidSpecificEnthalpy = 0;
        double outletLiquidSpecificEntropy = 0;
        double outletLiquidTemperature = 0;

        setRobject("inletWaterEnergyFlow", inletWaterEnergyFlow, object);
        setRobject("inletWaterMassFlow", inletWaterMassFlow, object);
        setRobject("inletWaterPressure", inletWaterPressure, object);
        setRobject("inletWaterQuality", inletWaterQuality, object);
        setRobject("inletWaterVolume", inletWaterVolume, object);
        setRobject("inletWaterSpecificEnthalpy", inletWaterSpecificEnthalpy, object);
        setRobject("inletWaterSpecificEntropy", inletWaterSpecificEntropy, object);
        setRobject("inletWaterTemperature", inletWaterTemperature, object);
        setRobject("outletGasEnergyFlow", outletGasEnergyFlow, object);
        setRobject("outletGasMassFlow", outletGasMassFlow, object);
        setRobject("outletGasPressure", outletGasPressure, object);
        setRobject("outletGasQuality", outletGasQuality, object);
        setRobject("outletGasVolume", outletGasVolume, object);
        setRobject("outletGasSpecificEnthalpy", outletGasSpecificEnthalpy, object);
        setRobject("outletGasSpecificEntropy", outletGasSpecificEntropy, object);
        setRobject("outletGasTemperature", outletGasTemperature, object);
        setRobject("outletLiquidEnergyFlow", outletLiquidEnergyFlow, object);
        setRobject("outletLiquidMassFlow", outletLiquidMassFlow, object);
        setRobject("outletLiquidPressure", outletLiquidPressure, object);
        setRobject("outletLiquidQuality", outletLiquidQuality, object);
        setRobject("outletLiquidVolume", outletLiquidVolume, object);
        setRobject("outletLiquidSpecificEnthalpy", outletLiquidSpecificEnthalpy, object);
        setRobject("outletLiquidSpecificEntropy", outletLiquidSpecificEntropy, object);
        setRobject("outletLiquidTemperature", outletLiquidTemperature, object);
    }

    void mapBlowdownFlashTank() {
        logMappingStart(__func__);
        mapFlashTank("blowdownFlashTank");
    }

    void mapCondensateFlashTank() {
        logMappingStart(__func__);
        mapFlashTank("condensateFlashTank");
    }

    void mapHighPressureCondensateFlashTank() {
        logMappingStart(__func__);
        mapFlashTank("highPressureCondensateFlashTank");
    }

    void mapMediumPressureCondensateFlashTank() {
        logMappingStart(__func__);
        mapFlashTank("mediumPressureCondensateFlashTank");
    }

    void mapHeader() {
        logMappingStart(__func__);

        Local <String> localName = Nan::New<String>("headerOutput").ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        const double energyFlow = 0;
        const double massFlow = 0;
        const double pressure = 0;
        const double quality = 0;
        const double specificEnthalpy = 0;
        const double specificEntropy = 0;
        const double temperature = 0;
//this may not be needed on header output,
//used during php calculation, still working through this piece
//    HeatLossOutput heatLoss = ;

        setRobject("energyFlow", energyFlow, object);
        setRobject("massFlow", massFlow, object);
        setRobject("pressure", pressure, object);
        setRobject("quality", quality, object);
        setRobject("specificEnthalpy", specificEnthalpy, object);
        setRobject("specificEntropy", specificEntropy, object);
        setRobject("temperature", temperature, object);
        //setRobject("heatLoss", heatLoss, object);
    }

    void mapHeatLoss() {
        logMappingStart(__func__);

        Local <String> localName = Nan::New<String>("heatLossOutput").ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        const double heatLoss = 0;
        const double inletEnergyFlow = 0;
        const double inletMassFlow = 0;
        const double inletPressure = 0;
        const double inletQuality = 0;
        const double inletSpecificEnthalpy = 0;
        const double inletSpecificEntropy = 0;
        const double inletTemperature = 0;
        const double outletEnergyFlow = 0;
        const double outletMassFlow = 0;
        const double outletPressure = 0;
        const double outletQuality = 0;
        const double outletSpecificEnthalpy = 0;
        const double outletSpecificEntropy = 0;
        const double outletTemperature = 0;

        setRobject("heatLoss", heatLoss, object);
        setRobject("inletEnergyFlow", inletEnergyFlow, object);
        setRobject("inletMassFlow", inletMassFlow, object);
        setRobject("inletPressure", inletPressure, object);
        setRobject("inletQuality", inletQuality, object);
        setRobject("inletSpecificEnthalpy", inletSpecificEnthalpy, object);
        setRobject("inletSpecificEntropy", inletSpecificEntropy, object);
        setRobject("inletTemperature", inletTemperature, object);
        setRobject("outletEnergyFlow", outletEnergyFlow, object);
        setRobject("outletMassFlow", outletMassFlow, object);
        setRobject("outletPressure", outletPressure, object);
        setRobject("outletQuality", outletQuality, object);
        setRobject("outletSpecificEnthalpy", outletSpecificEnthalpy, object);
        setRobject("outletSpecificEntropy", outletSpecificEntropy, object);
        setRobject("outletTemperature", outletTemperature, object);
    }

    void mapPrv(const std::string &outputName) {
        logCommonStart(__func__, outputName);

        Local <String> localName = Nan::New<String>(outputName).ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        const double feedwaterEnergyFlow = 0;
        const double feedwaterMassFlow = 0;
        const double feedwaterPressure = 0;
        const double feedwaterQuality = 0;
        const double feedwaterVolume = 0;
        const double feedwaterSpecificEnthalpy = 0;
        const double feedwaterSpecificEntropy = 0;
        const double feedwaterTemperature = 0;
        const double inletEnergyFlow = 0;
        const double inletMassFlow = 0;
        const double inletPressure = 0;
        const double inletQuality = 0;
        const double inletVolume = 0;
        const double inletSpecificEnthalpy = 0;
        const double inletSpecificEntropy = 0;
        const double inletTemperature = 0;
        const double outletEnergyFlow = 0;
        const double outletMassFlow = 0;
        const double outletPressure = 0;
        const double outletQuality = 0;
        const double outletVolume = 0;
        const double outletSpecificEnthalpy = 0;
        const double outletSpecificEntropy = 0;
        const double outletTemperature = 0;

        setRobject("feedwaterEnergyFlow", feedwaterEnergyFlow, object);
        setRobject("feedwaterMassFlow", feedwaterMassFlow, object);
        setRobject("feedwaterPressure", feedwaterPressure, object);
        setRobject("feedwaterQuality", feedwaterQuality, object);
        setRobject("feedwaterVolume", feedwaterVolume, object);
        setRobject("feedwaterSpecificEnthalpy", feedwaterSpecificEnthalpy, object);
        setRobject("feedwaterSpecificEntropy", feedwaterSpecificEntropy, object);
        setRobject("feedwaterTemperature", feedwaterTemperature, object);
        setRobject("inletEnergyFlow", inletEnergyFlow, object);
        setRobject("inletMassFlow", inletMassFlow, object);
        setRobject("inletPressure", inletPressure, object);
        setRobject("inletQuality", inletQuality, object);
        setRobject("inletVolume", inletVolume, object);
        setRobject("inletSpecificEnthalpy", inletSpecificEnthalpy, object);
        setRobject("inletSpecificEntropy", inletSpecificEntropy, object);
        setRobject("inletTemperature", inletTemperature, object);
        setRobject("outletEnergyFlow", outletEnergyFlow, object);
        setRobject("outletMassFlow", outletMassFlow, object);
        setRobject("outletPressure", outletPressure, object);
        setRobject("outletQuality", outletQuality, object);
        setRobject("outletVolume", outletVolume, object);
        setRobject("outletSpecificEnthalpy", outletSpecificEnthalpy, object);
        setRobject("outletSpecificEntropy", outletSpecificEntropy, object);
        setRobject("outletTemperature", outletTemperature, object);
    }

    void mapHighPressureToMediumPressurePrv() {
        logMappingStart(__func__);
        mapPrv("highPressureToMediumPressurePrv");
    }

    void mapMediumPressureToLowPressurePrv() {
        logMappingStart(__func__);
        mapPrv("mediumPressureToLowPressurePrv");
    }

    void mapTurbine(const std::string &outputName) {
        logCommonStart(__func__, outputName);

        Local <String> localName = Nan::New<String>(outputName).ToLocalChecked();
        Local <Object> object = Nan::New<Object>();
        Nan::Set(r, localName, object);

        const double energyOut = 0;
        const double generatorEfficiency = 0;
        const double inletEnergyFlow = 0;
        const double inletPressure = 0;
        const double inletQuality = 0;
        const double inletVolume = 0;
        const double inletSpecificEnthalpy = 0;
        const double inletSpecificEntropy = 0;
        const double inletTemperature = 0;
        const double isentropicEfficiency = 0;
        const double massFlow = 0;
        const double outletEnergyFlow = 0;
        const double outletPressure = 0;
        const double outletQuality = 0;
        const double outletVolume = 0;
        const double outletSpecificEnthalpy = 0;
        const double outletSpecificEntropy = 0;
        const double outletTemperature = 0;
        const double powerOut = 0;
        const double outletIdealPressure = 0;
        const double outletIdealTemperature = 0;
        const double outletIdealSpecificEnthalpy = 0;
        const double outletIdealSpecificEntropy = 0;
        const double outletIdealQuality = 0;
        const double outletIdealVolume = 0;

        setRobject("energyOut", energyOut, object);
        setRobject("generatorEfficiency", generatorEfficiency, object);
        setRobject("inletEnergyFlow", inletEnergyFlow, object);
        setRobject("inletPressure", inletPressure, object);
        setRobject("inletQuality", inletQuality, object);
        setRobject("inletVolume", inletVolume, object);
        setRobject("inletSpecificEnthalpy", inletSpecificEnthalpy, object);
        setRobject("inletSpecificEntropy", inletSpecificEntropy, object);
        setRobject("inletTemperature", inletTemperature, object);
        setRobject("isentropicEfficiency", isentropicEfficiency, object);
        setRobject("massFlow", massFlow, object);
        setRobject("outletEnergyFlow", outletEnergyFlow, object);
        setRobject("outletPressure", outletPressure, object);
        setRobject("outletQuality", outletQuality, object);
        setRobject("outletVolume", outletVolume, object);
        setRobject("outletSpecificEnthalpy", outletSpecificEnthalpy, object);
        setRobject("outletSpecificEntropy", outletSpecificEntropy, object);
        setRobject("outletTemperature", outletTemperature, object);
        setRobject("powerOut", powerOut, object);
        setRobject("outletIdealPressure", outletIdealPressure, object);
        setRobject("outletIdealTemperature", outletIdealTemperature, object);
        setRobject("outletIdealSpecificEnthalpy", outletIdealSpecificEnthalpy, object);
        setRobject("outletIdealSpecificEntropy", outletIdealSpecificEntropy, object);
        setRobject("outletIdealQuality", outletIdealQuality, object);
        setRobject("outletIdealVolume", outletIdealVolume, object);
    }

    void mapCondensingTurbine() {
        logMappingStart(__func__);
        mapTurbine("condensingTurbine");
    }

    void mapHighPressureToMediumPressureTurbine() {
        logMappingStart(__func__);
        mapTurbine("highPressureToMediumPressureTurbine");
    }

    void mapHighPressureToLowPressureTurbine() {
        logMappingStart(__func__);
        mapTurbine("highPressureToLowPressureTurbine");
    }

    void mapMediumPressureToLowPressureTurbine() {
        logMappingStart(__func__);
        mapTurbine("mediumPressureToLowPressureTurbine");
    }
};

#endif //AMO_TOOLS_SUITE_STEAMMODELEROUTPUTDATAMAPPER_H
