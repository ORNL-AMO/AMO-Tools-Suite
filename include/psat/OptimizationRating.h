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
     * @param optimalAnnualCost Existing annual energy cost based on the product of the Optimal annual energy consumption.
     * @return nothing
     */
    OptimizationRating(
        double existingAnnualCost,
        double optimalAnnualCost
    ) :
        existingAnnualCost_(existingAnnualCost),
        optimalAnnualCost_(optimalAnnualCost)
    {}

    /**
     * Calculates the optimization rating
     *
     * @return double, optimization rating
     */
    double calculate();

    /**
     * Gets the existing annual cost
     *
     * @return double, existing annual cost in US $
     */
    double getExistingAnnualCost() const {
        return existingAnnualCost_;
    }

    /**
     * Sets teh existing annual cost
     *
     * @param existingAnnualCost double, existing annual cost in US $
     *
     * @return nothing
     */
    void setExistingAnnualCost(double existingAnnualCost) {
        existingAnnualCost_ = existingAnnualCost;
    }

    /**
     * Gets the optimal annual cost
     *
     * @return double, optimal annual cost
     */
    double getOptimalAnnualCost() const {
        return optimalAnnualCost_;
    }

    /**
     * Sets the optimal annual cost
     *
     * @param optimalAnnualCost double, optimal annual cost in US $
     *
     * @return double, optimization rating
     */
    void setOptimalAnnualCost(double optimalAnnualCost) {
        optimalAnnualCost_ = optimalAnnualCost;
    }

private:
    double existingAnnualCost_;
    double optimalAnnualCost_;
};


#endif //AMO_LIBRARY_OPTIMIZATIONRATING_H
