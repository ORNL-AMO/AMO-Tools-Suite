//
// Created by Accawi, Gina K. on 6/15/16.
//

#include "FieldData.h"

FieldData::FieldData() {
    this->loadEstimationMethod_ = LoadEstimationMethod::POWER;
    this->flowRate_ = 0.0;
    this->head_ = 0.0;
    this->motorPower_ = 0.0;
    this->motorAmps_ = 0.0;
    this->voltage_ = 0.0;
}

FieldData::FieldData(LoadEstimationMethod loadEstimationMethod, double flowRate, double head, double motorPower,
                     double motorAmps, double voltage) {
    this->loadEstimationMethod_ = loadEstimationMethod;
    this->flowRate_ = flowRate;
    this->head_ = head;
    this->motorPower_ = motorPower;
    this->motorAmps_ = motorAmps;
    this->voltage_ = voltage;
}

FieldData::LoadEstimationMethod FieldData::getLoadEstimationMethod() {
    return loadEstimationMethod_;
}

void FieldData::setLoadEstimationMethod(FieldData::LoadEstimationMethod loadEstimationMethod)  {
    this->loadEstimationMethod_ = loadEstimationMethod;
}

double FieldData::getFlowRate()  {
    return flowRate_;
}

void FieldData::setFlowRate(double flowRate) {
    this->flowRate_ = flowRate;
}

double FieldData::getHead()  {
    return head_;
}

void FieldData::setHead(double head) {
    this->head_ = head;
}

double FieldData::getMotorPower()  {
    return motorPower_;
}

void FieldData::setMotorPower(double motorPower) {
    this->motorPower_ = motorPower;
}

double FieldData::getMotorAmps()  {
    return motorAmps_;
}

void FieldData::setMotorAmps(double motorAmps) {
    this->motorAmps_ = motorAmps;
}

double FieldData::getVoltage()  {
    return voltage_;
}

void FieldData::setVoltage(double voltage) {
    this->voltage_ = voltage;
}