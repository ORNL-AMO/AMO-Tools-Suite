/**
 * @file
 * @brief Calculator for total heat of solid load/charge material
 *
 * This contains the inputs for calculating a solid load/charge material's
 * total heat.
 *
 * @author Mark Adams
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */


#ifndef AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
#define AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H

#include <string>
#include "LoadChargeMaterial.h"

/**
 * Solid Load Charge Material class
 * Contains all of the properties of a solid load charge material
 * Used to calculate the heat required for a solid load charge material to tbe heated from the inlet temperature to the outlet temperature
 */
class SolidLoadChargeMaterial {
public:

    /**
 * Constructor for the solid load/charge material with all inputs specified.
 * @param thermicReactionType LoadChargeMaterial::ThermicReactionType, Enumerated value for either endothermic or exothermic reactions
 * @param specificHeatSolid double, Average specific heat of the solid material (dry) in Btu/(lb*°F)
 * @param latentHeat double, Latent heat of fusion in Btu/(lb)
 * @param specificHeatLiquid double, Specific heat of liquid from molten material in Btu/(lb*°F)
 * @param meltingPoint double, The melting point of the material in °F
 * @param chargeFeedRate double, Charge (wet)-feed rate in lb/hr
 * @param waterContentCharged double, Water content as charged (%)
 * @param waterContentDischarged double, Water content as discharged (%)
 * @param initialTemperature double, Initial temperature in °F
 * @param dischargeTemperature double, Charge material discharge temperature in °F
 * @param waterVaporDischargeTemperature double, Water vapor discharge temperature in °F
 * @param chargeMelted double, Charge melted (% of dry charge)
 * @param chargeReacted double, Charge Reacted (% of dry charge) in %
 * @param reactionHeat double, Heat of reaction in Btu/lb
 * @param additionalHeat double, Additional heat required in Btu/h
 * */
    SolidLoadChargeMaterial(
            const LoadChargeMaterial::ThermicReactionType thermicReactionType,
            const double specificHeatSolid,
            const double latentHeat,
            const double specificHeatLiquid,
            const double meltingPoint,
            const double chargeFeedRate,
            const double waterContentCharged,
            const double waterContentDischarged,
            const double initialTemperature,
            const double dischargeTemperature,
            const double waterVaporDischargeTemperature,
            const double chargeMelted,
            const double chargeReacted,
            const double reactionHeat,
            const double additionalHeat
    ) : thermicReactionType (thermicReactionType),
        specificHeatSolid(specificHeatSolid),
        latentHeat(latentHeat),
        specificHeatLiquid(specificHeatLiquid),
        meltingPoint(meltingPoint),
        chargeFeedRate(chargeFeedRate),
        waterContentCharged(waterContentCharged / 100.0),
        waterContentDischarged(waterContentDischarged / 100.0),
        initialTemperature(initialTemperature),
        dischargeTemperature(dischargeTemperature),
        waterVaporDischargeTemperature(waterVaporDischargeTemperature),
        chargeMelted(chargeMelted / 100.0),
        chargeReacted(chargeReacted / 100.0),
        reactionHeat(reactionHeat),
        additionalHeat(additionalHeat)
    {}

    SolidLoadChargeMaterial() = default;

    /**
     * Gets the thermic reaction type
     * @return LoadChargeMaterial::ThermicReactionType classification of thermic reaction type
     */
    LoadChargeMaterial::ThermicReactionType getThermicReactionType() const {
        return thermicReactionType;
    }

    /**
     * Sets the thermic reaction type
     * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
     */
    void setThermicReactionType(LoadChargeMaterial::ThermicReactionType thermicReactionType) {
        this->thermicReactionType = thermicReactionType;
    }

    /**
     * Gets the average specific heat of the solid material(dry)
     * @return double, average specific heat of solid material (dry) in btu/(lb*°F)
     */
    double getSpecificHeatSolid() const {
        return specificHeatSolid;
    }

    /**
     * Sets the average specific heat of the solid material (dry)
     * @param specificHeatSolid double, average specific heat of the solid material (dry) in btu/(lb*°F)
     */
    void setSpecificHeatSolid(const double specificHeatSolid) {
        this->specificHeatSolid = specificHeatSolid;
    }

    /**
     * Gets the latent heat of fusion
     * @return double, latent heat of fusion in btu/lb
     */
    double getLatentHeat() const {
        return latentHeat;
    }

    /**
     * Sets the latent heat of fusion
     * @param latentHeat double, latent heat of fusion in btu/lb
     */
    void setLatentHeat(const double latentHeat) {
        this->latentHeat = latentHeat;
    }

    /**
     * Gets the specific heat of liquid from molten material
     * @return double, specific heat of liquid from molten material in btu/(lb*°F)
     */
    double getSpecificHeatLiquid() const {
        return specificHeatLiquid;
    }

    /**
     * Sets the specific heat of liquid from molten material
     * @param specificHeatLiquid double, specific heat of liquid from molten material in btu/(lb*°F)
     */
    void setSpecificHeatLiquid(const double specificHeatLiquid) {
        this->specificHeatLiquid = specificHeatLiquid;
    }

    /**
     * Gets the melthing point of the material
     * @return double, melting point of material in °F
     */
    double getMeltingPoint() const {
        return meltingPoint;
    }

    /**
     * Gets the ID of material
     * @return int, ID number of material
     */
    int getID() const {
        return this->id;
    }

    /**
     * Sets the ID of a material
     * @param id int, ID of the material
     */
    void setID(const int id) {
        this->id = id;
    }

    /**
     * Sets the melting point of the material
     * @param meltingPoint double, melthing point of material in °F
     */
    void setMeltingPoint(const double meltingPoint) {
        this->meltingPoint = meltingPoint;
    }

    /**
     * Gets the charge (wet)-feed rate
     * @return double, charge (wet)-feed rate in lb/hr
     */
    double getChargeFeedRate() const {
        return chargeFeedRate;
    }

    /**
     * Sets the charge (wet)-feed rate
     * @param chargeFeedRate double, charge (wet)-feed rate in lb/hr
     */
    void setChargeFeedRate(const double chargeFeedRate) {
        this->chargeFeedRate = chargeFeedRate;
    }

    /**
     * Gets the water content as charged (%)
     * @return double, % of water content charged
     */
    double getWaterContentCharged() const {
        return waterContentCharged * 100.0;
    }

    /**
     * Sets the water content as charged (%)
     * @param waterContentCharged double, % of water content charged
     */
    void setWaterContentCharged(const double waterContentCharged) {
        this->waterContentCharged = waterContentCharged / 100.0;
    }

    /**
     * Gets the water content as discharged (%)
     * @return double, % of water content discharged
     */
    double getWaterContentDischarged() const {
        return waterContentDischarged * 100.0;
    }

    /**
     * Sets the water content as discharged (%)
     * @param waterContentDischarged double, % of water content discharged
     */
    void setWaterContentDischarged(const double waterContentDischarged) {
        this->waterContentDischarged = waterContentDischarged / 100.0;
    }

    /**
     * Gets the initial temperature
     * @return double, initial temperature in °F
     */
    double getInitialTemperature() const {
        return initialTemperature;
    }

    /**
     * Sets the initial temperature
     * @param initialTemperature double, initial temperature in °F
     */
    void setInitialTemperature(const double initialTemperature) {
        this->initialTemperature = initialTemperature;
    }

    /**
     * Gets the charge material discharge temperature
     * @return double, charge material discharge temperature in °F
     */
    double getDischargeTemperature() const {
        return dischargeTemperature;
    }

    /**
     * Sets the charge material discharge temperature
     * @param dischargeTemperature double, charge material discharge temperature in °F
     */
    void setDischargeTemperature(const double dischargeTemperature) {
        	this->dischargeTemperature = dischargeTemperature;
    }

    /**
     * Gets the water vapor discharge temperature
     * @return double, water vapor discharge temperature in °F
     */
    double getWaterVaporDischargeTemperature() const {
        return waterVaporDischargeTemperature;
    }

    /**
     * Sets the water vapor discharge temperature
     * @param waterVaporDischargeTemperature double, water vapor discharge temperature in °F
     */
    void setWaterVaporDischargeTemperature(const double waterVaporDischargeTemperature) {
        this->waterVaporDischargeTemperature = waterVaporDischargeTemperature;
    }

    /**
     * Gets the charge melted (% of dry charge)
     * @return double, charge melted (% of dry charge)
     */
    double getChargeMelted() const {
        return chargeMelted * 100.0;
    }

    /**
     * Sets the charge melted (% of dry charge)
     * @param chargeMelted double, charge melted (% of dry charge)
     */
    void setChargeMelted(const double chargeMelted) {
        this->chargeMelted = chargeMelted / 100.0;
    }

    /**
     * Gets the charge reacted
     * @return double, charge reacted (% of dry charge)
     */
    double getChargedReacted() const {
        return chargeReacted * 100.0;
    }

    /**
     * Sets the charged reacted
     * @param chargedReacted double, charge reacted (% of dry charge)
     */
    void setChargedReacted(const double chargedReacted) {
        this->chargeReacted = chargedReacted / 100.0;
    }

    /**
     * Gets the reaction heat
     * @return double, reaction heat in btu/lb
     */
    double getReactionHeat() const {
        return reactionHeat;
    }

    /**
     * Sets the reaction heat
     * @param reactionHeat double, reaction heat in btu/lb
     */
    void setReactionHeat(const double reactionHeat) {
        this->reactionHeat = reactionHeat;
    }

    /**
     * Gets the additional heat required
     * @return double, additional heat required in btu/hr
     */
    double getAdditionalHeat() const {
        return additionalHeat;
    }

    /**
     * Sets the additional heat required
     * @param additionalHeat double, additional heat required in btu/hr
     */
    void setAdditionalHeat(const double additionalHeat) {
        this->additionalHeat = additionalHeat;
    }

    /**
     * Gets the substance
     * @return string, name of substance
     */
    std::string getSubstance() const {
        return substance;
    }

    /**
     * Sets the substance
     * @param substance string, name of substance
     */
    void setSubstance(std::string const & substance) {
        this->substance = substance;
    }

    /**
     * bool == operator used to compare values in unit testing
     */
    bool operator == (const SolidLoadChargeMaterial& rhs) const
    {
        return specificHeatSolid == rhs.specificHeatSolid &&
                latentHeat == rhs.latentHeat &&
                specificHeatLiquid == rhs.specificHeatLiquid &&
                meltingPoint == rhs.meltingPoint &&
                substance == rhs.substance && id == rhs.id;
    }

    /**
     * Obtain the total heat for the solid charge material in Btu/hr
     * */
	double getTotalHeat() {
		double const waterBoilTemp = 212.0; // Heat required temperature is 212.0°F

		// Heat required for removal of moisture
		double hmv;
		if (waterVaporDischargeTemperature < waterBoilTemp) {
			//   (H_mv )=m_st×(%w_i )×〖(t〗_wo-t_si)
			hmv = chargeFeedRate * waterContentCharged * (waterVaporDischargeTemperature - initialTemperature);
		} else {
			double const specificHeatWaterVapor = 0.481;
			double const waterEvaporation = 970.0; // Latent heat of evaporation for water is 970 Btu/lb
			// (H_mv )=m_st×(%w_i )×(212-t_si )+m_st×(%w_i-%w_o )  ×[970+0.481×〖(t〗_wo-212)]
			hmv = (chargeFeedRate * waterContentCharged * (waterBoilTemp - initialTemperature))
				  + chargeFeedRate * (waterContentCharged - waterContentDischarged)
					* (waterEvaporation + specificHeatWaterVapor * (waterVaporDischargeTemperature - waterBoilTemp));
		}
		// (H_mr )=m_st×(%w_0 )×〖(t〗_wo-t_si)
		double hmr = chargeFeedRate * waterContentDischarged * (waterVaporDischargeTemperature - waterBoilTemp);

		// Heat required for solid
		double hs;
		if (dischargeTemperature < meltingPoint) {
			// (H_s)=m_st×(1-%w_i )×C_ps×(t_so-t_si)
			hs = chargeFeedRate * (1.0 - waterContentCharged) * specificHeatSolid * (dischargeTemperature - initialTemperature);
		} else {
			// (H_s )=m_st×(1-%w_i )×C_ps×(T_sm-t_si )+h_m+C_(pl ×) (t_so-T_sm)
			hs = chargeFeedRate * (1.0 - waterContentCharged)
				 * (specificHeatSolid * (meltingPoint - initialTemperature)
					+ (latentHeat * chargeMelted) + specificHeatLiquid * (dischargeTemperature - meltingPoint) * (chargeMelted)
					+ (specificHeatSolid * (1 - chargeMelted) * (dischargeTemperature - meltingPoint)));
		}

		double heatReaction = 0.0;
		if (thermicReactionType == LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC) {
			heatReaction = chargeFeedRate * (1.0 - waterContentCharged) * chargeReacted * reactionHeat;
		}

		// H_t=H_mv+H_mr+H_s±H_r
		totalHeat = hmv + hmr + hs + heatReaction + additionalHeat;
		return totalHeat;
	}

private:

    // In/Out values
    std::string substance = "Unknown";
    // In values
    LoadChargeMaterial::ThermicReactionType thermicReactionType = LoadChargeMaterial::ThermicReactionType::NONE;
    double specificHeatSolid = 0.0;
    double latentHeat = 0.0;
    double specificHeatLiquid = 0.0;
    double meltingPoint = 0.0;
    double chargeFeedRate = 0.0;
    double waterContentCharged = 0.0;
    double waterContentDischarged = 0.0;
    double initialTemperature = 0.0;
    double dischargeTemperature = 0.0;
    double waterVaporDischargeTemperature = 0.0;
    double chargeMelted = 0.0;
    double chargeReacted = 0.0;
    double reactionHeat = 0.0;
    double additionalHeat = 0.0;
    int id = 0;
    // Out values
    double totalHeat = 0.0;

    friend class SQLite;

    /**
    * Constructor for the solid load/charge material with subset of inputs specified.
    * @param substance string, Name of substance
    * @param specificHeatSolid double, Average specific heat of the solid material (dry) in Btu/(lb*°F)
    * @param latentHeat double, Latent heat of fusion in Btu/(lb)
    * @param specificHeatLiquid double, Specific heat of liquid from molten material in Btu/(lb*°F)
    * @param meltingPoint double, The melting point of the material in °F
    * */
    SolidLoadChargeMaterial(
            std::string substance,
            double specificHeatSolid,
            double latentHeat,
            double specificHeatLiquid,
            double meltingPoint
    ) : substance(std::move(substance)),
        specificHeatSolid(specificHeatSolid),
        latentHeat(latentHeat),
        specificHeatLiquid(specificHeatLiquid),
        meltingPoint(meltingPoint)
    {}

};

#endif //AMO_SUITE_SOLIDLOADCHARGEMATERIAL_H
