#ifndef AMO_LIBRARY_REYNOLDSNUMBER_H
#define AMO_LIBRARY_REYNOLDSNUMBER_H

class ReynoldsNumber
{
public:
    ReynoldsNumber(double diameter, double windVelocity, double kinematicViscosity)
        : _diameter(diameter), _windVelocity(windVelocity), _kinematicViscosity(kinematicViscosity) {}

    double calculate();

private:
    double _diameter;
    double _windVelocity;
    double _kinematicViscosity;
};

#endif //AMO_LIBRARY_REYNOLDSNUMBER_H