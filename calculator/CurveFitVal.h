//
// Created by ehm on 9/8/2016.
//

#ifndef AMO_LIBRARY_CURVEFITVAL_H
#define AMO_LIBRARY_CURVEFITVAL_H

#include <cmath>
#include <vector>

class CurveFitVal {
private:
    int noIntervalPoints_;
    int pdegree_;
    double *xcoord_;
    double *ycoord_;
    double loadFactor_;
    // It is the output. Array to store coefficients of the polynomial curve
public:
    CurveFitVal(int noIntervalPoints, double xcoord[], double ycoord[], int pdegree, double loadFactor) {
        noIntervalPoints_ = noIntervalPoints;
        pdegree_ = pdegree;
        xcoord_ = new double[noIntervalPoints_];
        ycoord_ = new double[noIntervalPoints_];
        xcoord_ = xcoord; // Copying the pointer to 1st element, will make a complete copy if it hampers later.
        ycoord_ = ycoord;
        loadFactor_ = loadFactor;
    }

//    virtual ~CurveFitVal() {
//        delete xcoord_;
//        delete ycoord_;
//    }

    double calculate();
};


#endif //AMO_LIBRARY_CURVEFITVAL_H
