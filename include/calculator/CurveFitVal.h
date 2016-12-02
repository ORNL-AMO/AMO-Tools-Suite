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

//
// Created by ehm on 9/8/2016.
//

#ifndef AMO_LIBRARY_CURVEFITVAL_H
#define AMO_LIBRARY_CURVEFITVAL_H

class CurveFitVal {
public:
    /**
     * Constructor
     * @param noIntervalPoints Number of interval points
     * @param xcoord Array of x coordinates
     * @param ycoord Array of y coordinates
     * @param pdegree Degree of polynomial curve
     * @param loadFactor load Factor
     * @return Curve Fit value at required load Factor.
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
     * Calculates the curve fit value
     * @return Curve Fit Value
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
