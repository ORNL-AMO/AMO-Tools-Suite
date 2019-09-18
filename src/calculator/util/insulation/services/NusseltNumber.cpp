#include "calculator/util/insulation/services/NusseltNumber.h"
#include <cmath>

double NusseltNumber::calculate()
{
    return std::pow(std::pow(this->_a, 4) + std::pow(this->_b, 4), 1 / 4);
}

double NusseltNumber::calculatedForcedConvection()
{
    double step1 = std::pow(this->_a, 1.0 / 2.0);
    double step2 = step1 * 0.62;
    double step3 = step2 * std::pow(this->_b, 1.0 / 3.0);

    double step4 = std::pow(this->_a / 282000.0, 5.0 / 8.0);
    double step5 = step4 + 1.0;
    double step6 = std::pow(step5, 4.0 / 5.0);

    double step7 = std::pow(0.4 / this->_b, 2.0 / 3.0);
    double step8 = step7 + 1.0;
    double step9 = std::pow(step8, 1.0 / 4.0);

    double step10 = step3 * step6 / step9;
    double step11 = step10 + 0.3;

    return step11;
}

double NusseltNumber::calculateFreeConvection()
{
    double step1 = std::pow(this->_a, 1.0 / 6.0);
    double step2 = step1 * 0.387;
    
    double step3 = std::pow(0.559 / this->_b, 9.0 / 16.0);
    double step4 = step3 + 1.0;
    double step5 = std::pow(step4, 8.0 / 27.0);

    double step6 = step2 / step5;
    double step7 = step6 + 0.6;
    double step8 = std::pow(step7, 2);
    return step8;
}
