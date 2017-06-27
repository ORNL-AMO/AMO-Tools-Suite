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

class CurveFitVal {
public:
    /**
     * Constructor
     * @param noIntervalPoints int, number of interval points
     * @param xcoord array of x coordinates as doubles
     * @param ycoord array of y coordinates as doubles
     * @param pdegree int, degree of polynomial curve
     * @param loadFactor double, load factor - unitless
     * @return nothing
     */
    CurveFitVal(
        int noIntervalPoints,
        double xcoord[],
        double ycoord[],
        int pdegree,
        double loadFactor
    ) :
        noIntervalPoints_(noIntervalPoints),
        pdegree_(pdegree),
        xcoord_(xcoord),
        ycoord_(ycoord),
        loadFactor_(loadFactor)
    {}

    /**
     * Calculates the curve fit value at required load factor
     * @return double, curve fit value
     */
    double calculate();

private:
    /**
     * Number of interval points
     */
    int noIntervalPoints_;
    /**
     * Degree of polynomial curve
     */
    int pdegree_;
    /**
     * x coordinates
     */
    double *xcoord_;
    /**
     * y coordinates
     */
    double *ycoord_;
    /**
     * load factor (here is the x coordinate, whose corresponding y coordinate is returned.
     */
    double loadFactor_;
};


#endif //AMO_LIBRARY_CURVEFITVAL_H
