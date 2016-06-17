//
// Created by Accawi, Gina K. on 6/15/16.
//

#include "Pump.h"

Pump::Pump() {
    // Will make a few assumptions/defaults
    setStyle(Style::END_SUCTION_ANSI_API);
    setDrive(Drive::DIRECT_DRIVE);
    setSpeed(Speed::FIXED_SPECIFIC_SPEED);
    setAchievableEfficiency(0.0);
    setRpm(0.0);
    setStageCount(0);
}

Pump::Pump(Style style, Drive drive, Speed speed, double achievableEfficiency, double rpm, int stageCount) {
    setStyle(style);
    setDrive(drive);
    setSpeed(speed);
    setAchievableEfficiency(achievableEfficiency);
    setRpm(rpm);
    setStageCount(stageCount);
}

Pump::Style Pump::getStyle() {
    return style_;
}

void Pump::setStyle(Pump::Style style) {
    this->style_ = style;
}

Pump::Drive Pump::getDrive() {
    return drive_;
}

void Pump::setDrive(Pump::Drive drive) {
    this->drive_ = drive;
}

Pump::Speed Pump::getSpeed() {
    return speed_;
}

void Pump::setSpeed(Pump::Speed speed) {
    this->speed_ = speed;
}

double Pump::getAchievableEfficiency() {
    return achievableEfficiency_;
}

void Pump::setAchievableEfficiency(double achievableEfficiency) {
    this->achievableEfficiency_ = achievableEfficiency;
}

double Pump::getRpm() {
    return rpm_;
}

void Pump::setRpm(double rpm) {
    this->rpm_ = rpm;
}

int Pump::getStageCount() {
    return stageCount_;
}

void Pump::setStageCount(int stageCount) {
    this->stageCount_ = stageCount;
}

FieldData Pump::getFieldData() {
    return fieldData_;
}

void Pump::setFieldData(FieldData fieldData) {
    this->fieldData_ = fieldData;
}

Motor Pump::getMotor() {
    return motor_;
}

void Pump::setMotor(Motor motor) {
    this->motor_ = motor;
}

Financial Pump::getFinancial() {
    return financial_;
}

void Pump::setFinancial(Financial financial) {
    this->financial_ = financial;
}

PSATResult Pump::calculate() {

}