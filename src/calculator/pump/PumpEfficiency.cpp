/**
 * @brief 
 *
 * @author Mark Root (mroot)
 * @bug No known bugs.
 *
 */

#include "calculator/pump/PumpEfficiency.h"
#include "calculator/pump/OptimalPrePumpEff.h"
#include "calculator/pump/OptimalDeviationFactor.h"

PumpEfficiency::Output PumpEfficiency::calculate() {

    OptimalPrePumpEff pef(style, flow);
    double average = pef.calculate();
    double odf = OptimalDeviationFactor(flow).calculate();
    double max = average * odf;

    return {average, max};
}
