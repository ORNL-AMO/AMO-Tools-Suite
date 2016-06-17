//
// Created by Accawi, Gina K. on 6/15/16.
//

#ifndef AMO_LIBRARY_FIELDDATA_H
#define AMO_LIBRARY_FIELDDATA_H


class FieldData {
public:
    enum class LoadEstimationMethod {
        POWER,
        CURRENT
    };

    FieldData();

    FieldData(LoadEstimationMethod loadEstimationMethod, double flowRate, double head, double motorPower,
              double motorAmps, double voltage);

    FieldData::LoadEstimationMethod getLoadEstimationMethod(void);

    void setLoadEstimationMethod(FieldData::LoadEstimationMethod loadEstimationMethod);
    double getFlowRate(void);
    void setFlowRate(double flowRate);
    double getHead(void);
    void setHead(double head);
    double getMotorPower(void);
    void setMotorPower(double motorPower);
    double getMotorAmps(void);
    void setMotorAmps(double motorAmps);
    double getVoltage(void);
    void setVoltage(double voltage);

private:
// Input values
    FieldData::LoadEstimationMethod loadEstimationMethod_;
    double flowRate_;
    double head_;
    double motorPower_;
    double motorAmps_;
    double voltage_;
};


#endif //AMO_LIBRARY_FIELDDATA_H
