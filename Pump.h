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

    Pump();


    Pump(Style style, Drive drive, Speed speed, double achievableEfficiency, double rpm, int stageCount);

// Setters
    void setStyle(Pump::Style style);
    void setDrive(Pump::Drive drive);
    void setSpeed(Pump::Speed speed);
    void setAchievableEfficiency(double achievableEfficiency);
    void setRpm(double rpm);
    void setStageCount(int stageCount);
    void setFieldData(FieldData fieldData);
    void setMotor(Motor motor);
    void setFinancial(Financial financial);
// Getters
    Pump::Style getStyle(void);
    Pump::Speed getSpeed(void);
    Pump::Drive getDrive(void);
    double getAchievableEfficiency(void);
    double getRpm(void);
    int getStageCount(void);
    FieldData getFieldData(void);
    Motor getMotor(void);
    Financial getFinancial(void);
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
};


#endif //AMO_LIBRARY_PUMP_H
