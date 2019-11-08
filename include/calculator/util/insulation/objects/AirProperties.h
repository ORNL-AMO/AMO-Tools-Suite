#ifndef AMO_LIBRARY_AIRPROPERTIES_H
#define AMO_LIBRARY_AIRPROPERTIES_H

class AirProperties
{
public:
    // AirProperties();
    AirProperties(double conductivity = 0,
                  double viscosity = 0,
                  double prandtl = 0,
                  double expansionCoefficient = 0,
                  double desnity = 0,
                  double kinViscosity = 0,
                  double specificHeat = 0,
                  double alpha = 0,
                  double reynolds = 0,
                  double rayleigh = 0)
        : _conductivity(conductivity),
          _viscosity(viscosity),
          _prandtl(prandtl),
          _expansionCoefficient(expansionCoefficient),
          _density(desnity),
          _kinViscosity(kinViscosity),
          _specificHeat(specificHeat),
          _alpha(alpha),
          _reynolds(reynolds),
          _rayleigh(rayleigh) {}

    double getConductivity();
    double getViscosity();
    double getPrandtl();
    double getExpansionCoefficient();
    double getDensity();
    double getKinViscosity();
    double getSpecificHeat();
    double getAlpha();
    double getReynolds();
    double getRayleigh();

    void setConductivity(double conductivity);
    void setViscosity(double viscosity);
    void setPrandtl(double prandtl);
    void setExpansionCoefficient(double expansionCoefficient);
    void setDensity(double density);
    void setKinViscosity(double kinViscosity);
    void setSpecificHeat(double specificHeat);
    void setAlpha(double alpha);
    void setReynolds(double reynolds);
    void setRayleigh(double rayleigh);

private:
    double _conductivity;
    double _viscosity;
    double _prandtl;
    double _expansionCoefficient;
    double _density;
    double _kinViscosity;
    double _specificHeat;
    double _alpha;
    double _reynolds;
    double _rayleigh;
};

#endif