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

#ifndef AMO_LIBRARY_OPTIMALMOTORSIZE_H
#define AMO_LIBRARY_OPTIMALMOTORSIZE_H

class OptimalMotorSize {
public:
    /**
     * Constructor
     * @param optimalMotorShaftPower double, optimal motor shaft power in hp
     * @param sizeMargin double, size margin as %
     */
    OptimalMotorSize(
        double optimalMotorShaftPower,
        double sizeMargin
    ) :
        optimalMotorShaftPower(optimalMotorShaftPower),
        sizeMargin(sizeMargin/100.0)
    {};

    /**
     * Calculates the optimal motor size
     * @return double, optimal motor size in hp
     */
    double calculate();

private:
    double optimalMotorShaftPower;
    double sizeMargin;
    double optimalMotorRatedPower;
};


#endif //AMO_LIBRARY_OPTIMALMOTORSIZE_H
