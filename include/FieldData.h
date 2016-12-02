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

    FieldData(
        double flowRate,
        double head,
        LoadEstimationMethod loadEstimationMethod,
        double motorPower,
        double motorAmps,
        double voltage
    ) :
        loadEstimationMethod_(loadEstimationMethod),
        flowRate_(flowRate),
        head_(head),
        motorPower_(motorPower),
        motorAmps_(motorAmps),
        voltage_(voltage)
    {}

    FieldData() = default;

    LoadEstimationMethod getLoadEstimationMethod() const {
        return loadEstimationMethod_;
    }

    void setLoadEstimationMethod(LoadEstimationMethod loadEstimationMethod) {
        loadEstimationMethod_ = loadEstimationMethod;
    }

    double getFlowRate() const {
        return flowRate_;
    }

    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    double getHead() const {
        return head_;
    }

    void setHead(double head) {
        head_ = head;
    }

    double getMotorPower() const {
        return motorPower_;
    }

    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

    double getMotorAmps() const {
        return motorAmps_;
    }

    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    double getVoltage() const {
        return voltage_;
    }

    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

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
