//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_PUMP_H
#define AMO_LIBRARY_PUMP_H

#include "FieldData.h"
#include "Motor.h"
#include "Financial.h"
#include "PSATResult.h"

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
    // Speed should be boolean or NO?
    enum class Speed {
        FIXED_SPECIFIC_SPEED,
        NO_FIXED_SPECIFIC_SPEED
    };

    Pump() = default;

    Pump(Style style, Drive drive, Speed speed, double achievableEfficiency, double rpm, int stageCount,
         const FieldData &fieldData, const Motor &motor, const Financial &financial) : style_(style), drive_(drive),
                                                                                       speed_(speed),
                                                                                       achievableEfficiency_(
                                                                                               achievableEfficiency),
                                                                                       rpm_(rpm),
                                                                                       stageCount_(stageCount),
                                                                                       fieldData_(fieldData),
                                                                                       motor_(motor),
                                                                                       financial_(financial) {}

    Pump(Drive drive, Speed speed, double achievableEfficiency, double rpm, int stageCount, const FieldData &fieldData,
         const Motor &motor, const Financial &financial, const PSATResult &psatResult, double actualEfficiency)
            : drive_(drive), speed_(speed), achievableEfficiency_(achievableEfficiency), rpm_(rpm),
              stageCount_(stageCount), fieldData_(fieldData), motor_(motor), financial_(financial),
              psatResult_(psatResult), actualEfficiency_(actualEfficiency) {}

    Style getStyle() const {
        return style_;
    }

    void setStyle(Style style) {
        style_ = style;
    }

    Drive getDrive() const {
        return drive_;
    }

    void setDrive(Drive drive) {
        drive_ = drive;
    }

    Speed getSpeed() const {
        return speed_;
    }

    void setSpeed(Speed speed) {
        speed_ = speed;
    }

    double getAchievableEfficiency() const {
        return achievableEfficiency_;
    }

    void setAchievableEfficiency(double achievableEfficiency) {
        achievableEfficiency_ = achievableEfficiency;
    }

    double getRpm() const {
        return rpm_;
    }

    void setRpm(double rpm) {
        rpm_ = rpm;
    }

    int getStageCount() const {
        return stageCount_;
    }

    void setStageCount(int stageCount) {
        stageCount_ = stageCount;
    }

    const FieldData &getFieldData() const {
        return fieldData_;
    }

    void setFieldData(const FieldData &fieldData) {
        fieldData_ = fieldData;
    }

    const Motor &getMotor() const {
        return motor_;
    }

    void setMotor(const Motor &motor) {
        motor_ = motor;
    }

    const Financial &getFinancial() const {
        return financial_;
    }

    void setFinancial(const Financial &financial) {
        financial_ = financial;
    }

    const PSATResult &getPsatResult() const {
        return psatResult_;
    }

    void setPsatResult(const PSATResult &psatResult) {
        psatResult_ = psatResult;
    }

    double getActualEfficiency() const {
        return actualEfficiency_;
    }

    void setActualEfficiency(double actualEfficiency) {
        actualEfficiency_ = actualEfficiency;
    }

// Calculate all results
    PSATResult calculate();
private:
// Input values
    Pump::Style style_;
    Pump::Drive drive_;
    Pump::Speed speed_;
    double achievableEfficiency_;
    double rpm_;
    int stageCount_;
    FieldData fieldData_;
    Motor motor_;
    Financial financial_;
    PSATResult psatResult_;
    double actualEfficiency_;
};


#endif //AMO_LIBRARY_PUMP_H
