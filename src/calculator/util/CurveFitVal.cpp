/**
 * @brief Contains the definition of functions of CurveFitVal class.
 *      calculate(): Calculates the curve fit value
 *
 * Given a set of x and y coordinates and degree of polynomial curve to fit, it calculates the curve fit value
 * for a particular x coordinate value (read load factor here).
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include <vector>
#include "calculator/util/CurveFitVal.h"

/**
 * Given a set of x and y coordinates and degree of polynomial curve to fit, it calculates the curve fit value
 * for a particular x coordinate value (read load factor here).
 * @return curve fit value.
 */
double CurveFitVal::calculate() const {
    // Array to store Sigma X values
    std::vector<double> sigmaX(2 * pdegree + 1, 0);
    for (std::size_t i = 0; i < 2 * pdegree + 1; i++) {
        for (auto const val : xcoord) {
            sigmaX[i] += std::pow(val, i);
        }
    }

    // Array to store Sigma Y values
    std::vector<double> sigmaY_(2 * pdegree + 1, 0);
    for (std::size_t i = 0; i < pdegree + 1; i++) {
        for (std::size_t j = 0; j < xcoord.size(); j++)
            sigmaY_[i] = sigmaY_[i] + std::pow(xcoord[j], i) * ycoord[j];
    }

    // Array to store matrix which in turn store the equations
    std::vector<std::vector<double>> augMatrix(pdegree + 1, std::vector<double>(pdegree + 2, 0));
    for (std::size_t i = 0; i <= pdegree; i++) {
        for (std::size_t j = 0; j <= pdegree; j++) {
            augMatrix[i][j] = sigmaX[i + j];
        }
    }

    for (std::size_t i = 0; i <= pdegree; i++) {
        augMatrix[i][pdegree + 1] = sigmaY_[i];
    }

    /**
     * Using Gaussian Elimination method to solve the matrix [As suggested by online resources]
     * Look to citations for reference
     */

    std::size_t const pdegreeplus = pdegree + 1;
    for (std::size_t i = 0; i < pdegreeplus; i++) {
        for (std::size_t k = i + 1; k < pdegreeplus; k++) {
            if (augMatrix[i][i] < augMatrix[k][i]) {
                for (std::size_t j = 0; j <= pdegreeplus; j++) {
                    double temp = augMatrix[i][j];
                    augMatrix[i][j] = augMatrix[k][j];
                    augMatrix[k][j] = temp;
                }
            }
        }
    }

    for (std::size_t i = 0; i < pdegreeplus - 1; i++) {
        for (std::size_t k = i + 1; k < pdegreeplus; k++) {
            double t = augMatrix[k][i] / augMatrix[i][i];
            for (std::size_t j = 0; j <= pdegreeplus; j++)
                augMatrix[k][j] -= t * augMatrix[i][j];
        }
    }

    /**
     * Array to store the coefficients of the curve.
     */
    std::vector<double> coeff(pdegree + 1, 0);
    for (auto i = static_cast<int>(pdegreeplus - 1); i >= 0; i--) {
        coeff[i] = augMatrix[i][pdegreeplus];
        for (std::size_t j = 0; j < pdegreeplus; j++) {
            if (j == i) continue;
            coeff[i] = coeff[i] - augMatrix[i][j] * coeff[j];
        }
        coeff[i] = coeff[i] / augMatrix[i][i];
    }

    /**
     * Returning the value instead of the coefficients
     */
    double curveFitVal = 0;
    for (int i = 0; i < pdegreeplus; ++i) {
        curveFitVal += coeff[i] * std::pow(loadFactor, i);
    }
    return curveFitVal;
}
