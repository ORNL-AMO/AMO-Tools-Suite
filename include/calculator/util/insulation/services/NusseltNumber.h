#ifndef AMO_LIBRARY_NUSSELTNUMBER_H
#define AMO_LIBRARY_NUSSELTNUMBER_H

class NusseltNumber
{
public:
    NusseltNumber(double a, double b)
        : _a(a), _b(b) {}

    double calculate();
    double calculateForcedConvection();
    double calculateFreeConvection();

private:
    double _a;
    double _b;
};

#endif //AMO_LIBRARY_NUSSELTNUMBER_H