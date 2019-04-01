#ifndef AMO_TOOLS_SUITE_STEAMMODELEROUTPUTDATAMAPPER_H
#define AMO_TOOLS_SUITE_STEAMMODELEROUTPUTDATAMAPPER_H

#include "../NanDataConverters.h"
#include <ssmt/Boiler.h>
#include <ssmt/Deaerator.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/SteamModelerOutput.h>
#include <ssmt/domain/EnergyAndCostCalculationsDomain.h>
#include <ssmt/domain/ReturnCondensateCalculationsDomain.h>

class SteamModelerOutputDataMapper {
public:
    const void map(const SteamModelerOutput &steamModelerOutput) {
        const std::string methodName = "SteamModelerOutputDataMapper::map";

        logSection(methodName + ": converting to output: begin");

        const EnergyAndCostCalculationsDomain &energyAndCostCalculationsDomain = steamModelerOutput.energyAndCostCalculationsDomain;
        const Boiler &boiler = steamModelerOutput.boiler;
        const std::shared_ptr<FlashTank> &blowdownFlashTank = steamModelerOutput.blowdownFlashTank;
        const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain = steamModelerOutput.highPressureHeaderCalculationsDomain;
        const Deaerator &deaerator = steamModelerOutput.deaerator;
        const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain = steamModelerOutput.lowPressureHeaderCalculationsDomain;
        const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain = steamModelerOutput.makeupWaterAndCondensateHeaderCalculationsDomain;
        const ProcessSteamUsageCalculationsDomain &processSteamUsageCalculationsDomain = steamModelerOutput.processSteamUsageCalculationsDomain;
        const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain = steamModelerOutput.mediumPressureHeaderCalculationsDomain;
        const PowerBalanceCheckerCalculationsDomain &powerBalanceCheckerCalculationsDomain = steamModelerOutput.powerBalanceCheckerCalculationsDomain;

        const ReturnCondensateCalculationsDomain &returnCondensateCalculationsDomain = makeupWaterAndCondensateHeaderCalculationsDomain.returnCondensateCalculationsDomain;
        const std::shared_ptr<FlashTank> &condensateFlashTank = returnCondensateCalculationsDomain.condensateFlashTank;

        const SteamSystemModelerTool::FluidProperties &makeupWater = makeupWaterAndCondensateHeaderCalculationsDomain.makeupWater;
        const SteamSystemModelerTool::FluidProperties &makeupWaterAndCondensateHeaderOutput = makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterAndCondensateHeaderOutput;

        const MakeupWaterVolumeFlowCalculationsDomain &makeupWaterVolumeFlowCalculationsDomain = makeupWaterAndCondensateHeaderCalculationsDomain.makeupWaterVolumeFlowCalculationsDomain;

        const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank = highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;
        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput = highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
        const std::shared_ptr<Turbine> &condensingTurbine = highPressureHeaderCalculationsDomain.condensingTurbine;
        const std::shared_ptr<Turbine> &highToMediumPressureTurbine = highPressureHeaderCalculationsDomain.highToMediumPressureTurbine;
        const std::shared_ptr<Turbine> &highToLowPressureTurbine = highPressureHeaderCalculationsDomain.highToLowPressureTurbine;

        const ProcessSteamUsage &highPressureProcessSteamUsage = processSteamUsageCalculationsDomain.highPressureProcessSteamUsage;

        const std::shared_ptr<SteamSystemModelerTool::FluidProperties> &lowPressureVentedSteam = powerBalanceCheckerCalculationsDomain.lowPressureVentedSteam;

        // always in output
        mapOperations(energyAndCostCalculationsDomain, makeupWaterVolumeFlowCalculationsDomain);
        mapBoiler(boiler);
        mapDeaerator(deaerator);
        mapHighPressureHeaderSteam(highPressureHeaderOutput);
        mapMakeupWater(makeupWater);
        mapMakeupWaterAndCondensate(makeupWaterAndCondensateHeaderOutput);
        mapHighPressureProcessSteamUsage(highPressureProcessSteamUsage);

        // optional turbines 0-4
        mapCondensingTurbine(condensingTurbine);
        mapHighToMediumPressureTurbine(highToMediumPressureTurbine);
        mapHighToLowPressureTurbine(highToLowPressureTurbine);

        if (mediumPressureHeaderCalculationsDomain == nullptr) {
            std::cout << methodName << ": mediumPressureHeaderCalculationsDomain is null, skipping output mapping"
                      << std::endl;
            makeOutputObject("mediumPressureHeaderSteam");
            makeOutputObject("mediumPressureToLowPressureTurbine");
            makeOutputObject("highPressureToMediumPressurePrv");
        } else {
            const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput =
                    mediumPressureHeaderCalculationsDomain->mediumPressureHeaderOutput;
            mapMediumPressureHeaderSteam(mediumPressureHeaderOutput);

            const std::shared_ptr<Turbine> &mediumToLowPressureTurbine =
                    mediumPressureHeaderCalculationsDomain->mediumToLowPressureTurbine;
            mapMediumToLowPressureTurbine(mediumToLowPressureTurbine);

            const std::shared_ptr<PrvWithoutDesuperheating> &highToMediumPressurePrv =
                    mediumPressureHeaderCalculationsDomain->highToMediumPressurePrv;
            mapHighToMediumPressurePrv(highToMediumPressurePrv);
        }

        //0-4 flash tanks
        mapBlowdownFlashTank(blowdownFlashTank);
        mapCondensateFlashTank(condensateFlashTank);
        mapHighPressureCondensateFlashTank(highPressureCondensateFlashTank);

        if (lowPressureHeaderCalculationsDomain == nullptr) {
            std::cout << methodName << ": lowPressureHeaderCalculationsDomain is null, skipping output mapping"
                      << std::endl;
            makeOutputObject("mediumPressureCondensateFlashTank");
            makeOutputObject("lowPressureHeaderSteam");
            makeOutputObject("mediumPressureToLowPressurePrv");
        } else {
            const LowPressureFlashedSteamIntoHeaderCalculatorDomain &lowPressureFlashedSteamIntoHeaderCalculatorDomain =
                    lowPressureHeaderCalculationsDomain->lowPressureFlashedSteamIntoHeaderCalculatorDomain;
            const std::shared_ptr<FlashTank> &mediumPressureCondensateFlashTank =
                    lowPressureFlashedSteamIntoHeaderCalculatorDomain.mediumPressureCondensateFlashTank;
            mapMediumPressureCondensateFlashTank(mediumPressureCondensateFlashTank);

            const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput =
                    lowPressureHeaderCalculationsDomain->lowPressureHeaderOutput;
            mapLowPressureHeaderSteam(lowPressureHeaderOutput);

            const std::shared_ptr<PrvWithoutDesuperheating> &lowPressurePrv =
                    lowPressureHeaderCalculationsDomain->lowPressurePrv;
            mapMediumToLowPressurePrv(lowPressurePrv);
        }

        mapLowPressureVentedSteam(lowPressureVentedSteam);

        logSection(methodName + ": converting to output: end");
    }

private:
    Local <Object> makeOutputObject(const std::string &outputName) {
        return makeOutputObjectOnObject(outputName, r);
    }

    Local <Object> makeOutputObjectOnObject(const std::string &outputName, Local <Object> onObject) {
        Local <Object> object = Nan::New<Object>();
        Local <String> localName = Nan::New<String>(outputName).ToLocalChecked();
        Nan::Set(onObject, localName, object);
        return object;
    }

    void logSection(const std::string &message) const {
        std::cout << std::endl;
        std::cout << "======== " << std::endl;
        std::cout << "======== " << message << std::endl;
        std::cout << "======== " << std::endl;
    }

    static void logMappingStart(const std::string &methodName) {
        std::cout << "==== " << methodName << ": begin" << std::endl;
    }

    static void logCommonStart(const std::string &methodName, const std::string &outputName) {
        std::cout << methodName << ": begin: outputName=" << outputName << std::endl;
    }

    void
    mapFluidPropertiesToObject(const std::string &variableNamePrefix,
                               const SteamSystemModelerTool::FluidProperties &properties, Local <Object> object) {
        std::cout << "SteamModelerOutputDataMapper::" << __func__ << ": variableNamePrefix=" << variableNamePrefix
                  << std::endl;

        const double pressure = properties.pressure;
        const double temperature = properties.temperature;
        const double specificEnthalpy = properties.specificEnthalpy;
        const double specificEntropy = properties.specificEntropy;
        const double quality = properties.quality;
        const double volume = properties.specificVolume;
        const double massFlow = properties.massFlow;
        const double energyFlow = properties.energyFlow;

        setRobject(variableNamePrefix + "Pressure", pressure, object);
        setRobject(variableNamePrefix + "Temperature", temperature, object);
        setRobject(variableNamePrefix + "SpecificEnthalpy", specificEnthalpy, object);
        setRobject(variableNamePrefix + "SpecificEntropy", specificEntropy, object);
        setRobject(variableNamePrefix + "Quality", quality, object);
        setRobject(variableNamePrefix + "Volume", volume, object);
        setRobject(variableNamePrefix + "MassFlow", massFlow, object);
        setRobject(variableNamePrefix + "EnergyFlow", energyFlow, object);
    }

    void
    mapFluidProperties(const std::string &outputName, const SteamSystemModelerTool::FluidProperties &properties) {
        logCommonStart(__func__, outputName);

        Local <Object> object = makeOutputObject(outputName);

        const double pressure = properties.pressure;
        const double temperature = properties.temperature;
        const double specificEnthalpy = properties.specificEnthalpy;
        const double specificEntropy = properties.specificEntropy;
        const double quality = properties.quality;
        const double specificVolume = properties.specificVolume;
        const double massFlow = properties.massFlow;
        const double energyFlow = properties.energyFlow;

        setRobject("pressure", pressure, object);
        setRobject("temperature", temperature, object);
        setRobject("specificEnthalpy", specificEnthalpy, object);
        setRobject("specificEntropy", specificEntropy, object);
        setRobject("quality", quality, object);
        setRobject("specificVolume", specificVolume, object);
        setRobject("massFlow", massFlow, object);
        setRobject("energyFlow", energyFlow, object);
    }

    void
    mapSteamProperties(const std::string &outputName, const SteamSystemModelerTool::SteamPropertiesOutput &properties) {
        logCommonStart(__func__, outputName);

        Local <Object> object = makeOutputObject(outputName);

        const double pressure = properties.pressure;
        const double temperature = properties.temperature;
        const double specificEnthalpy = properties.specificEnthalpy;
        const double specificEntropy = properties.specificEntropy;
        const double quality = properties.quality;
        const double specificVolume = properties.specificVolume;

        setRobject("pressure", pressure, object);
        setRobject("temperature", temperature, object);
        setRobject("specificEnthalpy", specificEnthalpy, object);
        setRobject("specificEntropy", specificEntropy, object);
        setRobject("quality", quality, object);
        setRobject("specificVolume", specificVolume, object);
    }

    void
    mapProcessSteamUsage(const std::string &outputName, const ProcessSteamUsage &processSteamUsage) {
        logCommonStart(__func__, outputName);

        Local <Object> object = makeOutputObject(outputName);

        const double energyFlow = processSteamUsage.energyFlow;
        const double massFlow = processSteamUsage.massFlow;
        const double temperature = processSteamUsage.temperature;
        const double pressure = processSteamUsage.pressure;
        const double processUsage = processSteamUsage.processUsage;

        setRobject("energyFlow", energyFlow, object);
        setRobject("massFlow", massFlow, object);
        setRobject("temperature", temperature, object);
        setRobject("pressure", pressure, object);
        setRobject("processUsage", processUsage, object);
    }

    void mapOperations(const EnergyAndCostCalculationsDomain &energyDomain,
                       const MakeupWaterVolumeFlowCalculationsDomain &waterDomain) {
        logMappingStart(__func__);

        Local <Object> object = makeOutputObject("operationsOutput");

        const double powerGenerated = energyDomain.powerGenerated;
        const double boilerFuelCost = energyDomain.boilerFuelCost;
        const double makeupWaterCost = energyDomain.makeupWaterCost;
        const double totalOperatingCost = energyDomain.totalOperatingCost;
        const double powerGenerationCost = energyDomain.powerGenerationCost;
        const double boilerFuelUsage = energyDomain.boilerFuelUsage;
        const double sitePowerImport = energyDomain.sitePowerImport;
        const double sitePowerDemand = energyDomain.powerDemand;

        const double makeupWaterVolumeFlow = waterDomain.makeupWaterVolumeFlow;
        const double makeupWaterVolumeFlowAnnual = waterDomain.makeupWaterVolumeFlowAnnual;

        setRobject("powerGenerated", powerGenerated, object);
        setRobject("boilerFuelCost", boilerFuelCost, object);
        setRobject("makeupWaterCost", makeupWaterCost, object);
        setRobject("totalOperatingCost", totalOperatingCost, object);
        setRobject("powerGenerationCost", powerGenerationCost, object);
        setRobject("boilerFuelUsage", boilerFuelUsage, object);
        setRobject("sitePowerImport", sitePowerImport, object);
        setRobject("sitePowerDemand", sitePowerDemand, object);

        setRobject("makeupWaterVolumeFlow", makeupWaterVolumeFlow, object);
        setRobject("makeupWaterVolumeFlowAnnual", makeupWaterVolumeFlowAnnual, object);
    }

    void mapBoiler(const Boiler &boiler) {
        logMappingStart(__func__);

        Local <Object> object = makeOutputObject("boilerOutput");

        const SteamSystemModelerTool::FluidProperties &steamProperties = boiler.getSteamProperties();
        const SteamSystemModelerTool::FluidProperties &blowdownProperties = boiler.getBlowdownProperties();
        const SteamSystemModelerTool::FluidProperties &feedwaterProperties = boiler.getFeedwaterProperties();

        mapFluidPropertiesToObject("steam", steamProperties, object);
        mapFluidPropertiesToObject("blowdown", blowdownProperties, object);
        mapFluidPropertiesToObject("feedwater", feedwaterProperties, object);

        const double boilerEnergy = boiler.getBoilerEnergy();
        const double fuelEnergy = boiler.getFuelEnergy();
        const double blowdownRate = boiler.getBlowdownRate();
        const double combustionEff = boiler.getCombustionEfficiency();

        setRobject("boilerEnergy", boilerEnergy, object);
        setRobject("fuelEnergy", fuelEnergy, object);
        setRobject("blowdownRate", blowdownRate, object);
        setRobject("combustionEff", combustionEff, object);
    }

    void mapHighPressureHeaderSteam(const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) {
        logMappingStart(__func__);
        mapFluidProperties("highPressureHeaderSteam", highPressureHeaderOutput);
    }

    void mapMakeupWater(const SteamSystemModelerTool::FluidProperties &makeupWater) {
        logMappingStart(__func__);
        mapFluidProperties("makeupWater", makeupWater);
    }

    void
    mapMakeupWaterAndCondensate(const SteamSystemModelerTool::FluidProperties &makeupWaterAndCondensateHeaderOutput) {
        logMappingStart(__func__);
        mapFluidProperties("makeupWaterAndCondensate", makeupWaterAndCondensateHeaderOutput);
    }

    void mapHighPressureProcessSteamUsage(const ProcessSteamUsage &highPressureProcessSteamUsage) {
        logMappingStart(__func__);
        mapProcessSteamUsage("highPressureProcessSteamUsage", highPressureProcessSteamUsage);
    }

    void mapMediumPressureHeaderSteam(const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) {
        logMappingStart(__func__);
        mapFluidProperties("mediumPressureHeaderSteam", mediumPressureHeaderOutput);
    }

    void mapLowPressureHeaderSteam(const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput) {
        logMappingStart(__func__);
        mapFluidProperties("lowPressureHeaderSteam", lowPressureHeaderOutput);
    }

    void mapLowPressureVentedSteam(
            const std::shared_ptr<SteamSystemModelerTool::FluidProperties> &lowPressureVentedSteamPtr) {
        logMappingStart(__func__);
        if (lowPressureVentedSteamPtr == nullptr) {
            std::cout << "SteamModelerOutputDataMapper::" << __func__
                      << ": lowPressureVentedSteam is null, skipping output mapping" << std::endl;
            makeOutputObject("lowPressureVentedSteam");
        } else {
            SteamSystemModelerTool::FluidProperties lowPressureVentedSteam = *lowPressureVentedSteamPtr;
            mapFluidProperties("lowPressureVentedSteam", lowPressureVentedSteam);
        }
    }

    void mapDeaerator(const Deaerator &deaerator) {
        logMappingStart(__func__);

        Local <Object> object = makeOutputObject("deaeratorOutput");

        const SteamSystemModelerTool::FluidProperties &feedwaterProperties = deaerator.getFeedwaterProperties();
        const SteamSystemModelerTool::FluidProperties &inletSteamProperties = deaerator.getInletSteamProperties();
        const SteamSystemModelerTool::FluidProperties &inletWaterProperties = deaerator.getInletWaterProperties();
        const SteamSystemModelerTool::FluidProperties &ventedSteamProperties = deaerator.getVentedSteamProperties();

        mapFluidPropertiesToObject("feedwater", feedwaterProperties, object);
        mapFluidPropertiesToObject("inletSteam", inletSteamProperties, object);
        mapFluidPropertiesToObject("inletWater", inletWaterProperties, object);
        mapFluidPropertiesToObject("ventedSteam", ventedSteamProperties, object);
    }

    void mapFlashTank(const std::string &outputName, const std::shared_ptr<FlashTank> &flashTank) {
        logCommonStart(__func__, outputName);

        Local <Object> object = makeOutputObject(outputName);

        if (flashTank == nullptr) {
            std::cout << "SteamModelerOutputDataMapper::" << __func__ << ": flashTank '" << outputName
                      << "' is null, skipping output mapping" << std::endl;
            makeOutputObjectOnObject("inletWater", object);
            makeOutputObjectOnObject("outletGas", object);
            makeOutputObjectOnObject("outletLiquid", object);
        } else {
            const SteamSystemModelerTool::FluidProperties &inletWaterProperties = flashTank->getInletWaterProperties();
            const SteamSystemModelerTool::FluidProperties &outletGasSaturatedProperties = flashTank->getOutletGasSaturatedProperties();
            const SteamSystemModelerTool::FluidProperties &outletLiquidSaturatedProperties = flashTank->getOutletLiquidSaturatedProperties();

            mapFluidPropertiesToObject("inletWater", inletWaterProperties, object);
            mapFluidPropertiesToObject("outletGas", outletGasSaturatedProperties, object);
            mapFluidPropertiesToObject("outletLiquid", outletLiquidSaturatedProperties, object);
        }
    }

    void mapBlowdownFlashTank(const std::shared_ptr<FlashTank> &flashTank) {
        logMappingStart(__func__);
        mapFlashTank("blowdownFlashTank", flashTank);
    }

    void mapCondensateFlashTank(const std::shared_ptr<FlashTank> &flashTank) {
        logMappingStart(__func__);
        mapFlashTank("condensateFlashTank", flashTank);
    }

    void mapHighPressureCondensateFlashTank(std::shared_ptr<FlashTank> const &flashTank) {
        logMappingStart(__func__);
        mapFlashTank("highPressureCondensateFlashTank", flashTank);
    }

    void mapMediumPressureCondensateFlashTank(std::shared_ptr<FlashTank> const &flashTank) {
        logMappingStart(__func__);
        mapFlashTank("mediumPressureCondensateFlashTank", flashTank);
    }

    void
    mapPrv(const std::string &outputName, const std::shared_ptr<PrvWithoutDesuperheating> &prv) {
        logCommonStart(__func__, outputName);

        Local <Object> object = makeOutputObject(outputName);

        if (prv == nullptr) {
            std::cout << "SteamModelerOutputDataMapper::" << __func__ << ": for " << outputName
                      << ", prv is null, skipping output mapping"
                      << std::endl;
        } else {
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
    }

    void mapHighToMediumPressurePrv(const std::shared_ptr<PrvWithoutDesuperheating> &highToMediumPressurePrv) {
        logMappingStart(__func__);
        mapPrv("highPressureToMediumPressurePrv", highToMediumPressurePrv);
    }

    void mapMediumToLowPressurePrv(const std::shared_ptr<PrvWithoutDesuperheating> &lowPressurePrv) {
        logMappingStart(__func__);
        mapPrv("mediumPressureToLowPressurePrv", lowPressurePrv);
    }

    void mapTurbine(const std::string &outputName, const std::shared_ptr<Turbine> &turbine) {
        logCommonStart(__func__, outputName);

        Local <Object> object = makeOutputObject(outputName);

        if (turbine == nullptr) {
            std::cout << "SteamModelerOutputDataMapper::" << __func__ << ": for " << outputName
                      << ", turbine is null, skipping output mapping"
                      << std::endl;
        } else {
            const SteamSystemModelerTool::SteamPropertiesOutput &inletProperties = turbine->getInletProperties();
            const SteamSystemModelerTool::SteamPropertiesOutput &outletProperties = turbine->getOutletProperties();

            const double energyOut = turbine->getEnergyOut();
            const double generatorEfficiency = turbine->getGeneratorEfficiency();

            const double inletEnergyFlow = turbine->getInletEnergyFlow();
            const double inletPressure = inletProperties.pressure;
            const double inletQuality = inletProperties.quality;
            const double inletVolume = inletProperties.specificVolume;
            const double inletSpecificEnthalpy = inletProperties.specificEnthalpy;
            const double inletSpecificEntropy = inletProperties.specificEntropy;
            const double inletTemperature = inletProperties.temperature;

            const double isentropicEfficiency = turbine->getIsentropicEfficiency();
            const double massFlow = turbine->getMassFlow();
            const double outletEnergyFlow = turbine->getOutletEnergyFlow();
            const double outletPressure = outletProperties.pressure;
            const double outletQuality = outletProperties.quality;
            const double outletVolume = outletProperties.specificVolume;
            const double outletSpecificEnthalpy = outletProperties.specificEnthalpy;
            const double outletSpecificEntropy = outletProperties.specificEntropy;
            const double outletTemperature = outletProperties.temperature;
            const double powerOut = turbine->getPowerOut();

            //FIXME what are "outletIdeal*" sources?
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
    }

    void mapCondensingTurbine(const std::shared_ptr<Turbine> &condensingTurbine) {
        logMappingStart(__func__);
        mapTurbine("condensingTurbine", condensingTurbine);
    }

    void mapHighToMediumPressureTurbine(const std::shared_ptr<Turbine> &highToMediumPressureTurbine) {
        logMappingStart(__func__);
        mapTurbine("highPressureToMediumPressureTurbine", highToMediumPressureTurbine);
    }

    void mapHighToLowPressureTurbine(const std::shared_ptr<Turbine> &highToLowPressureTurbine) {
        logMappingStart(__func__);
        mapTurbine("highPressureToLowPressureTurbine", highToLowPressureTurbine);
    }

    void mapMediumToLowPressureTurbine(const std::shared_ptr<Turbine> &mediumToLowPressureTurbine) {
        logMappingStart(__func__);
        mapTurbine("mediumPressureToLowPressureTurbine", mediumToLowPressureTurbine);
    }
};

#endif //AMO_TOOLS_SUITE_STEAMMODELEROUTPUTDATAMAPPER_H
