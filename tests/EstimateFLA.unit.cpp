#include "catch.hpp"
#include <sqlite/SQLite.h>
//#include <calculator/motor/MotorEfficiency.h>
#include <calculator/motor/EstimateFLA.h>
#include <fstream>


TEST_CASE( "Estimate FLA", "[EstimateFLA]" ) {
    auto fla1 = EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 94, 460);
    auto fla2 = EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 95, 460);
    
    std::ofstream fout;
    fout.open("debug.txt", std::ios::app);
    auto results1 = fla1.calculate();
    auto results2 = fla2.calculate();
    fout << "EstimateFLA.unit.cpp" << std::endl;
    fout << "------------------------" << std::endl;
    fout << "results1:" << std::endl;
    fout << "{";
    for (const double &result : results1)
    {
        fout << result << ", ";
    }
    fout << "}";
    fout << std::endl;
    fout << "results2:" << std::endl;
    fout << "{";
    for (const double &result : results2)
    {
        fout << result << ", ";
    }
    fout << "}";
    fout << std::endl;
    auto estFLA1 = fla1.getEstimatedFLA();
    auto estFLA2 = fla2.getEstimatedFLA();
    fout << "estFLA1: " << estFLA1 << std::endl;
    fout << "estFLA2: " << estFLA2 << std::endl;
    fout << "End" << std::endl;
    fout << "------------------------" << std::endl;
    fout.close();

    CHECK(estFLA1 == Approx(228.4));
    CHECK(estFLA2 == Approx(227.3));
    //CHECK(EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 94, 460).calculate() == Approx(227.3));
    //CHECK(EstimateFLA(200, 1780, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 95, 460).calculate() == Approx(228.4));
} 