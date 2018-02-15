/**
 * @brief Contains the definition of functions of OptimalMotorSize class.
 *      calculate(): Calculates the Optimal Motor Size
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @author Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include <set>
#include "calculator/motor/OptimalMotorSize.h"

double OptimalMotorSize::calculate() {
    // Motor Size collection in hp
    static const std::set<double> motorSize = {
            0, 5, 7.5, 10, 15, 20, 25, 30, 40, 50, 60, 75, 100, 125, 150, 200, 250, 300, 350, 400, 450, 500, 600, 700,
            800, 900, 1000, 1250, 1500, 1750, 2000, 2250, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 7000, 8000,
            9000, 10000, 11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000, 22500, 25000, 27500,
            30000, 35000, 40000, 45000, 50000
    };

    double const requiredShaftPower = optimalMotorShaftPower * (1 + sizeMargin);
    optimalMotorRatedPower = *motorSize.lower_bound(requiredShaftPower);
    return optimalMotorRatedPower;
}
