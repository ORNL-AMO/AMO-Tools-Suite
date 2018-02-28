#include "fans/Planar.h"

Planar::Planar(const double area, const double tdx, const double pbx, const double psx)
		: dryBulbTemperature(tdx), barometricPressure(pbx), area(area), staticPressure(psx)
{}

FanInletFlange::FanInletFlange(const double area, const double tdx, const double pbx)
		: Planar(area, tdx, pbx, 0) {}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double area, const double tdx, const double pbx)
		: Planar(area, tdx, pbx, 0) {}

FlowTraverse::FlowTraverse(const double area, const double tdx, const double pbx,
                           const double psx, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > traverseHoleData)
		: Planar(area, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
{}

AddlTravPlane::AddlTravPlane(const double area, const double tdx, const double pbx,
                             const double psx, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > traverseHoleData)
		: Planar(area, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, std::move(traverseHoleData))
{}

InletMstPlane::InletMstPlane(const double area, const double tdx, const double pbx, const double psx)
		: Planar(area, tdx, pbx, psx) {}

OutletMstPlane::OutletMstPlane(const double area, const double tdx, const double pbx,
                               const double psx)
		: Planar(area, tdx, pbx, psx) {}

VelocityPressureTraverseData::VelocityPressureTraverseData(const double pitotTubeCoefficient,
                                                           std::vector< std::vector< double > > traverseHoleData)
		: pitotTubeCoefficient(pitotTubeCoefficient), traverseHoleData(std::move(traverseHoleData))
{
	auto maxPv3r = 0.0;
	auto sumPv3r = 0.0;
	for (auto & row : this->traverseHoleData) {
		for (auto & val : row) {
			if (val <= 0) {
				val = 0;
				continue;
			}
			val *= std::pow(pitotTubeCoefficient, 2);
			if (val > maxPv3r) maxPv3r = val;
			sumPv3r += std::sqrt(val);
		}
	}

	// TODO this pv3 value differs slightly from what is in the document
	pv3 = std::pow(sumPv3r / (this->traverseHoleData.size() * this->traverseHoleData[0].size()), 2);

	std::size_t count = 0;
	for (auto & row : this->traverseHoleData) {
		for (auto & val : row) {
			if (val > (0.1 * maxPv3r)) count++;
		}
	}

	percent75Rule = count / static_cast<double>(this->traverseHoleData.size() * this->traverseHoleData[0].size());
}
