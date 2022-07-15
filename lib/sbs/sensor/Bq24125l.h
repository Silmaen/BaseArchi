/**
 * @file Bq24125l.h
 * @author Silmaen
 * @date 15/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "io/i2c/Device.h"

namespace sbs::sensor {

/**
 * @brief Class Bq24125l
 *
 * The BQ24125L is a battery charge controler
 */
class Bq24125l : public io::i2c::Device {
public:
    Bq24125l(const Bq24125l&)            = delete;
    Bq24125l(Bq24125l&&)                 = delete;
    Bq24125l& operator=(const Bq24125l&) = delete;
    Bq24125l& operator=(Bq24125l&&)      = delete;
    /**
     * @brief Default constructor.
     */
    Bq24125l();
    /**
     * @brief Destructor.
     */
    ~Bq24125l() override = default;

    /**
     * @brief Initialize the device
     */
    void init() override;

    /**
     * @brief Get device's name
     * @return The device's name.
     */
    [[nodiscard]] string getName() const override { return "BQ24125L"; }

    /**
     * @brief Check the presence of the device.
     * @return Return true if the device is found.
     */
    [[nodiscard]] bool checkPresence() const override;

    /**
     * @brief Power mode
     */
    enum struct ChargingMode {
        Disable,     ///< Charging disconnected
        Normal,      ///< Charge at normale rate
        Boost,       ///< Charge in boost rate
        Disconnected,///< Disconnect battery
    };
    void setChargingMode(const ChargingMode& mode);
    void enableCharge();
    void enableBoostMode();
    void disableCharge();
    void disableBoostMode();

    // Input source control register
    void enableBuck();
    void disableBuck();
    void setInputCurrentLimit(float current);
    float getInputCurrentLimit();
    void setInputVoltageLimit(float voltage);
    float getInputVoltageLimit();

    // Power ON configuration register
    void resetWatchdog();
    void setMinimumSystemVoltage(float voltage);
    float getMinimumSystemVoltage();
    /**
     * @brief Set the charge current.
     * @param current The charge current.
     */
    void setChargeCurrent(float current);
    /**
     * @brief Get the charge current.
     * @return The charge current
     */
    [[nodiscard]] float getChargeCurrent() const;

    // PreCharge/Termination Current Control Register
    void setPreChargeCurrent(float current);
    [[nodiscard]] float getPreChargeCurrent() const;
    void setTermChargeCurrent(float current);
    [[nodiscard]] float getTermChargeCurrent() const;

    // Charge Voltage Control Register
    void setChargeVoltage(float voltage);
    float getChargeVoltage();

    // Charge Timer Control Register
    void disableWatchdog();

    // Misc Operation Control Register
    void enableDPDM();
    void disableDPDM();
    void enableBATFET();
    void disableBATFET();
    void enableChargeFaultINT();
    void disableChargeFaultINT();
    void enableBatFaultINT();
    void disableBatFaultINT();

    // System Status Register
    int USBmode();
    int chargeStatus();
    /**
     * @brief Check for a connected battery
     * @return True if a battery detected
     */
    [[nodiscard]] bool isBattConnected() const;
    bool isPowerGood(void);
    bool isHot(void);
    bool canRunOnBattery();

    // Fault Register
    enum struct ThermalFault {
        Ok,
        LowerThresholdTemperature,
        UpperThresholdTemperature,
        Unknown
    };
    enum struct ChargeFault {
        Ok,
        InputOverVoltage,
        ThermalShutDown,
        ChargeSafetyTimeExpired,
        Unknown
    };
    [[nodiscard]] ThermalFault getThermalFault() const;
    [[nodiscard]] ChargeFault getChargeFault() const;

    [[nodiscard]] bool isWatchdogExpired()const;
    /**
     * @brief If battery over-voltage fault occurs
     * @return True if battery over-voltage
     */
    [[nodiscard]] bool isBatteryInOverVoltage() const;

private:
    enum Registers {
        INPUT_SOURCE = 0x00,
        /**
         * @brief Power On register
         *  bits 7   6   5   4   3   2   1   0
         *              Charge
         *
         *  Charge, 00: disable, 01: charge, 10: boost
         */
        POWERON_CONFIG = 0x01,
        /**
         * @brief Control charge current
         *  bits 7   6   5   4   3   2   1   0
         *        -- charge current --
         */
        CHARGE_CURRENT_CONTROL = 0x02,
        /**
         * @brief Control charge current
         *  bits 7   6   5   4   3   2   1   0
         *       -- chg cur --  - th chg cur -
         */
        PRECHARGE_CURRENT_CONTROL = 0x03,
        CHARGE_VOLTAGE_CONTROL    = 0x04,
        /**
         * @brief Charge Time control
         *  bits 7   6   5   4   3   2   1   0
         *      chg
         *
         * chg, 0: disable charge terminason pin, 1: enable
         */
        CHARGE_TIMER_CONTROL = 0x05,
        THERMAL_REG_CONTROL  = 0x06,
        /**
         * @brief Miscelaneous configuration
         *  bits 7   6   5   4   3   2   1   0
         *                             b_fault_int
         *
         * b_fault_int: 11: enable Enable Battery Fault interrupt & Charge Fault Interrupt, 00:disable all:
         */
        MISC_CONTROL = 0x07,
        /**
         * @brief System status
         *  bits 7   6   5   4   3   2   1   0
         *                      BAT
         *
         * BAT: Battery is present
         */
        SYSTEM_STATUS = 0x08,
        /**
         * @brief Fault register
         *  bits 7   6   5   4   3   2   1   0
         *       WE     ChgFlt  IOV ThermalFault
         *
         * WE          : Watchdog expired
         * ChgFlt      : Charge fault 01 input over voltage, 10: Thermal shutdown, 11: Charge safety time expired
         * IOV         : Battery input over voltage
         * ThermalFault: 101 lowerthreshold temperature, 110 upper threshold temperature
         */
        FAULT = 0x09,
        /**
         * @brief Version number
         */
        PMIC_VERSION = 0x0A,
    };
    // Misc Operation Control Register
    void setWatchdog(uint8_t time);

    // Thermal Regulation Control Register
    void setThermalRegulationTemperature(int degree);
    int getThermalRegulationTemperature();

    // Power ON configuration register
    void enableCharging();
    void disableCharging();
    void enableOTG();
    void disableOTG();

    /**
     * @brief Read the version register
     * @return The version register
     */
    [[nodiscard]] uint8_t getVersion() const;
    [[nodiscard]] uint8_t readOpControlRegister() const;
    [[nodiscard]] uint8_t readChargeTermRegister() const;
    [[nodiscard]] uint8_t readPowerONRegister() const;
    [[nodiscard]] uint8_t readInputSourceRegister() const;
    [[nodiscard]] uint8_t readSystemStatusRegister() const;
    [[nodiscard]] uint8_t readFaultRegister() const;
};

}// namespace sbs::sensor
