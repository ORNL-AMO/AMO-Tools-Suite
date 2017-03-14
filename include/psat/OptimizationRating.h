/**
 * @file
 * @brief Function prototypes for the Financial fields
 *
 * This contains the prototypes for the OptimizationRating structure
 * including getters and setters for the important fields. Primary
 * importance are methods for setting and getting data dealing with
 * optimization.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMIZATIONRATING_H
#define AMO_LIBRARY_OPTIMIZATIONRATING_H


class OptimizationRating {
public:

    /**
     * Constructor
     * @param existingAnnualCost Existing annual energy cost based on the product of the Existing annual energy consumption.
     * @param motorRatedPower Existing annual energy cost based on the product of the Optimal annual energy consumption.
     * @return nothing
     */
    OptimizationRating(
        double existingAnnualCost,
        double optimalAnnualCost
    ) :
        existingAnnualCost_(existingAnnualCost),
        optimalAnnualCost_(optimalAnnualCost)
    {}

    double calculate();

    double getExistingAnnualCost() const {
        return existingAnnualCost_;
    }

    void setExistingAnnualCost(double existingAnnualCost) {
        existingAnnualCost_ = existingAnnualCost;
    }

    double getOptimalAnnualCost() const {
        return optimalAnnualCost_;
    }

    void setOptimalAnnualCost(double optimalAnnualCost) {
        optimalAnnualCost_ = optimalAnnualCost;
    }

private:
    double existingAnnualCost_;
    double optimalAnnualCost_;
};


#endif //AMO_LIBRARY_OPTIMIZATIONRATING_H
