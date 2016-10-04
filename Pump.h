//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_PUMP_H
#define AMO_LIBRARY_PUMP_H


#include <cmath>

class Pump {
public:
    enum class Style {
        END_SUCTION_SLURRY,
        END_SUCTION_SEWAGE,
        END_SUCTION_STOCK,
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

    Pump(Style style, double rpm, Drive drive, double kviscosity, double sg, int stageCount, bool fixedSpeed) :
            style_(style), rpm_(rpm), drive_(drive), kviscosity_(kviscosity), sg_(sg), stageCount_(stageCount),
            fixedSpeed_(fixedSpeed) {};

    Pump() = default;

    Style getStyle() {
        return style_;
    }

    void setStyle(Style style) {
        style_ = style;
    }

    int getRpm() {
        return std::round(rpm_);
    }

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

    int getFixedSpeed() {
        return fixedSpeed_;
    }

    void setFixedSpeed_(bool fixedSpeed) {
        fixedSpeed_ = fixedSpeed;
    };

private:
// Input values
    Pump::Style style_;
    double rpm_;
    Pump::Drive drive_;
    double kviscosity_;
    double sg_;
    int stageCount_;
    bool fixedSpeed_;
};


#endif //AMO_LIBRARY_PUMP_H
