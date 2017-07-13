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
     * @return nothing
     */

    FieldData(
        double flowRate,
        double head,
        LoadEstimationMethod loadEstimationMethod,
        double motorPower,
        double motorAmps,
        double voltage
    ) :
        loadEstimationMethod_(loadEstimationMethod),
        flowRate_(flowRate),
        head_(head),
        motorPower_(motorPower),
        motorAmps_(motorAmps),
        voltage_(voltage)
    {}

    FieldData() = default;

    /**
     * Gets the classification of the load estimation method
     *
     * @return LoadEstimationMethod, classification of the load estimation method
     */
    LoadEstimationMethod getLoadEstimationMethod() const {
        return loadEstimationMethod_;
    }

    /**
     * Sets the classification of the load estimation method
     *
     * @param loadEstimationMethod LoadEstimationMethod, classification of the load estimation method
     *
     * @return nothing
     */
    void setLoadEstimationMethod(LoadEstimationMethod loadEstimationMethod) {
        loadEstimationMethod_ = loadEstimationMethod;
    }

    /**
     * Gets the rate of flow
     *
     * @return double, rate of flow in gpm
     */
    double getFlowRate() const {
        return flowRate_;
    }

    /**
     * Sets the rate of flow
     *
     * @param flowRate double, rate of flow in gpm
     *
     * @return nothing
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    /**
     * Gets the pump head
     *
     * @return double, pump head in ft
     */
    double getHead() const {
        return head_;
    }

    /**
     * Sets the pump head
     *
     * @param head double, pump head in ft
     *
     * @return nothing
     */
    void setHead(double head) {
        head_ = head;
    }

    /**
     * Gets the power output of the pump's motor
     *
     * @return double, pump motor's output power in hp
     */
    double getMotorPower() const {
        return motorPower_;
    }

    /**
     * Sets the power output of the pump's motor
     *
     * @param motorPower double, pump motor's output power in hp
     *
     * @return nothing
     */
    void setMotorPower(double motorPower) {
        motorPower_ = motorPower;
    }

    /**
     * Gets the current measured from the pump's motor
     *
     * @return double, current measured from pump's motor in amps
     */
    double getMotorAmps() const {
        return motorAmps_;
    }

    /**
     * Sets the current measured from the pump's motor
     *
     * @param motorAmps double, current measured from pump's motor in amps
     *
     * @return nothing
     */
    void setMotorAmps(double motorAmps) {
        motorAmps_ = motorAmps;
    }

    /**
     * Gets the measured bus voltage
     *
     * @return double, measured bus voltage in volts
     */
    double getVoltage() const {
        return voltage_;
    }

    /**
     * Sets the measured bus voltage
     *
     * @param voltage double, measured bus voltage in volts
     *
     * @return nothing
     */
    void setVoltage(double voltage) {
        voltage_ = voltage;
    }

private:
// Input values
    FieldData::LoadEstimationMethod loadEstimationMethod_;
    double flowRate_;
    double head_;
    double motorPower_;
    double motorAmps_;
    double voltage_;
};


#endif //AMO_LIBRARY_FIELDDATA_H
