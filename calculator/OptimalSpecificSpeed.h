/**
 * @brief Header file for Optimal Specific Speed class
 *
 * This contains the prototypes of Optimal Specific Speed calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Mishra, Subhankar on 10/21/16.
//

#ifndef AMO_LIBRARY_OPTIMALSPECIFICSPEED_H
#define AMO_LIBRARY_OPTIMALSPECIFICSPEED_H

#include <cmath>

class OptimalSpecificSpeed {
public:
    OptimalSpecificSpeed(double rpm, double flowRate, double head, double stageCount): rpm_(rpm), flowRate_(flowRate), head_(head), stageCount_(stageCount){};
    double calculate();
private:
    double stageCount_;
    double flowRate_;
    double head_;
    double rpm_;
};


#endif //AMO_LIBRARY_OPTIMALSPECIFICSPEED_H
