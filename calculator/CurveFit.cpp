//
// Created by ehm on 8/31/2016.
//

#include "CurveFit.h"

/*
 * Citation: Weisstein, E. W. (2002). Least Squares Fitting--Polynomial. http://mathworld.wolfram.com/LeastSquaresFittingPolynomial.html
 * Citation: https://en.wikipedia.org/wiki/Least_squares
 * Citation: http://mathworld.wolfram.com/GaussianElimination.html
 */
double *CurveFit::calculate() {
    /*
     * Iterators
     */
    int i, j, k;
    /*
     * Array to store Sigma X values
     */
    double sigmaX_[2 * pdegree_ + 1];
    for (i = 0; i < 2 * pdegree_ + 1; i++) {
        sigmaX_[i] = 0;
        for (j = 0; j < noIntervalPoints_; j++)
            sigmaX_[i] = sigmaX_[i] + pow(xcoord_[j], i);
    }
    /*
     * Array to store Sigma Y values
     */
    double sigmaY_[2 * pdegree_ + 1];
    for (i = 0; i < pdegree_ + 1; i++) {
        sigmaY_[i] = 0;
        for (j = 0; j < noIntervalPoints_; j++)
            sigmaY_[i] = sigmaY_[i] + pow(xcoord_[j], i) * ycoord_[j];
    }
    /*
     * Array to store matrix which in turn store the equations
     */
    double augMatrix[pdegree_ + 1][pdegree_ + 2];
    for (i = 0; i <= pdegree_; i++)
        for (j = 0; j <= pdegree_; j++)
            augMatrix[i][j] = sigmaX_[i + j];

    for (i = 0; i <= pdegree_; i++)
        augMatrix[i][pdegree_ + 1] = sigmaY_[i];
    /*
     * Array to store the coefficients of the curve.
     */
    /*
     * To new or not to new.
     */

    //double coeff_[pdegree_ + 1];
    double *coeff_ = new double[pdegree_ + 1];

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

    return coeff_;
}