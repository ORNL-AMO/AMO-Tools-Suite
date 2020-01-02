/**
 * @brief Curve Fit class
 *
 * This contains the prototypes for the Curve Fit Value calculator.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_CURVEFITVAL_H
#define AMO_LIBRARY_CURVEFITVAL_H

#include <vector>
#include <exception>
#include <stdexcept>

class CurveFitVal {
public:
    /**
     * Constructor
     * @param xcoord vector of x coordinates as doubles
     * @param ycoord vector of y coordinates as doubles
     * @param pdegree int, degree of polynomial curve
     * @param loadFactor double, load factor - unitless
     */
    CurveFitVal(
        std::vector<double> xcoord,
        std::vector<double> ycoord,
        const std::size_t pdegree,
        const double loadFactor
    ) :
        pdegree(pdegree),
        xcoord(std::move(xcoord)),
        ycoord(std::move(ycoord)),
        loadFactor(loadFactor)
    {
        if (this->xcoord.size() != this->ycoord.size()) {
            throw std::runtime_error("X and Y coordinate vectors must be the same size");
        }
    }

    /**
     * Calculates the curve fit value at required load factor
     * @return double, curve fit value
     */
    double calculate() const;

private:
    /**
     * Degree of polynomial curve
     */
    std::size_t pdegree;
    /**
     * x and y coordinates
     */
    std::vector<double> xcoord, ycoord;
    /**
     * load factor (here is the x coordinate, whose corresponding y coordinate is returned.
     */
    double loadFactor;
};


#endif //AMO_LIBRARY_CURVEFITVAL_H
