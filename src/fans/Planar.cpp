#include "fans/Planar.h"

Planar::Planar(const double circularDuctDiameter, const double tdx, const double pbx, const double psx)
		: tdx(tdx), pbx(pbx), area(((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0),
		  psx(psx)
{}

Planar::Planar(const double rectLength, const double rectWidth, const double tdx, const double pbx, const double psx)
		: tdx(tdx), pbx(pbx), area((rectLength * rectWidth) / 144.0), psx(psx)
{}

Planar::Planar(const double rectLength, const double rectWidth, unsigned const noInletBoxes, const double tdx,
               const double pbx, const double psx)
		: tdx(tdx), pbx(pbx), area((rectLength * rectWidth * noInletBoxes) / 144.0), psx(psx)
{}

FanInletFlange::FanInletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
		: Planar(circularDuctDiameter, tdx, pbx, 0) {}

FanInletFlange::FanInletFlange(const double rectLength, const double rectWidth, const double tdx, const double pbx)
		: Planar(rectLength, rectWidth, tdx, pbx, 0) {}

FanInletFlange::FanInletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                               const double tdx, const double pbx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx, 0)
{}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
		: Planar(circularDuctDiameter, tdx, pbx, 0) {}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double rectLength, const double rectWidth, const double tdx,
                                               const double pbx)
		: Planar(rectLength, rectWidth, tdx, pbx, 0) {}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double rectLength, const double rectWidth,
                                               const unsigned noInletBoxes, const double tdx, const double pbx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx, 0)
{}

FlowTraverse::FlowTraverse(const double circularDuctDiameter, const double tdx, const double pbx,
                           const double psx, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > & traverseHoleData)
		: Planar(circularDuctDiameter, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, traverseHoleData)
{}

FlowTraverse::FlowTraverse(const double rectLength, const double rectWidth, const double tdx,
                           const double pbx, const double psx, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, traverseHoleData)
{}

FlowTraverse::FlowTraverse(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                           const double tdx, const double pbx, const double psx, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, traverseHoleData)
{}

AddlTravPlane::AddlTravPlane(const double circularDuctDiameter, const double tdx, const double pbx,
                             const double psx, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > & traverseHoleData)
		: Planar(circularDuctDiameter, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, traverseHoleData)
{}

AddlTravPlane::AddlTravPlane(const double rectLength, const double rectWidth, const double tdx,
                             const double pbx, const double psx, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, traverseHoleData)
{}

AddlTravPlane::AddlTravPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                             const double tdx, const double pbx, const double psx, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx, psx),
		  VelocityPressureTraverseData(pitotTubeCoefficient, traverseHoleData)
{}

InletMstPlane::InletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx, const double psx)
		: Planar(circularDuctDiameter, tdx, pbx, psx) {}

InletMstPlane::InletMstPlane(const double rectLength, const double rectWidth, const double tdx, const double pbx,
                             const double psx)
		: Planar(rectLength, rectWidth, tdx, pbx, psx) {}

InletMstPlane::InletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                             const double tdx, const double pbx, const double psx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx, psx)
{}

OutletMstPlane::OutletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx,
                               const double psx)
		: Planar(circularDuctDiameter, tdx, pbx, psx) {}

OutletMstPlane::OutletMstPlane(const double rectLength, const double rectWidth, const double tdx,
                               const double pbx, const double psx)
		: Planar(rectLength, rectWidth, tdx, pbx, psx) {}

OutletMstPlane::OutletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                               const double tdx, const double pbx, const double psx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx, psx)
{}

VelocityPressureTraverseData::VelocityPressureTraverseData(const double pitotTubeCoefficient,
                                                           std::vector< std::vector< double > > & traverseHoleData)
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
