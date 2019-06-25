/**
 * @brief Contains the definition of functions of OptimalPrePumpEff class.
 *      calculate(): Calculates the pump efficiency before correction
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include "calculator/pump/OptimalPrePumpEff.h"

double OptimalPrePumpEff::calculate() {
    /*
     * DOUBLE_SUCTION
     */
    const double jCoeff[5][2] = {{90.190375,     91.0},
                           {-7.8068742,    -3.6664629},
                           {0.00033366482, 0.0001264433},
                           {-8.1364684,    -14.697275},
                           {0.0026659434,  0.00072855045}};
    /*
     * VERTICAL_TURBINE
     */
    const double vCoeff[5][3] = {{87.456119,     89.899894,     90.124016},
                           {-9.3556039,    -5.9800814,    -1.7332611},
                           {0.00067139092, 0.00019480643, 0.00014953651},
                           {-9.4309496,    -7.0638099,    -3.3197451},
                           {0.0039344122,  0.0010440162,  0.00015232542}};
    /*
     * LARGE_END_SUCTION
     */
    const double gCoeff[5] = {90.379274,
                        -3.000737,
                        0.000034054964,
                        -4.818246,
                        0.00019083831};
    /*
     * END_SUCTION_ANSI_API
     */
    const double fCoeff[5][2] = {{84.655455,    87.748473},
                           {-18.706336,   -7.6842423},
                           {0.0016056629, 0.0003739105},
                           {-20.655962,   -17.336122},
                           {0.0081197589, 0.0024096967}};
    /*
     * MULTISTAGE_BOILER_FEED
     */
    const double eCoeff[5][2] = {{84.286574,    87.129684},
                           {-17.836167,   -7.8144274},
                           {0.0013236525, 0.00034998448},
                           {-26.951966,   -19.605637},
                           {0.0068256307, 0.0022387671}};
    /*
     * API_DOUBLE_SUCTION
     * and
     * END_SUCTION_STOCK
     */
    const double dhCoeff[5][2] = {{87.199887,     90.158464},
                            {-10.580842,    -4.8350009},
                            {0.00027878405, 0.000048652395},
                            {-23.785033,    -7.2881572},
                            {0.0018831236,  0.00027630687}};
    /*
     * END_SUCTION_SUBMERSIBLE_SEWAGE
     * and
     * END_SUCTION_SEWAGE
     */
    const double bcCoeff[5][2] = {{83.528143,     89.704526},
                            {-23.543231,    -6.9708815},
                            {0.00071315587, 0.000057096295},
                            {-37.584938,    -13.868089},
                            {0.005809375,   0.00046766436}};
    /*
     * END_SUCTION_SLURRY
     */
    const double aCoeff[5][2] = {{79.096487,     85.957484},
                           {-32.006283,    -15.256678},
                           {0.00084199445, 0.00017627657},
                           {-23.100062,    -24.920847},
                           {0.0064912714,  0.0012055457}};

    /*
     * Below format has been kept to mimic the excel sheet. There must be a better way to do this.
     */

    int range = 0;
    switch (style) {
        case Pump::Style::DOUBLE_SUCTION:
	        range = (flowRate < 9000) ? 0 : 1;
            return jCoeff[0][range] + (jCoeff[1][range] * std::exp(-jCoeff[2][range] * flowRate) +
                                       jCoeff[3][range] * std::exp(-jCoeff[4][range] * flowRate));

        case Pump::Style::VERTICAL_TURBINE:
        case Pump::Style::AXIAL_FLOW:
            if (flowRate < 2550) {
                range = 0;
            } else {
	            range = (flowRate < 7220) ? 1 : 2;
            }
            return vCoeff[0][range] + (vCoeff[1][range] * std::exp(-vCoeff[2][range] * flowRate) +
                                       vCoeff[3][range] * std::exp(-vCoeff[4][range] * flowRate));

        case Pump::Style::LARGE_END_SUCTION:
            return gCoeff[0] + (gCoeff[1] * std::exp(-gCoeff[2] * flowRate) +
                                 gCoeff[3] * std::exp(-gCoeff[4] * flowRate));

        case Pump::Style::END_SUCTION_ANSI_API:
	        range = (flowRate < 1030) ? 0 : 1;
            return fCoeff[0][range] + (fCoeff[1][range] * std::exp(-fCoeff[2][range] * flowRate) +
                                       fCoeff[3][range] * std::exp(-fCoeff[4][range] * flowRate));

        case Pump::Style::MULTISTAGE_BOILER_FEED:
	        range = (flowRate < 890) ? 0 : 1;
            return eCoeff[0][range] + (eCoeff[1][range] * std::exp(-eCoeff[2][range] * flowRate) +
                                       eCoeff[3][range] * std::exp(-eCoeff[4][range] * flowRate));

        case Pump::Style::END_SUCTION_STOCK:
        case Pump::Style::API_DOUBLE_SUCTION:
            range = (flowRate < 4440) ? 0 : 1;
            return dhCoeff[0][range] + (dhCoeff[1][range] * std::exp(-dhCoeff[2][range] * flowRate) +
                                        dhCoeff[3][range] * std::exp(-dhCoeff[4][range] * flowRate));

        case Pump::Style::END_SUCTION_SEWAGE:
        case Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE:
	        range = (flowRate < 2170) ? 0 : 1;
            return bcCoeff[0][range] + (bcCoeff[1][range] * std::exp(-bcCoeff[2][range] * flowRate) +
                                        bcCoeff[3][range] * std::exp(-bcCoeff[4][range] * flowRate));

        case Pump::Style::END_SUCTION_SLURRY:
	        range = (flowRate < 1690) ? 0 : 1;
            return aCoeff[0][range] + (aCoeff[1][range] * std::exp(-aCoeff[2][range] * flowRate) +
                                       aCoeff[3][range] * std::exp(-aCoeff[4][range] * flowRate));

    }
    
}
