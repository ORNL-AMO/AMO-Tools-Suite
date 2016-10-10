//
// Created by ehm on 9/8/2016.
//

#include "CurveFitVal.h"
#include <iostream>
using namespace std;
double CurveFitVal::calculate() {
    /*
     * Iterators
     */
    int i, j, k;
    /*
     * Array to store Sigma X values
     */
    vector<double> sigmaX_(2 * pdegree_ + 1);
    for (i = 0; i < 2 * pdegree_ + 1; i++) {
        sigmaX_[i] = 0;
        for (j = 0; j < noIntervalPoints_; j++)
            sigmaX_[i] = sigmaX_[i] + pow(xcoord_[j], i);
    }

    /*
     * Array to store Sigma Y values
     */
    vector<double> sigmaY_(2 * pdegree_ + 1);
    for (i = 0; i < pdegree_ + 1; i++) {
        sigmaY_[i] = 0;
        for (j = 0; j < noIntervalPoints_; j++)
            sigmaY_[i] = sigmaY_[i] + pow(xcoord_[j], i) * ycoord_[j];
    }
    /*
     * Array to store matrix which in turn store the equations
     */
    std::vector<std::vector<double>> augMatrix(pdegree_ + 1, std::vector<double>(pdegree_ + 2, 0));
    // double augMatrix[pdegree_ + 1][pdegree_ + 2];
    for (i = 0; i <= pdegree_; i++)
        for (j = 0; j <= pdegree_; j++)
            augMatrix[i][j] = sigmaX_[i + j];

    for (i = 0; i <= pdegree_; i++)
        augMatrix[i][pdegree_ + 1] = sigmaY_[i];
    /*
     * Array to store the coefficients of the curve.
     */

    //double *coeff_ = new double[pdegree_ + 1];
    //double coeff_[pdegree_ + 1];
    vector<double> coeff_(pdegree_ + 1);
    for (int m = 0; m < pdegree_ + 1; ++m) {
        coeff_[m] = 0;
    }

    int pdegreeplus = pdegree_ + 1;
    /*
     * Using Gaussian Elimination method to solve the matrix [As suggested by online resources]
     * Look to citations for reference
     */

    for (i = 0; i < pdegreeplus; i++)
        for (k = i + 1; k < pdegreeplus; k++)
            if (augMatrix[i][i] < augMatrix[k][i])
                for (j = 0; j <= pdegreeplus; j++) {
                    double temp = augMatrix[i][j];
                    augMatrix[i][j] = augMatrix[k][j];
                    augMatrix[k][j] = temp;
                }

    for (i = 0; i < pdegreeplus - 1; i++)
        for (k = i + 1; k < pdegreeplus; k++) {
            double t = augMatrix[k][i] / augMatrix[i][i];
            for (j = 0; j <= pdegreeplus; j++)
                augMatrix[k][j] = augMatrix[k][j] - t * augMatrix[i][j];
        }
    for (i = pdegreeplus - 1; i >= 0; i--) {
        coeff_[i] = augMatrix[i][pdegreeplus];
        for (j = 0; j < pdegreeplus; j++)
            if (j != i)
                coeff_[i] = coeff_[i] - augMatrix[i][j] * coeff_[j];
        coeff_[i] = coeff_[i] / augMatrix[i][i];
    }

    /*
     * Returning the value instead of the coefficients
     */


    double temp_ = 0;
    for (int l = 0; l < pdegreeplus; ++l) {
        temp_ += coeff_[l] * pow(loadFactor_, l);
    }
    return temp_;
}