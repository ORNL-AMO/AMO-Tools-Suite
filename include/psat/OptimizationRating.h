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
     * @param existingAnnualCost double, existing annual energy cost based on the product of the existing annual energy consumption in $/year
     * @param optimalAnnualCost double, existing annual energy cost based on the product of the optimal annual energy consumption in $/year
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
     * @return double, optimization rating as %
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
     * @param existingAnnualCost double, existing annual cost in $/year
     *
     * @return nothing
     */
    void setExistingAnnualCost(double existingAnnualCost) {
        existingAnnualCost_ = existingAnnualCost;
    }

    /**
     * Gets the optimal annual cost
     *
     * @return double, optimal annual cost in $/year
     */
    double getOptimalAnnualCost() const {
        return optimalAnnualCost_;
    }

    /**
     * Sets the optimal annual cost
     *
     * @param optimalAnnualCost double, optimal annual cost in $/year
     *
     * @return nothing
     */
    void setOptimalAnnualCost(double optimalAnnualCost) {
        optimalAnnualCost_ = optimalAnnualCost;
    }

private:
    double existingAnnualCost_;
    double optimalAnnualCost_;
};


#endif //AMO_LIBRARY_OPTIMIZATIONRATING_H
