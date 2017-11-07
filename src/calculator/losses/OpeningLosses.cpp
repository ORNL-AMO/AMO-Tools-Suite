/**
 * @file
 * @brief Contains the implementation of the opening leakage losses calculations.
 *
 * @author Gina Accawi (accawigk) & Preston Shires (pshires)
 * @bug No known bugs.
 *
 */

#include <cmath>
#include <stdexcept>
#include "calculator/losses/OpeningLosses.h"

double OpeningLosses::getHeatLoss() {
    const double pi = 3.141592653589793238463;
    const double stephenBoltzman = 0.1713 * pow(10, -8);
    double area;

    if ( openingShape == OpeningShape::CIRCULAR ) {
        const double d = diameter / 12;
        area = pi * (d / 2) * (d / 2);
    } else {
        area = (diameter * width) / 144;
    }

    const double hlRad = emissivity * stephenBoltzman * (pow(insideTemperature + 460, 4) -
                          pow(ambientTemperature + 460, 4)) * area;

    heatLoss = hlRad * viewFactor * percentTimeOpen / 100;
    return heatLoss;
}

double OpeningLosses::calculateViewFactor(OpeningLosses::OpeningShape const shape, const double thickness,
                                          const double diameter)
{
    if (shape != OpeningLosses::OpeningShape::CIRCULAR) {
        throw std::runtime_error("OpeningShape must be circular");
    }

    if (!diameter) return 0;
    const double thicknessRatio = (!thickness) ? 6.1 : diameter / thickness;




//    dblDiameter = dblLengthDia
//    If dblDiameter = 0 Then
//            CalculateViewFactor = 0
//    Exit Function
//    ElseIf (dblThickness = 0) Then
//            dblThicknessRatio = 6.1
//    Else
//            dblThicknessRatio = dblDiameter / dblThickness
//    End If
    // ^^^ done


    // TODO
//    If (dblThickness = 0 Or dblThicknessRatio > 6) Then
//            CalculateViewFactor = ViewFactorEquation(2, 6)
//    Exit Function
//    ElseIf (dblThicknessRatio < 0.1) Then
//            CalculateViewFactor = ViewFactorEquation(1, 0.1) * dblThicknessRatio / 0.1
//    Exit Function
//    ElseIf (dblThicknessRatio >= 0.1 And dblThicknessRatio < 1) Then
//            CalculateViewFactor = ViewFactorEquation(1, dblThicknessRatio)
//    Exit Function
//    Else
//            CalculateViewFactor = ViewFactorEquation(2, dblThicknessRatio)
//    End If

}

//Public Function ViewFactorEquation(ByRef bytEquationNo As Byte, ByRef dblThicknessRatio As Double) As Double
//Select Case bytEquationNo
//        Case 1
//dblReturnValue = 1.10000000001829 + 92.8571428570049 * dblThicknessRatio - 57.5892857139671 * dblThicknessRatio ^ 2 + 15.6249999998005 * dblThicknessRatio ^ 3
//Case 2
//dblReturnValue = 29.4999999989821 + 26.8416666684161 * dblThicknessRatio - 4.35416666785322 * dblThicknessRatio ^ 2 - 8.33333330461522E-02 * dblThicknessRatio ^ 3 + 0.104166666655532 * dblThicknessRatio ^ 4 - 8.33333333686747E-03 * dblThicknessRatio ^ 5
//Case 3
//dblReturnValue = 3.50000000001719 + 89.5833333332039 * dblThicknessRatio - 49.9999999997023 * dblThicknessRatio ^ 2 + 10.4166666664804 * dblThicknessRatio ^ 3
//Case 4
//dblReturnValue = 23.9999999965639 + 39.3916666718743 * dblThicknessRatio - 11.6041666697487 * dblThicknessRatio ^ 2 + 1.85416666706894 * dblThicknessRatio ^ 3 - 0.145833333217932 * dblThicknessRatio ^ 4 + 4.16666663902102E-03 * dblThicknessRatio ^ 5
//Case 5
//dblReturnValue = 2.70000000002409 + 112.678571428391 * dblThicknessRatio - 70.9821428567315 * dblThicknessRatio ^ 2 + 15.6249999997447 * dblThicknessRatio ^ 3
//Case 6
//dblReturnValue = 35.4999999992976 + 29.4583333347815 * dblThicknessRatio - 4.52083333446976 * dblThicknessRatio ^ 2 - 0.687499999606652 * dblThicknessRatio ^ 3 + 0.270833333273064 * dblThicknessRatio ^ 4 - 2.08333333303721E-02 * dblThicknessRatio ^ 5
//Case 7
//dblReturnValue = 13.0000000000278 + 123.74999999979 * dblThicknessRatio - 99.9999999995182 * dblThicknessRatio ^ 2 + 31.249999999699 * dblThicknessRatio ^ 3
//Case 8
//dblReturnValue = 26.9999999903567 + 64.5666666806646 * dblThicknessRatio - 29.9166666745008 * dblThicknessRatio ^ 2 + 7.14583333396145 * dblThicknessRatio ^ 3 - 0.833333332874441 * dblThicknessRatio ^ 4 + 3.74999999085373E-02 * dblThicknessRatio ^ 5