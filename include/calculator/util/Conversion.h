#ifndef AMO_LIBRARY_CONVERSION_H
#define AMO_LIBRARY_CONVERSION_H

class Conversion
{
  public:
    Conversion(double x)
        : x(x)
    {}

    double fractionToPercent();
    double percentToFraction();
    double manualConversion(double factor);

  private:
    double x;
};

#endif //AMO_LIBRARY_CONVERSION_H