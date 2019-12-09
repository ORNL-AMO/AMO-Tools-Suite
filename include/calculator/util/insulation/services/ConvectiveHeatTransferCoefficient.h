#ifndef AMO_LIBRARY_CONVECTIVEHEATTRANSFERCOEFFICIENT_H
#define AMO_LIBRARY_CONVECTIVEHEATTRANSFERCOEFFICIENT_H

class ConvectiveHeatTransferCoefficient
{
public:
    ConvectiveHeatTransferCoefficient(double nusselt, double airConductivity, double diameter)
        : _nusselt(nusselt), _airConductivity(airConductivity), _diameter(diameter) {}

    double calculate();

private:
    double _nusselt;
    double _airConductivity;
    double _diameter;
};

#endif //AMO_LIBRARY_CONVECTIVEHEATTRANSFERCOEFFICIENT_H