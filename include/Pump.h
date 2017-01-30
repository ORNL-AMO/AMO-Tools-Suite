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
    enum class Drive {
        DIRECT_DRIVE,
        BELT_DRIVE
    };
    enum class Speed {
        FIXED_SPEED,
        NOT_FIXED_SPEED
    };

    /**
     * Constructor
     * @param style Style of pump being used.
     * @param achievableEfficiency Pump % efficiency at the specified operating conditions.
     * @param rpm Pump RPM to define its operating speed.
     * @param drive Type of drive the pump uses from either direct or belt drive.
     * @param kviscosity Kinematic viscosity of the fluid being pumped, in centistokes.
     * @param sg Specific gravity.
     * @param stageCount The number of pump stages.
     * @param speed Type of pump speed from either fixed or not fixed.
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

    Style getStyle() {
        return style_;
    }

    void setStyle(Style style) {
        style_ = style;
    }
    double getAchievableEfficiency(){
        return achievableEfficiency_;
    }
    void setAchievableEfficiency(double achievableEfficiency){
        achievableEfficiency_ = achievableEfficiency;
    }

    int getRpm();

    void setRpm(double rpm) {
        rpm_ = rpm;
    }

    Drive getDrive() {
        return drive_;
    }

    void setDrive(Drive drive) {
        drive_ = drive;
    }

    double getKviscosity() {
        return kviscosity_;
    }

    void setKviscosity_(double kviscosity) {
        kviscosity_ = kviscosity;
    }

    double getSg() {
        return sg_;
    }

    void setSg(double sg) {
        sg_ = sg;
    }

    int getStageCount() {
        return stageCount_;
    }

    void setStageCount(int stageCount) {
        stageCount_ = stageCount;
    }

    Speed getFixedSpeed(){
        return speed_;
    }
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
