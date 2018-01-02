/**
 * @file
 * @brief Function prototypes for the FieldData fields
 *
 * This contains the prototypes for the FieldData structure
 * including getters and setters for the important fields. Primary
 * importance are methods for setting and getting important information
 * used in further calculations from the data fields.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_LIBRARY_FIELDDATA_H
#define AMO_LIBRARY_FIELDDATA_H

/**
 * Field Data class
 * Contains all of the data that can be measured from a pump.
 */
class FieldData {
public:

    /// Classifications of load estimation methods
    enum class LoadEstimationMethod {
        POWER,
        CURRENT
    };

    /**
     * Constructor
     * @param flowRate double, rate of flow. Units are gpm
     * @param head double, pump head measured in feet
     * @param loadEstimationMethod LoadEstimationMethod, classification of load estimation method
     * @param motorPower double, power output of the pump's motor in hp.
     * @param motorAmps double, current measured from the pump's motor in amps
     * @param voltage double, the measured bus voltage in volts
     */

    FieldData(
        const double flowRate,
        const double head,
        const LoadEstimationMethod loadEstimationMethod,
        const double motorPower,
        const double motorAmps,
        const double voltage
    ) :
        loadEstimationMethod(loadEstimationMethod),
        flowRate(flowRate),
        head(head),
        motorPower(motorPower),
        motorAmps(motorAmps),
        voltage(voltage)
    {}

    FieldData() = default;

    /**
     * Gets the classification of the load estimation method
     * @return LoadEstimationMethod, classification of the load estimation method
     */
    LoadEstimationMethod getLoadEstimationMethod() const {
        return loadEstimationMethod;
    }

    /**
     * Sets the classification of the load estimation method
     * @param loadEstimationMethod LoadEstimationMethod, classification of the load estimation method
     */
    void setLoadEstimationMethod(const LoadEstimationMethod loadEstimationMethod) {
        this->loadEstimationMethod = loadEstimationMethod;
    }

    /**
     * Gets the rate of flow
     * @return double, rate of flow in gpm
     */
    double getFlowRate() const {
        return flowRate;
    }

    /**
     * Sets the rate of flow
     * @param flowRate double, rate of flow in gpm
     */
    void setFlowRate(const double flowRate) {
        this->flowRate = flowRate;
    }

    /**
     * Gets the pump head
     * @return double, pump head in ft
     */
    double getHead() const {
        return head;
    }

    /**
     * Sets the pump head
     * @param head double, pump head in ft
     */
    void setHead(const double head) {
        this->head = head;
    }

    /**
     * Gets the power output of the pump's motor
     * @return double, pump motor's output power in hp
     */
    double getMotorPower() const {
        return motorPower;
    }

    /**
     * Sets the power output of the pump's motor
     * @param motorPower double, pump motor's output power in hp
     */
    void setMotorPower(const double motorPower) {
        this->motorPower = motorPower;
    }

    /**
     * Gets the current measured from the pump's motor
     * @return double, current measured from pump's motor in amps
     */
    double getMotorAmps() const {
        return motorAmps;
    }

    /**
     * Sets the current measured from the pump's motor
     * @param motorAmps double, current measured from pump's motor in amps
     */
    void setMotorAmps(const double motorAmps) {
        this->motorAmps = motorAmps;
    }

    /**
     * Gets the measured bus voltage
     * @return double, measured bus voltage in volts
     */
    double getVoltage() const {
        return voltage;
    }

    /**
     * Sets the measured bus voltage
     * @param voltage double, measured bus voltage in volts
     */
    void setVoltage(const double voltage) {
        this->voltage = voltage;
    }

private:
    FieldData::LoadEstimationMethod loadEstimationMethod;
    double flowRate, head, motorPower, motorAmps, voltage;
};


#endif //AMO_LIBRARY_FIELDDATA_H
