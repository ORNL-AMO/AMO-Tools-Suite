//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_PUMPEFFICIENCY_H
#define AMO_LIBRARY_PUMPEFFICIENCY_H


class PumpEfficiency {

public:
    PumpEfficiency(double specificGravity, double flowRate, double head, double pumpShaftPower) : specificGravity_(
            specificGravity), flowRate_(flowRate), head_(head), pumpShaftPower_(pumpShaftPower) { }

    double calculate();
public:
    double getSpecificGravity() const {
        return specificGravity_;
    }

    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
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

    double getPumpShaftPower() const {
        return pumpShaftPower_;
    }

    void setPumpShaftPower(double pumpShaftPower) {
        pumpShaftPower_ = pumpShaftPower;
    }

private:
    double specificGravity_;
    double flowRate_;
    double head_;
    double pumpShaftPower_;

};


#endif //AMO_LIBRARY_PUMPEFFICIENCY_H
