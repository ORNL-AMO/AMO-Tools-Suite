#include "catch.hpp"
#include <calculator/motor/MotorEfficiency.h>

TEST_CASE( "Calculate Motor Efficiency - 200 HP", "[MotorEfficiency]" ) {
    MotorEfficiency motorEff(Motor::LineFrequency::FREQ60, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 200, 0);

    {
        motorEff.setLoadFactor( 0.0 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.0 ) );
    }

    {
        motorEff.setLoadFactor( 0.25 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.930393384 ) );
    }

    {
        motorEff.setLoadFactor( 0.5 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.949504131 ) );
    }

    {
        motorEff.setLoadFactor( 0.75 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.9569034 ) );
    }

    {
        motorEff.setLoadFactor( 1.0 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.956259245 ) );
    }

    {
        motorEff.setLoadFactor( 1.25 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.946696653 ) );
    }

}

TEST_CASE( "Calculate Motor Efficiency - 100 HP", "[MotorEfficiency]" ) {
    MotorEfficiency motorEff(Motor::LineFrequency::FREQ60, 1785, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 100, 0);

    {
        motorEff.setLoadFactor( 0.0 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.0 ) );
    }

    {
        motorEff.setLoadFactor( 0.25 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.921519665 ) );
    }

    {
        motorEff.setLoadFactor( 0.5 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.946047805 ) );
    }

    {
        motorEff.setLoadFactor( 0.75 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.951033931 ) );
    }

    {
        motorEff.setLoadFactor( 1.0 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.949413679 ) );
    }

    {
        motorEff.setLoadFactor( 1.25 );
        INFO( "Load Factor == " << motorEff.getLoadFactor() );
        CHECK( motorEff.calculate() == Approx( 0.939919542 ) );
    }

}
