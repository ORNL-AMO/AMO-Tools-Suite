#ifndef AMO_TOOLS_SUITE_FAN_H
#define AMO_TOOLS_SUITE_FAN_H

#include <string>
#include <unordered_map>
#include <cmath>

// TODO consider deleting class member variables rectLength, width, diameter etc if they are used ONLY in area calculations
// no need to have them sitting around if everything we need comes from the constructor input.
class Planar {
public:
	Planar(const double rectLength, const double rectWidth, const unsigned noInletBoxes = 0) :
			rectLength(rectLength), rectWidth(rectWidth), noInletBoxes(noInletBoxes)
	{
		area = (rectLength * rectWidth) / 144.0;
		if (noInletBoxes > 0) area *= noInletBoxes;
	}

	// TODO assuming inlet boxes are not possible to have if circular shape
	explicit Planar(const double circularDuctDiameter) :
			circularDuctDiameter(circularDuctDiameter), shape(Shape::CIRCULAR)
	{
		area = ((3.14159265358979 / 4) * (circularDuctDiameter * circularDuctDiameter)) / 144.0;
	}

private:
	enum class Shape {
		RECTANGULAR,
		CIRCULAR
	};


	const double rectLength = 0, rectWidth = 0, circularDuctDiameter = 0;
	double area = 0;
	const unsigned noInletBoxes = 0;
	const Shape shape = Shape::RECTANGULAR;
};


class FanRatedInfo {
public:
	enum class DriveType {
		DIRECT,
		BELT
	};

	// this currently does not take the field SystemDamperPosition, as it is used "only for reference purposes" as per
	// page 8 in the algorithm document
	FanRatedInfo(double const fanDamperPosition, double const fanSpeed, double const motorSpeed, double const nc,
	             double const pc, double const pbc, DriveType const driveType) :
			fanDamperPosition(fanDamperPosition / 100.0), fanSpeed(fanSpeed), motorSpeed(motorSpeed),
			nc(nc), pc(pc), pbc(pbc), driveType(driveType)
	{};

private:
	double const fanDamperPosition, fanSpeed, motorSpeed, nc, pc, pbc;
	DriveType const driveType;

};


class Fan {
public:
	Fan(FanRatedInfo & fanRatedInfo, std::unordered_map<std::string, Planar> & planes) :
			fanRatedInfo(fanRatedInfo)
	{
		this->planes = std::move(planes);
	}

private:
	FanRatedInfo const fanRatedInfo;
	std::unordered_map<std::string, Planar> planes;
};

#endif //AMO_TOOLS_SUITE_FAN_H
