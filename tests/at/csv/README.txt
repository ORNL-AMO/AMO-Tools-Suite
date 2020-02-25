= Acceptance Test Data README

== Units of Measure
* operationsOutput_makeupWaterVolumeFlow is m3 per hour.
* powerOut, powerGenerated, and sitePowerDemand are kJ per hour.

== Ideal Turbine Expected Data

Ideal data is a complete turbine run, and clients ignore these fields:

* energy
* mass flow
* energy flow
* power

If any tests fail on any of these fields in ideal turbines, just update the expected data to match actual.

For example, these are the expected fields/AT data columns for highPressureToLowPressureTurbineIdealOutput:

* highPressureToLowPressureTurbineIdealOutput_energyOut
* highPressureToLowPressureTurbineIdealOutput_massFlow
* highPressureToLowPressureTurbineIdealOutput_outletEnergyFlow
* highPressureToLowPressureTurbineIdealOutput_powerOut
