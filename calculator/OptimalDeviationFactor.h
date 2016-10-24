//
// Created by Mishra, Subhankar on 10/24/16.
//

#ifndef AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
#define AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H


class OptimalDeviationFactor {
public:
    OptimalDeviationFactor(double flowRate):flowRate_(flowRate){}
    double calculate();
private:
    double flowRate_;
};


#endif //AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
