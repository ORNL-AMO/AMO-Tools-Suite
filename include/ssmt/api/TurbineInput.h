#ifndef AMO_TOOLS_SUITE_TURBINEINPUT_H
#define AMO_TOOLS_SUITE_TURBINEINPUT_H

#include <iostream>
#include <type_traits>

enum class CondensingTurbineOperation {
    POWER_GENERATION = 1,
    STEAM_FLOW = 0
};

enum class PressureTurbineOperation {
    BALANCE_HEADER = 2,
    FLOW_RANGE = 4,
    POWER_GENERATION = 1,
    POWER_RANGE = 3,
    STEAM_FLOW = 0
};

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

class CondensingTurbine {
public:
    CondensingTurbine(double isentropicEfficiency, double generationEfficiency, double condenserPressure,
                      CondensingTurbineOperation operationType, double operationValue, bool useTurbine);

    friend std::ostream &operator<<(std::ostream &stream, const CondensingTurbine &oi);

    double getIsentropicEfficiency() const;

    double getGenerationEfficiency() const;

    double getCondenserPressure() const;

    CondensingTurbineOperation getOperationType() const;

    double getOperationValue() const;

    bool isUseTurbine() const;

private:
    double isentropicEfficiency;
    double generationEfficiency;
    double condenserPressure;
    CondensingTurbineOperation operationType;
    double operationValue;
    bool useTurbine;
};

class PressureTurbine {
public:
    PressureTurbine(double isentropicEfficiency, double generationEfficiency, PressureTurbineOperation operationType,
                    double operationValue1, double operationValue2, bool useTurbine);

    friend std::ostream &operator<<(std::ostream &stream, const PressureTurbine &pt);

    double getIsentropicEfficiency() const;

    double getGenerationEfficiency() const;

    PressureTurbineOperation getOperationType() const;

    double getOperationValue1() const;

    double getOperationValue2() const;

    bool isUseTurbine() const;

private:
    double isentropicEfficiency;
    double generationEfficiency;
    PressureTurbineOperation operationType;
    double operationValue1;
    double operationValue2;
    bool useTurbine;
};

class TurbineInput {
public:
    TurbineInput(const CondensingTurbine &condensingTurbine, const PressureTurbine &highToLowTurbine,
                 const PressureTurbine &highToMediumTurbine, const PressureTurbine &mediumToLowTurbine);

    CondensingTurbine getCondensingTurbine() const;

    PressureTurbine getHighToLowTurbine() const;

    PressureTurbine getHighToMediumTurbine() const;

    PressureTurbine getMediumToLowTurbine() const;

private:
    CondensingTurbine condensingTurbine;
    PressureTurbine highToLowTurbine;
    PressureTurbine highToMediumTurbine;
    PressureTurbine mediumToLowTurbine;
};

#endif //AMO_TOOLS_SUITE_TURBINEINPUT_H
