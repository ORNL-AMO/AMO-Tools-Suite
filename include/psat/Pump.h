/**
 * @file
 * @brief Function prototypes for the Pump fields
 *
 * This contains the prototypes for the Pump structure
 * including getters and setters for the important fields. Primary
 * importance are methods for setting and getting data dealing with
 * pump information.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_PUMP_H
#define AMO_LIBRARY_PUMP_H

#include <cmath>

/**
 * Pump class
 * Contains all of the properties of a pump.
 */
class Pump {
public:

    ///enum class for pump styles
    enum class Style {
        END_SUCTION_SLURRY,
        END_SUCTION_SEWAGE,
        END_SUCTION_STOCK,
        END_SUCTION_SUBMERSIBLE_SEWAGE,
        API_DOUBLE_SUCTION,
        MULTISTAGE_BOILER_FEED,
        END_SUCTION_ANSI_API,
        AXIAL_FLOW,
        DOUBLE_SUCTION,
        VERTICAL_TURBINE,
        LARGE_END_SUCTION,
        SPECIFIED_OPTIMAL_EFFICIENCY
    };

    ///enum class for drive types
    enum class Drive {
        DIRECT_DRIVE,
        V_BELT_DRIVE,
        N_V_BELT_DRIVE,
        S_BELT_DRIVE
    };

    ///enum class for speed types
    enum class Speed {
        FIXED_SPEED,
        NOT_FIXED_SPEED
    };

    /**
     * Constructor
     * @param style Style, classification of style of pump being used.
     * @param achievableEfficiency double, pump % efficiency at the specified operating conditions
     * @param rpm double, pump RPM to define its operating speed
     * @param drive Drive, type of drive the pump uses from either direct or belt drive.
     * @param kviscosity double, kinematic viscosity of the fluid being pumped in centistokes.
     * @param sg double, specific gravity- unitless
     * @param stageCount int, the number of pump stages
     * @param speed Speed, type of pump speed from either fixed or not fixed.
     */
    Pump(
        Style style,
        double achievableEfficiency,
        double rpm,
        Drive drive,
        double kviscosity,
        double sg,
        int stageCount,
        Speed speed
    ) :
        style(style),
        achievableEfficiency(achievableEfficiency),
        rpm(rpm),
        drive(drive),
        kviscosity(kviscosity),
        specificGravity(sg),
        stageCount(stageCount),
        speed(speed)
    {};

//    Pump() = default;

    /**
     * Get the style of the pump being used
     * @return Style, classification of style of pump
     */
    Style getStyle() {
        return style;
    }

    /**
     * Set the style of pump being used
     * @param style Style, classification of style of pump
     */
    void setStyle(Style style) {
        this->style = style;
    }

    /**
     * Get the achievable efficiency of the pump at specified operating conditions
     * @return double, achievable efficiency as %
     */
    double getAchievableEfficiency(){
        return achievableEfficiency;
    }

    /**
     * Set the achievable efficiency of the pump at specified operating conditions
     * @param achievableEfficiency double, achievable efficiency as %
     */
    void setAchievableEfficiency(double achievableEfficiency){
        this->achievableEfficiency = achievableEfficiency;
    }

    /**
     * Get RPM of pump to define operation speed
     * @return int, motor RPM
     */
    int getRpm() {
	    return static_cast<int>(std::round(rpm));
    };

    /**
     * Set the RPM of pump to define operation speed
     * @param rpm double, motor RPM
     */
    void setRpm(double rpm) {
        this->rpm = rpm;
    }

    /**
     * Get the type of drive the pump uses from either direct or belt drive
     * @return Drive, classification of drive type
     */
    Drive getDrive() {
        return drive;
    }

    /**
     * Set the type of drive the pump uses from either direct or belt drive
     * @param drive Drive, classification of drive type
     */
    void setDrive(Drive drive) {
        this->drive = drive;
    }

    /**
     * Get the kinematic viscosity of the fluid being pumped
     * @return double, kinematic viscosity in centistokes
     */
    double getKviscosity() {
        return kviscosity;
    }

    /**
     * Set the kinematic viscosity of the fluid being pumped
     * @param kviscosity double, kinematic viscosity in centistokes
     */
    void setKviscosity_(double kviscosity) {
        this->kviscosity = kviscosity;
    }

    /**
     * Get the specific gravity
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() {
        return specificGravity;
    }

    /**
     * Set the specific gravity
     * @param sg double, specific gravity - unitless
     */
    void setSpecificGravity(double sg) {
        this->specificGravity = sg;
    }

    /**
     * Get number of pump stages
     * @return int, number of pump stages
     */
    int getStageCount() {
        return stageCount;
    }

    /**
     * Set number of pump stages
     * @param stageCount int, number of pump stages
     */
    void setStageCount(int stageCount) {
        this->stageCount = stageCount;
    }

    /**
     * Get the type of pump speed from either fixed or not fixed
     * @return Speed, classification of pump speed type
     */
    Speed getFixedSpeed(){
        return speed;
    }

    /**
     * Set the type of pump speed from either fixed or not fixed
     * @param speed Speed, classification of pump speed type
     */
    void setFixedSpeed_(Speed speed){
        this->speed = speed;
    };

private:
// Input values
    Pump::Style style;
    double achievableEfficiency;
    double rpm;
    Pump::Drive drive;
    double kviscosity;
    double specificGravity;
    int stageCount;
    Speed speed;
};


#endif //AMO_LIBRARY_PUMP_H
