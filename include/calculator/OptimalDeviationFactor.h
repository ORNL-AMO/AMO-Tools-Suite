/**
 * @brief Header file for OptimalDeviationFactor class
 *
 * This contains the prototypes of OptimalDeviationFactor calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Mishra, Subhankar on 10/24/16.
//

#ifndef AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
#define AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H

class OptimalDeviationFactor {
public:
    OptimalDeviationFactor(
        double flowRate
    ) :
        flowRate_(flowRate)
    {}

    double calculate();

private:
    double flowRate_;
};


#endif //AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
