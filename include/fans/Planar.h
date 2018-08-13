#ifndef AMO_TOOLS_SUITE_PLANAR_H
#define AMO_TOOLS_SUITE_PLANAR_H

#include <vector>
#include <cmath>

// to be inherited by planes 3 and 3a, 3b
class VelocityPressureTraverseData {
public:
	double getPv3Value() const {
		return pv3;
	}

	double get75percentRule() const {
		return percent75Rule;
	}
protected:
	// protected constructor to be used only during the construction of its derived classes
	VelocityPressureTraverseData(const double pitotTubeCoefficient,
	                             std::vector< std::vector< double > > traverseHoleData)
			: pitotTubeCoefficient(pitotTubeCoefficient), traverseHoleData(std::move(traverseHoleData))
	{
		double maxPv3r = 0.0;
		double sumPv3r = 0.0;
		for (auto & row : this->traverseHoleData) {
			for (double & val : row) {
				if (val <= 0) {
					val = 0;
					continue;
				}
				val *= std::pow(pitotTubeCoefficient, 2);
				if (val > maxPv3r) {
					maxPv3r = val;
				}
				sumPv3r += std::sqrt(val);
			}
		}

		pv3 = std::pow(sumPv3r / (this->traverseHoleData.size() * this->traverseHoleData[0].size()), 2);

		std::size_t count = 0;
		for (auto & row : this->traverseHoleData) {
			for (auto & val : row) {
				if (val > (0.1 * maxPv3r)) count++;
			}
		}

		percent75Rule = count / static_cast<double>(this->traverseHoleData.size() * this->traverseHoleData[0].size());
	}

	const double pitotTubeCoefficient;
	double pv3 = 0, percent75Rule = 0;

	std::vector< std::vector< double > > traverseHoleData;

	friend class PlaneData;
};

class Planar {
protected:
	Planar(const double area, const double tdx, const double pbx, const double psx)
			: dryBulbTemperature(tdx), barometricPressure(pbx), area(area), staticPressure(psx)
	{}

	const double dryBulbTemperature, barometricPressure, area;
	double gasDensity = 0, gasVelocity = 0, gasVolumeFlowRate = 0, gasVelocityPressure = 0, gasTotalPressure = 0;
	double staticPressure = 0;

	friend class PlaneData;
	friend class Fan203;
};

class FlangePlane : public Planar {
public:
	FlangePlane(const double area, const double tdx, const double pbx)
			: Planar(area, tdx, pbx, 0) {}
};

class TraversePlane : public Planar, public VelocityPressureTraverseData {
public:
	TraversePlane(const double area, const double tdx, const double pbx, const double psx,
				  const double pitotTubeCoefficient, std::vector< std::vector< double > > traverseHoleData)
			: Planar(area, tdx, pbx, psx),
			  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
	{}
};

class MstPlane : public Planar {
public:
	MstPlane(const double area, const double tdx, const double pbx, const double psx)
			: Planar(area, tdx, pbx, psx) {}
};

#endif //AMO_TOOLS_SUITE_PLANAR_H
