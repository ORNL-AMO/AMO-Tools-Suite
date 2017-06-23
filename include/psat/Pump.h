/**
 * @file
 * @brief Function prototypes for the Financial fields
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

    ///emun class for drive types
    enum class Drive {
        DIRECT_DRIVE,
        BELT_DRIVE
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
     * @return nothing
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
        style_(style),
        achievableEfficiency_(achievableEfficiency),
        rpm_(rpm),
        drive_(drive),
        kviscosity_(kviscosity),
        sg_(sg),
        stageCount_(stageCount),
        speed_(speed)
    {};

    Pump() = default;

    /**
     * Get the style of the pump being used
     *
     * @return Style, classificiation of style of pump
     */
    Style getStyle() {
        return style_;
    }

    /**
     * Set the style of pump being used
     *
     * @param style Style, classification of style of pump
     *
     * @return nothing
     */
    void setStyle(Style style) {
        style_ = style;
    }

    /**
     * Get the achievable efficiency of the pump at specified operating conditions
     *
     * @return double, achievable efficiency as %
     */
    double getAchievableEfficiency(){
        return achievableEfficiency_;
    }

    /**
     * Set the achievable efficiency of the pump at specified operating conditons
     *
     * @param achievableEfficiency double, achievable efficiency as %
     *
     * @return nothing
     */
    void setAchievableEfficiency(double achievableEfficiency){
        achievableEfficiency_ = achievableEfficiency;
    }

    /**
     * Get RPM of pump to define operation speed
     *
     * @return int, motor RPM
     */
    int getRpm();

    /**
     * Set the RPM of pump to define operation speed
     *
     * @param rpm double, motor RPM
     *
     * @return nothing
     */
    void setRpm(double rpm) {
        rpm_ = rpm;
    }

    /**
     * Get the type of drive the pump uses from either direct or belt drive
     *
     * @return Drive, classification of drive type
     */
    Drive getDrive() {
        return drive_;
    }

    /**
     * Set the type of drive the pump uses from either direct or belt drive
     *
     * @param drive Drive, classification of drive type
     *
     * @return nothing
     */
    void setDrive(Drive drive) {
        drive_ = drive;
    }

    /**
     * Get the kinematic viscosity of the fluid being pumped
     *
     * @return double, kinematic viscosity in centistokes
     */
    double getKviscosity() {
        return kviscosity_;
    }

    /**
     * Set the kinematic viscosity of the fluid being pumped
     *
     * @param kviscosity double, kinematic viscosity in centistokes
     *
     * @return nothing
     */
    void setKviscosity_(double kviscosity) {
        kviscosity_ = kviscosity;
    }

    /**
     * Get the specific gravity
     *
     * @return double, specific gravity - unitless
     */
    double getSg() {
        return sg_;
    }

    /**
     * Set the specific gravity
     *
     * @param sg double, specific gravity - unitless
     *
     * @return nothing
     */
    void setSg(double sg) {
        sg_ = sg;
    }

    /**
     * Get number of pump stages
     *
     * @return int, number of pump stages
     */
    int getStageCount() {
        return stageCount_;
    }

    /**
     * Set number of pump stages
     *
     * @param stageCount int, number of pump stages
     *
     * @return nothing
     */
    void setStageCount(int stageCount) {
        stageCount_ = stageCount;
    }

    /**
     * Get the type of pump speed from either fixed or not fixed
     *
     * @return Speed, classification of pump speed type
     */
    Speed getFixedSpeed(){
        return speed_;
    }

    /**
     * Set the type of pump speed from either fixed or not fixed
     *
     * @param speed Speed, classification of pump speed type
     *
     * @return nothing
     */
    void setFixedSpeed_(Speed speed){
        speed_ = speed;
    };

private:
// Input values
    Pump::Style style_;
    double achievableEfficiency_;
    double rpm_;
    Pump::Drive drive_;
    double kviscosity_;
    double sg_;
    int stageCount_;
    Speed speed_;
};


#endif //AMO_LIBRARY_PUMP_H
