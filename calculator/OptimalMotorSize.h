//
// Created by Mishra, Subhankar on 10/14/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORSIZE_H
#define AMO_LIBRARY_OPTIMALMOTORSIZE_H


class OptimalMotorSize {
public:
    OptimalMotorSize(double optimalMotorShaftPower, double sizeMargin):
            optimalMotorShaftPower_(optimalMotorShaftPower), sizeMargin_(sizeMargin){};
    double calculate();
private:
    double optimalMotorShaftPower_;
    double sizeMargin_;
    double optimalMotorRatedPower_;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSIZE_H
