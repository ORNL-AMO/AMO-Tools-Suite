#ifndef AMO_LIBRARY_INSULATEDTANKOUTPUT_H
#define AMO_LIBRARY_INSULATEDTANKOUTPUT_H

class InsulatedTankOutput
{
public:
    InsulatedTankOutput();
    InsulatedTankOutput(double heatLength, double annualHeatLoss) : _heatLength(heatLength), _annualHeatLoss(annualHeatLoss) {}

    double getHeatLength();
    double getAnnualHeatLoss();
    void setHeatLength(double heatLength);
    void setAnnualHeatLoss(double annualHeatLoss);

private:
    double _heatLength;
    double _annualHeatLoss;
};

#endif