//
// Created by Accawi, Gina K. on 6/15/16.
//

#include "Motor.h"

Motor::Motor() {
    // Will make a few assumptions defaults
    this->efficiencyClass_ = EfficiencyClass::STANDARD;
    this->lineFrequency_ = 0.0;
    this->motorRatedPower_ = 0.0;
    this->fullLoadEfficiency_ = 0.0;
    this->motorRatedVoltage_ = 0.0;
    this->sizeMargin_ = 0.0;
}

Motor::Motor(EfficiencyClass efficiencyClass, double lineFrequency, double motorRatedPower, double fullLoadEfficiency,
             double motor_rated_voltage, double sizeMargin) {
    this->efficiencyClass_ = efficiencyClass;
    this->lineFrequency_ = lineFrequency;
    this->motorRatedPower_ = motorRatedPower;
    this->fullLoadEfficiency_ = fullLoadEfficiency;
    this->motorRatedVoltage_ = motor_rated_voltage;
    this->sizeMargin_ = sizeMargin;
}

Motor::EfficiencyClass Motor::getEfficiencyClass()  {
    return efficiencyClass_;
}

void Motor::setEfficiencyClass(Motor::EfficiencyClass efficiencyClass) {
    this->efficiencyClass_ = efficiencyClass;
}

double Motor::getLineFrequency()  {
    return lineFrequency_;
}

void Motor::setLineFrequency(double lineFrequency) {
    this->lineFrequency_ = lineFrequency;
}

double Motor::getMotorRatedPower()  {
    return motorRatedPower_;
}

void Motor::setMotorRatedPower(double motorRatedPower) {
    this->motorRatedPower_ = motorRatedPower;
}

double Motor::getFullLoadEfficiency()  {
    return fullLoadEfficiency_;
}

void Motor::setFullLoadEfficiency(double fullLoadEfficiency) {
    this->fullLoadEfficiency_ = fullLoadEfficiency;
}

double Motor::getMotorRatedVoltage()  {
    return motorRatedVoltage_;
}

void Motor::setMotorRatedVoltage(double motorRatedVoltage) {
    this->motorRatedVoltage_ = motorRatedVoltage;
}

double Motor::getSizeMargin() {
    return sizeMargin_;
}

void Motor::setSizeMargin(double sizeMargin) {
    this->sizeMargin_ = sizeMargin;
}