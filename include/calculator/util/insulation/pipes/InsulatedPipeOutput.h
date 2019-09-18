#ifndef AMO_LIBRARY_INSULATEDPIPEOUTPUT_H
#define AMO_LIBRARY_INSULATEDPIPEOUTPUT_H

class InsulatedPipeOutput
{
public:
    InsulatedPipeOutput(double annualHeatLoss) : _annualHeatLoss(annualHeatLoss) {}

    double getAnnualHeatLoss();

private:
    double _annualHeatLoss;
};

#endif