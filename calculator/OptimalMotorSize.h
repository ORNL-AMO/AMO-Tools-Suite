/**
 * @brief Header file for OptimalMotorSize class
 *
 * This contains the prototypes of OptimalMotorSize calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

//
// Created by Mishra, Subhankar on 10/14/16.
//

#ifndef AMO_LIBRARY_OPTIMALMOTORSIZE_H
#define AMO_LIBRARY_OPTIMALMOTORSIZE_H

class OptimalMotorSize {
public:
    /**
     * Constructor
     * @param optimalMotorShaftPower
     * @param sizeMargin
     * @return nothing
     */
    OptimalMotorSize(
        double optimalMotorShaftPower,
        double sizeMargin
    ) :
        optimalMotorShaftPower_(optimalMotorShaftPower),
        sizeMargin_(sizeMargin)
    {};

    double calculate();

private:
    double optimalMotorShaftPower_;
    double sizeMargin_;
    double optimalMotorRatedPower_;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSIZE_H
