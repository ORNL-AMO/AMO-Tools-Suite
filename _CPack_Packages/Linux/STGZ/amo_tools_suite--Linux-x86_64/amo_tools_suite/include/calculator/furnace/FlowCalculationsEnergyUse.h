/**
 * @file
 * @brief Calculator for flow calculations energy use for fuel-fired furnaces
 *
 * This contains the inputs for calculating the flow calculations energy use fuel-fired furnaces.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_FLOWCALCULATIONSENERGYUSE_H
#define AMO_TOOLS_SUITE_FLOWCALCULATIONSENERGYUSE_H
/**
 * Flow Calculations Energy Use calculator class
 * Used to find the flow and the heat input of a fuel-fired furnace.
 */
class FlowCalculationsEnergyUse {
public:

    ///enum class for gas types
    enum class Gas {
        AIR,
        AMMONIA_DISSOCIATED,
        ARGON,
        BUTANE,
        ENDOTHERMIC_AMMONIA,
        EXOTHERMIC_CRACKED_LEAN,
        EXOTHERMIC_CRACKED_RICH,
        HELIUM,
        HYDROGEN,
        NATURAL_GAS,
        NITROGEN,
        OXYGEN,
        PROPANE,
        OTHER
    };

    ///enum class for section type
    enum class Section {
        SQUARE_EDGE,
        SHARP_EDGE,
        VENTURI
    };

    /**
     *
     * Constructor for the flow calculations energy use
     *
     * @param gasType Gas, type of gas
     * @param specificGravity double, specific gravity specified by the user- unitless
     * @param orificeDiameter double, diameter of orifice in inches
     * @param insidePipeDiameter double, diameter of inside pipe in inches
     * @param sectionType Section, type of section
     * @param dischargeCoefficient double, coefficient of discharge - unitless
     * @param gasHeatingValue double, heating value of gas in Btu/scf
     * @param gasTemperature double, temperature of gas in °F
     * @param gasPressure double, pressure of gas in Psig
     * @param orificePressureDrop double, orifice pressure drop in inch W.C.
     * @param operatingTime double, operating time in hrs
     *
     *
     * */
    FlowCalculationsEnergyUse(
            Gas gasType,
            double specificGravity,
            double orificeDiameter,
            double insidePipeDiameter,
            Section sectionType,
            double dischargeCoefficient,
            double gasHeatingValue,
            double gasTemperature,
            double gasPressure,
            double orificePressureDrop,
            double operatingTime)
            : gasType_(gasType),
              specificGravity_(specificGravity),
              orificeDiameter_(orificeDiameter),
              insidePipeDiameter_(insidePipeDiameter),
              sectionType_(sectionType),
              dischargeCoefficient_(dischargeCoefficient),
              gasHeatingValue_(gasHeatingValue),
              gasTemperature_(gasTemperature),
              gasPressure_(gasPressure),
              orificePressureDrop_(orificePressureDrop),
              operatingTime_(operatingTime)

    {
        area_ = 0.0;
        adjustedDischargeCoefficient_ = 0.0;
        pressureDrop_ = 0.0;
        adjustedGasTemperature_ = 0.0;
        adjustedGasPressure_ = 0.0;
        flow_ = 0.0;
        heatInput_ = 0.0;

    }

    FlowCalculationsEnergyUse() = default;

    /**
     * Gets the type of gas
     *
     * @return Gas, type of gas
     */
    Gas getGasType() const {
        return gasType_;
    }

    /**
     * Sets the type of gas
     *
     * @param gasType Gas, type of gas
     *
     */
    void setGasType(Gas gasType) {
        gasType_ = gasType;

        switch(gasType) {
            case Gas::AIR:
                specificGravity_ = 1;
            case Gas::AMMONIA_DISSOCIATED:
                specificGravity_ = 0.3;
            case Gas::ARGON:
                specificGravity_ = 1.38;
            case Gas::BUTANE:
                specificGravity_ = 2.02;
            case Gas::ENDOTHERMIC_AMMONIA:
                specificGravity_ = 0.59;
            case Gas::EXOTHERMIC_CRACKED_LEAN:
                specificGravity_ = 1;
            case Gas::EXOTHERMIC_CRACKED_RICH:
                specificGravity_ = 0.85;
            case Gas::HELIUM:
                specificGravity_ = 0.14;
            case Gas::HYDROGEN:
                specificGravity_ = 0.07;
            case Gas::NATURAL_GAS:
                specificGravity_ = 0.65;
            case Gas::NITROGEN:
                specificGravity_ = 0.96;
            case Gas::OXYGEN:
                specificGravity_ = 1.11;
            case Gas::PROPANE:
                specificGravity_ = 1.52;
            case Gas::OTHER:
                specificGravity_ = 0.0;
        }
    }

    /**
     * Gets the specific gravity
     *
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity_;
    }

    /**
     * Sets the specific gravity using a value
     *
     * @param specificGravity double, specific gravity - unitless
     *
     */
    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

    /**
     * Gets the diameter of orifice
     *
     * @return double, diameter of orifice in inches
     */
    double getOrificeDiameter() const {
        return orificeDiameter_;
    }

    /**
     * Sets the diameter of orifice
     *
     * @param orificeDiameter double, diameter of orifice
     *
     */
    void setOrificeDiameter(double orificeDiameter) {
        orificeDiameter_ = orificeDiameter;
    }

    /**
     * Gets the diameter of inside of pipe
     *
     * @return double, diameter of inside of pipe in inches
     */
    double getInsidePipeDiameter() const {
        return insidePipeDiameter_;
    }

    /**
     * Sets the diameter of inside of pipe
     *
     * @param insidePipeDiameter double, diameter of inside of pipe
     *
     */
    void setInsidePipeDiameter(double insidePipeDiameter) {
        insidePipeDiameter_ = insidePipeDiameter;
    }

    /**
     * Gets the type of section
     *
     * @return Section, type of section
     */
    Section getSectionType() const {
        return sectionType_;
    }

    /**
     * Sets the type of section
     *
     * @param sectionType Section, type of section
     *
     */
    void setSectionType(Section sectionType) {
        sectionType_ = sectionType;

        switch(sectionType) {
            case Section::SHARP_EDGE:
                dischargeCoefficient_ = 0.6;
            case Section::SQUARE_EDGE:
                dischargeCoefficient_ = 0.5;
            case Section::VENTURI:
                dischargeCoefficient_ = 0.8;
        }
    }

    /**
     * Gets the coefficient of discharge
     *
     * @return double, coefficient of discharge - unitless
     */
    double getDischargeCoefficient() const {
        return dischargeCoefficient_;
    }

    /**
     * Sets the coefficient of discharge
     *
     * @param dischargeCoefficient double coefficient of discharge - unitless
     *
     */
    void setDischargeCoefficient(double dischargeCoefficient) {
        dischargeCoefficient_ = dischargeCoefficient;
    }

    /**
     * Gets the gas heating value
     *
     * @return double, gas heating value in Btu/scf
     */
    double getGasHeatingValue() const {
        return gasHeatingValue_;
    }

    /**
     * Sets the gas heating value
     *
     * @param gasHeatingValue double, gas heating value in Btu/scf
     *
     */
    void setGasHeatingValue(double gasHeatingValue) {
        gasHeatingValue_ = gasHeatingValue;
    }

    /**
     * Gets the temperature of gas in °F
     *
     * @return double, gas temperature in °F
     */
    double getGasTemperature() const {
        return gasTemperature_;
    }

    /**
     * Sets the temperature of gas
     *
     * @param gasTemperature double, temperature of gas in °F
     *
     */
    void setGasTemperature(double gasTemperature) {
        gasTemperature_ = gasTemperature;
    }

    /**
     * Gets the pressure of gas
     *
     * @return double, pressure of gas in Psig
     */
    double getGasPressure() const {
        return gasPressure_;
    }

    /**
     * Sets the pressure of gas
     *
     * @param gasPressure double, pressure of gas in Psig
     *
     */
    void setGasPressure(double gasPressure) {
        gasPressure_ = gasPressure;
    }

    /**
     * Gets the pressure drop at orifice
     *
     * @return double, pressure drop at orifice in inch W.C.
     */
    double getOrificePressureDrop() const {
        return orificePressureDrop_;
    }

    /**
     * Sets the pressure drop at orifice
     *
     * @param orificePressureDrop double, pressure drop at orifice in inch W.C.
     *
     */
    void setOrificePressureDrop(double orificePressureDrop) {
        orificePressureDrop_ = orificePressureDrop;
    }

    /**
     * Gets the operating time
     *
     * @return double, operating time in hrs
     */
    double getOperatingTime() const {
        return operatingTime_;
    }

    /**
     * Sets the operating time
     *
     * @param operatingTime double, operating time in hrs
     *
     */
    void setOperatingTime(double operatingTime) {
        operatingTime_ = operatingTime;
    }


    /**
     * Gets the area
     *
     * @return double, area in in in^2
     */
    double getArea();

    /**
     * Gets the adjusted (if necessary) discharge coefficient
     *
     * @return double, adjusted discharge coefficient - unitless
     */
    double getAdjustedDischargeCoefficient();

    /**
     * Gets the pressure drop in inch W.C.
     *
     * @return double, pressure drop in inch W.C.
     */
    double getPressureDrop();

    /**
     * Gets the adjusted temperature of gas used in calculating flow
     *
     * @return double, adjusted temperature of gas in °F
     */
    double getAdjustedGasTemperature();

    /**
     * Gets the adjusted pressure of gas used in calculating flow
     *
     * @return double, adjusted pressure of gas in Psig
     */
    double getAdjustedGasPressure();

    /**
     * Gets the flow in scfh
     *
     * @return double, flow in scfh
     */
    double getFlow();

    /**
     * Gets the heat input
     *
     * @return double, heat input in Million Btu
     */
    double getHeatInput();

/**
 * Gets the total flow in scf
 *
 * @return double, total flow in scf
 */

    double getTotalFlow();

private:
    // In values
    FlowCalculationsEnergyUse::Gas gasType_;
    double specificGravity_ = 0.0;
    double orificeDiameter_ = 0.0;
    double insidePipeDiameter_ = 0.0;
    FlowCalculationsEnergyUse::Section sectionType_;
    double dischargeCoefficient_ = 0.0;
    double gasHeatingValue_ = 0.0;
    double gasTemperature_ = 0.0;
    double gasPressure_ = 0.0;
    double orificePressureDrop_ = 0.0;
    double operatingTime_ = 0.0;


    // Out values
    double area_;
    double adjustedDischargeCoefficient_;
    double pressureDrop_;
    double adjustedGasTemperature_;
    double adjustedGasPressure_;
    double flow_;
    double heatInput_;
    double totalflow_;
};



#endif //AMO_TOOLS_SUITE_FLOWCALCULATIONSENERGYUSE_H
