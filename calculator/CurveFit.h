//
// Created by ehm on 8/31/2016.
//

#ifndef AMO_LIBRARY_POLYNOMIALFIT_H
#define AMO_LIBRARY_POLYNOMIALFIT_H

#include<iomanip>
#include<cmath>

/*
 * Polynomial Fit uses Least Squares method to calculate the coefficients of the equation for the curve given the interval points
 * Input:
 * - Number of interval points
 * - X axis coordinates [array]
 * - Y axis coordinates [array]
 * - Degree of polynomial curve
 *
 * Output:
 * - Coefficients of the polynomial curve in ascending order.
 */

class CurveFit {
private:
    int noIntervalPoints_;
    int pdegree_;
    double *xcoord_;
    double *ycoord_;
    // It is the output. Array to store coefficients of the polynomial curve
public:
    CurveFit(int noIntervalPoints, double xcoord[], double ycoord[], int pdegree, double coeff[]) {
        noIntervalPoints_ = noIntervalPoints;
        pdegree_ = pdegree;
        xcoord_ = new double[noIntervalPoints_];
        ycoord_ = new double[noIntervalPoints_];
        xcoord_ = xcoord; // Copying the pointer to 1st element, will make a complete copy if it hampers later.
        ycoord_ = ycoord;
    }

    double *calculate();
};


#endif //AMO_LIBRARY_POLYNOMIALFIT_H
