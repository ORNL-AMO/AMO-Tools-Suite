/**
 * @file
 * @brief Calculator for opening heat losses
 *
 * This contains the inputs for calculating an opening heat loss.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_SUITE_OPENINGLOSSES_H
#define AMO_SUITE_OPENINGLOSSES_H

#include <functional>
#include <array>

/**
 * Opening Losses class
 * Contains all the properties of an opening loss.
 * Used to calculate the heat loss caused by heat transfer from the openings on equipment to the surrounding.
 * Only considers thermal radiation losses due to exposure of furnace to the surroundings.
 */
class OpeningLosses {
public:

    /**
     * OpeningShape - Enum class consisting of CIRCULAR and RECTANGULAR entries. Set automatically by the constructor
     * depending on which constructor is chosen, the one with length + width or the one with diameter. The shape of the
     * opening can later be changed via the setOpeningShape methods.
     */
    enum class OpeningShape {
        CIRCULAR,
        RECTANGULAR
    };

    /**
     * Method to calculate viewFactor for circular openings only
     * @param double, thickness - furnace wall thickness in inches
     * @param double, diameter of opening in inches
     * @return double, viewFactor - unitless
     * */
    double calculateViewFactor(double thickness, double diameter);

    /**
     * Method to calculate viewFactor for rectangular openings only
     * @param double, thickness - furnace wall thickness in inches
     * @param double, length - length of opening in inches
     * @param double, height - height of opening in inches
     * @return double, viewFactor - unitless
     */
    double calculateViewFactor(double thickness, double length, double height);

    /**
	 * Constructor for a rectangular opening
	 * @param emissivity double, emissivity - unitless
	 * @param length double, length of openings in inches
     * @param width double, height of openings in inches
	 * @param thickness double, furnace wall thickness in inches
	 * @param ratio double, ratio
	 * @param ambientTemperature double, ambient temperature in °F
	 * @param insideTemperature double, inside temperature in °F
	 * @param percentTimeOpen double, amount of time open as a %
	 * @param viewFactor double, view factor - unitless
	 */
    OpeningLosses(double emissivity,
                  double length,
                  double width,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor)
            : emissivity(emissivity),
              length(length),
              width(width),
              thickness(thickness), ratio(ratio),
              ambientTemperature(ambientTemperature),
              insideTemperature(insideTemperature),
              percentTimeOpen(percentTimeOpen),
              viewFactor(viewFactor),
              openingShape(OpeningShape::RECTANGULAR)
    {}

   /**
    * Constructor for a circular opening
    * @param emissivity double, emissivity - unitless
    * @param diameter double, diameter of opening in inches
    * @param thickness double, furnace wall thickness in inches
    * @param ratio double, ratio
    * @param ambientTemperature double, ambient temperature in °F
    * @param insideTemperature double, inside temperature in °F
    * @param percentTimeOpen double, amount of time open as %
    * @param viewFactor double, view factor - unitless
    */
    OpeningLosses(double emissivity,
                  double diameter,
                  double thickness,
                  double ratio,
                  double ambientTemperature,
                  double insideTemperature,
                  double percentTimeOpen,
                  double viewFactor)
            : emissivity(emissivity),
              diameter(diameter),
              thickness(thickness), ratio(ratio),
              ambientTemperature(ambientTemperature),
              insideTemperature(insideTemperature),
              percentTimeOpen(percentTimeOpen),
              viewFactor(viewFactor),
              openingShape(OpeningShape::CIRCULAR)
    {}

    OpeningLosses() = default;

    /**
     * Gets the emissivity
     * @return double, emissivity - unitless
     */
    double getEmissivity() const {
        return emissivity;
    }


    /**
     * Sets the emissivity
     * @param emissivity double, emissivity - unitless
     */
    void setEmissivity(double emissivity) {
        this->emissivity = emissivity;
    }


    /**
     * Gets the diameter of opening
     * @return double, diameter of opening in inches
     */
    double getDiameter() const {
        return diameter;
    }


    /**
     * Sets the diameter of the circular opening
     * @param diameter double, diameter of opening in inches
     */
    void setDiameter(double diameter) {
        this->diameter = diameter;
    }

    /**
     * Gets the width of the opening
     * @return double, width of opening in inches
     */
    double getWidth() const {
        return width;
    }

    /**
     * Sets the width of opening
     * @param width double, width of opening in inches
     */
    void setWidth(double width) {
        this->width = width;
    }

    /**
     * Gets the furnace wall thickness
     * @return double, furnace wall thickness in inches
     */
    double getThickness() const {
        return thickness;
    }

    /**
     * Sets the furnace wall thickness
     * @param thickness double, furnace wall thickness in inches
     */
    void setThickness(double thickness) {
        this->thickness = thickness;
    }

    /**
     * Gets the ratio
     * @return double, ratio - unitless
     */
    double getRatio() const {
        return ratio;
    }

    /**
     * Sets the ratio
     * @param ratio double, ratio - unitless
     *
     */
    void setRatio(double ratio) {
        this->ratio = ratio;
    }

    /**
     * Gets the ambient temperature
     * @return double, ambient temperature in °F
     */
    double getAmbientTemperature() const {
        return ambientTemperature;
    }

    /**
     * Sets the ambient temperature
     * @param ambientTemperature double, ambient temperature in °F
     */
    void setAmbientTemperature(double ambientTemperature) {
        this->ambientTemperature = ambientTemperature;
    }

    /**
     * Gets the inside temperature
     * @return double, inside temperature in °F
     */
    double getInsideTemperature() const {
        return insideTemperature;
    }

    /**
     * Sets the inside temperature
     * @param insideTemperature double, inside temperature in °F
     */
    void setInsideTemperature(double insideTemperature) {
        this->insideTemperature = insideTemperature;
    }

    /**
     * Gets the percentage of time open
     * @return double, amount of time open as %
     */
    double getPercentTimeOpen() const {
        return percentTimeOpen;
    }

    /**
     * Sets the percentage of time open
     * @param percentTimeOpen double, amount of time open as a %
     */
    void setPercentTimeOpen(double percentTimeOpen) {
        this->percentTimeOpen = percentTimeOpen;
    }

    /**
     * Gets the view factor
     * @return double, view factor - unitless
     */
    double getViewFactor() const {
        return viewFactor;
    }

    /**
     * Sets the view factor manually, can also be calculated via one of the calculateViewFactor methods
     * @param viewFactor double, view factor - unitless
     */
    void setViewFactor(double viewFactor) {
        this->viewFactor = viewFactor;
    }

    /**
     * Gets the opening shape
     * @return OpeningShape, classification of shape of opening
     */
    OpeningShape getOpeningShape() const {
        return openingShape;
    }

    /**
     * Sets the opening shape - you better be calling this to set shape to RECTANGULAR
     * @param openingShape OpeningShape, classification of shape of opening
     * @param double, length - length of opening in inches
     * @param double, width - width / height of rectangular opening in inches
     */
    void setOpeningShape(OpeningShape const openingShape, const double length, const double width) {
        if (openingShape != OpeningShape::RECTANGULAR) {
            throw std::runtime_error("Call the other set opening shape function to set openingShape to Circular");
        }
        this->openingShape = openingShape;
        this->length = length;
        this->width = width;
        diameter = 0;
    }

    /**
     * Sets the opening shape - you better be calling this to set shape to CIRCULAR
     * @param openingShape OpeningShape, classification of shape of opening
     * @param double, diameter - diameter of circular opening in inches
     */
    void setOpeningShape(OpeningShape const openingShape, const double diameter) {
        if (openingShape != OpeningShape::CIRCULAR) {
            throw std::runtime_error("Call the other set opening shape function to set openingShape to Rectangular");
        }
        this->openingShape = openingShape;
	    this->diameter = diameter;
        length = 0;
        width = 0;
    }

    /**
     * Gets the heat loss
     * @return double, heat loss in btu/cycle
     */
    double getHeatLoss();

private:
    double emissivity = 0.95;
    double diameter = 0;
    double length = 0, width = 0;
    double thickness;
    double ratio;
    double ambientTemperature;
    double insideTemperature;
    double percentTimeOpen;
    double viewFactor;
    OpeningShape openingShape;

    double heatLoss = 0;

    const std::array<const std::function< double ( const double thicknessRatio ) >, 8> viewFactorEquations = {
            {
                    [](const double tr) {
                        return (1.10000000001829 + 92.8571428570049 * tr - 57.5892857139671 * std::pow(tr, 2) +
                               15.6249999998005 * std::pow(tr, 3)) / 100;
                    }, // case 1
                    [](const double tr) {
                        return (29.4999999989821 + 26.8416666684161 * tr - 4.35416666785322 * std::pow(tr, 2) -
                               8.33333330461522E-02 * std::pow(tr, 3) + 0.104166666655532 * std::pow(tr, 4) -
                               8.33333333686747E-03 * std::pow(tr, 5)) / 100;
                    }, // case 2
                    [](const double tr) {
                        return (3.50000000001719 + 89.5833333332039 * tr - 49.9999999997023 * std::pow(tr, 2) +
                               10.4166666664804 * std::pow(tr, 3)) / 100;
                    }, // case 3
                    [](const double tr) {
                        return (23.9999999965639 + 39.3916666718743 * tr - 11.6041666697487 * std::pow(tr, 2) +
                               1.85416666706894 * std::pow(tr, 3) - 0.145833333217932 * std::pow(tr, 4) +
                               4.16666663902102E-03 * std::pow(tr, 5)) / 100;
                    }, // case 4
                    [](const double tr) {
                        return (2.70000000002409 + 112.678571428391 * tr - 70.9821428567315 * std::pow(tr, 2) +
                               15.6249999997447 * std::pow(tr, 3)) / 100;
                    }, // case 5
                    [](const double tr) {
                        return (35.4999999992976 + 29.4583333347815 * tr - 4.52083333446976 * std::pow(tr, 2) -
                               0.687499999606652 * std::pow(tr, 3) + 0.270833333273064 * std::pow(tr, 4) -
                               2.08333333303721E-02 * std::pow(tr, 5)) / 100;
                    }, // case 6
                    [](const double tr) {
                        return (13.0000000000278 + 123.74999999979 * tr - 99.9999999995182 * std::pow(tr, 2) +
                               31.249999999699 * std::pow(tr, 3)) / 100;
                    }, // case 7
                    [](const double tr) {
                        return (26.9999999903567 + 64.5666666806646 * tr - 29.9166666745008 * std::pow(tr, 2) +
                               7.14583333396145 * std::pow(tr, 3) - 0.833333332874441 * std::pow(tr, 4) +
                               3.74999999085373E-02 * std::pow(tr, 5)) / 100;
                    }, // case 8
            }
    };
};
#endif //AMO_SUITE_OPENINGLOSSES_H
