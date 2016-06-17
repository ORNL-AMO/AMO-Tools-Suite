//
// Created by Accawi, Gina K. on 6/17/16.
//

#ifndef AMO_LIBRARY_MOTORRATEDPOWER_H
#define AMO_LIBRARY_MOTORRATEDPOWER_H


class MotorRatedPower {


public:
    MotorRatedPower(double horsepower) : horsepower_(horsepower) { }
    double calculate();
    double getHorsepower() const {
        return horsepower_;
    }

    void setHorsepower(double horsepower) {
        horsepower_ = horsepower;
    }

private:
    double horsepower_;
};


#endif //AMO_LIBRARY_MOTORRATEDPOWER_H
