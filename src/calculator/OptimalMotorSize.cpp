/**
 * @brief Contains the definition of functions of OptimalMotorSize class.
 *      calculate(): Calculates the Optimal Motor Size
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Mishra, Subhankar on 10/14/16.
//

#include <vector>
#include "calculator/OptimalMotorSize.h"

double OptimalMotorSize::calculate() {
    // Motor Size collection in hp
    std::vector<double> motorSize(62);
    motorSize[0] = 0;
    motorSize[1] = 5;
    motorSize[2] = 7.5;
    motorSize[3] = 10;
    motorSize[4] = 15;
    motorSize[5] = 20;
    motorSize[6] = 25;
    motorSize[7] = 30;
    motorSize[8] = 40;
    motorSize[9] = 50;
    motorSize[10] = 60;
    motorSize[11] = 75;
    motorSize[12] = 100;
    motorSize[13] = 125;
    motorSize[14] = 150;
    motorSize[15] = 200;
    motorSize[16] = 250;
    motorSize[17] = 300;
    motorSize[18] = 350;
    motorSize[19] = 400;
    motorSize[20] = 450;
    motorSize[21] = 500;
    motorSize[22] = 600;
    motorSize[23] = 700;
    motorSize[24] = 800;
    motorSize[25] = 900;
    motorSize[26] = 1000;
    motorSize[27] = 1250;
    motorSize[28] = 1500;
    motorSize[29] = 1750;
    motorSize[30] = 2000;
    motorSize[31] = 2250;
    motorSize[32] = 2500;
    motorSize[33] = 3000;
    motorSize[34] = 3500;
    motorSize[35] = 4000;
    motorSize[36] = 4500;
    motorSize[37] = 5000;
    motorSize[38] = 5500;
    motorSize[39] = 6000;
    motorSize[40] = 7000;
    motorSize[41] = 8000;
    motorSize[42] = 9000;
    motorSize[43] = 10000;
    motorSize[44] = 11000;
    motorSize[45] = 12000;
    motorSize[46] = 13000;
    motorSize[47] = 14000;
    motorSize[48] = 15000;
    motorSize[49] = 16000;
    motorSize[50] = 17000;
    motorSize[51] = 18000;
    motorSize[52] = 19000;
    motorSize[53] = 20000;
    motorSize[54] = 22500;
    motorSize[55] = 25000;
    motorSize[56] = 27500;
    motorSize[57] = 30000;
    motorSize[58] = 35000;
    motorSize[59] = 40000;
    motorSize[60] = 45000;
    motorSize[61] = 50000;

    double requiredShaftPower = optimalMotorShaftPower_ * (1 + sizeMargin_);
//    double previous = motorSize[0];
    for (int i = 1; i < 62; ++i) {
        if (requiredShaftPower < motorSize[i]){
            optimalMotorRatedPower_ = motorSize[i];
            break;
        }
    }
    return optimalMotorRatedPower_;
}
