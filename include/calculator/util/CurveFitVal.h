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
        const int pdegree,
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

//    /**
//     * Constructor
//     * @param noIntervalPoints int, number of interval points
//     * @param xcoord array of x coordinates as doubles
//     * @param ycoord array of y coordinates as doubles
//     * @param pdegree int, degree of polynomial curve
//     * @param loadFactor double, load factor - unitless
//     */
//    CurveFitVal(
//        int noIntervalPoints,
//        double xcoord[],
//        double ycoord[],
//        int pdegree,
//        double loadFactor
//    ) :
//        noIntervalPoints(noIntervalPoints),
//        pdegree(pdegree),
//        xcoord(xcoord),
//        ycoord(ycoord),
//        loadFactor(loadFactor)
//    {}

    /**
     * Calculates the curve fit value at required load factor
     * @return double, curve fit value
     */
    double calculate() const;

private:
    /**
     * Degree of polynomial curve
     */
    const size_t pdegree;
    /**
     * x and y coordinates
     */
    const std::vector<double> xcoord, ycoord;
    /**
     * load factor (here is the x coordinate, whose corresponding y coordinate is returned.
     */
    const double loadFactor;
};


#endif //AMO_LIBRARY_CURVEFITVAL_H
