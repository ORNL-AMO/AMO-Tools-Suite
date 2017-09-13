#include "fsat/Planar.h"

Planar::Planar(const double circularDuctDiameter, const double tdx, const double pbx)
		: tdx(tdx), pbx(pbx), area(((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0)
{}

Planar::Planar(const double rectLength, const double rectWidth, const double tdx, const double pbx)
		: tdx(tdx), pbx(pbx), area((rectLength * rectWidth) / 144.0)
{}

Planar::Planar(const double rectLength, const double rectWidth, unsigned const noInletBoxes, const double tdx,
               const double pbx)
		: tdx(tdx), pbx(pbx), area((rectLength * rectWidth * noInletBoxes) / 144.0)
{}

FanInletFlange::FanInletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
		: Planar(circularDuctDiameter, tdx, pbx) {}

FanInletFlange::FanInletFlange(const double rectLength, const double rectWidth, const double tdx, const double pbx)
		: Planar(rectLength, rectWidth, tdx, pbx) {}

FanInletFlange::FanInletFlange(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                               const double tdx, const double pbx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx)
{}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double circularDuctDiameter, const double tdx, const double pbx)
		: Planar(circularDuctDiameter, tdx, pbx) {}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double rectLength, const double rectWidth, const double tdx,
                                               const double pbx)
		: Planar(rectLength, rectWidth, tdx, pbx) {}

FanOrEvaseOutletFlange::FanOrEvaseOutletFlange(const double rectLength, const double rectWidth,
                                               const unsigned noInletBoxes, const double tdx, const double pbx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx)
{}

FlowTraverse::FlowTraverse(const double circularDuctDiameter, const double tdx, const double pbx,
                           const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > & traverseHoleData)
		: Planar(circularDuctDiameter, tdx, pbx),
		  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData), psx(psx)
{}

FlowTraverse::FlowTraverse(const double rectLength, const double rectWidth, const double tdx,
                           const double pbx, const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
                           std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, tdx, pbx),
		  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData), psx(psx)
{}

FlowTraverse::FlowTraverse(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                           const double tdx, const double pbx, const double psx, const TubeType tubeType,
                           const double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx),
		  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData), psx(psx)
{}

AddlTravPlane::AddlTravPlane(const double circularDuctDiameter, const double tdx, const double pbx,
                             const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > & traverseHoleData)
		: Planar(circularDuctDiameter, tdx, pbx),
		  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData), psx(psx)
{}

AddlTravPlane::AddlTravPlane(const double rectLength, const double rectWidth, const double tdx,
                             const double pbx, const double psx, const TubeType tubeType, const double pitotTubeCoefficient,
                             std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, tdx, pbx),
		  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData), psx(psx)
{}

AddlTravPlane::AddlTravPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                             const double tdx, const double pbx, const double psx, const TubeType tubeType,
                             const double pitotTubeCoefficient, std::vector< std::vector< double > > & traverseHoleData)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx),
		  VelocityPressureTraverseData(tubeType, pitotTubeCoefficient, traverseHoleData), psx(psx)
{}

InletMstPlane::InletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx, const double psx)
		: Planar(circularDuctDiameter, tdx, pbx), psx(psx) {}

InletMstPlane::InletMstPlane(const double rectLength, const double rectWidth, const double tdx, const double pbx,
                             const double psx)
		: Planar(rectLength, rectWidth, tdx, pbx), psx(psx) {}

InletMstPlane::InletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                             const double tdx, const double pbx, const double psx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx), psx(psx)
{}

OutletMstPlane::OutletMstPlane(const double circularDuctDiameter, const double tdx, const double pbx,
                               const double psx)
		: Planar(circularDuctDiameter, tdx, pbx), psx(psx) {}

OutletMstPlane::OutletMstPlane(const double rectLength, const double rectWidth, const double tdx,
                               const double pbx, const double psx)
		: Planar(rectLength, rectWidth, tdx, pbx), psx(psx) {}

OutletMstPlane::OutletMstPlane(const double rectLength, const double rectWidth, const unsigned noInletBoxes,
                               const double tdx, const double pbx, const double psx)
		: Planar(rectLength, rectWidth, noInletBoxes, tdx, pbx), psx(psx)
{}

VelocityPressureTraverseData::VelocityPressureTraverseData(const TubeType pitotTubeType, const double pitotTubeCoefficient,
                                                           std::vector< std::vector< double > > & traverseHoleData)
		: pitotTubeType(pitotTubeType), pitotTubeCoefficient(pitotTubeCoefficient),
		  traverseHoleData(std::move(traverseHoleData))
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

	size_t count = 0;
	for (auto & row : this->traverseHoleData) {
		for (auto & val : row) {
			if (val > (0.1 * maxPv3r)) count++;
		}
	}

	percent75Rule = count / static_cast<double>(this->traverseHoleData.size() * this->traverseHoleData[0].size());
}
