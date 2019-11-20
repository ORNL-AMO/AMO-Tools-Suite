#ifndef AMO_LIBRARY_INSULATEDTANKOUTPUT_H
#define AMO_LIBRARY_INSULATEDTANKOUTPUT_H

class InsulatedTankOutput
{
public:
    InsulatedTankOutput();
    InsulatedTankOutput(double heatLoss, double annualHeatLoss) : _heatLoss(heatLoss), _annualHeatLoss(annualHeatLoss) {}

    double getHeatLoss();
    double getAnnualHeatLoss();
    void setHeatLoss(double heatLoss);
    void setAnnualHeatLoss(double annualHeatLoss);

private:
    double _heatLoss;
    double _annualHeatLoss;
};

#endif