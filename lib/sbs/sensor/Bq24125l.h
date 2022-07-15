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
    bool enableCharge();
    bool enableBoostMode();
    bool disableCharge();
    bool disableBoostMode();

    // Input source control register
    bool enableBuck(void);
    bool disableBuck(void);
    bool setInputCurrentLimit(float current);
    float getInputCurrentLimit(void);
    bool setInputVoltageLimit(float voltage);
    float getInputVoltageLimit(void);

    // Power ON configuration register
    bool resetWatchdog(void);
    bool setMinimumSystemVoltage(float voltage);
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
    [[nodiscard]] float getChargeCurrent()const;

    // PreCharge/Termination Current Control Register
    void setPreChargeCurrent(float current);
    [[nodiscard]] float getPreChargeCurrent()const;
    void setTermChargeCurrent(float current);
    [[nodiscard]] float getTermChargeCurrent()const;

    // Charge Voltage Control Register
    bool setChargeVoltage(float voltage);
    float getChargeVoltage();

    // Charge Timer Control Register
    void disableWatchdog();

    // Misc Operation Control Register
    bool enableDPDM(void);
    bool disableDPDM(void);
    bool enableBATFET(void);
    bool disableBATFET(void);
    bool enableChargeFaultINT();
    bool disableChargeFaultINT();
    bool enableBatFaultINT();
    bool disableBatFaultINT();

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
    bool isWatchdogExpired();
    int getChargeFault();
    /**
     * @brief If battery over-voltage fault occurs
     * @return True if battery over-voltage
     */
    [[nodiscard]] bool isBatteryInOverVoltage() const;
    int hasBatteryTemperatureFault();

private:
    enum Registers {
        INPUT_SOURCE              = 0x00,
        POWERON_CONFIG            = 0x01,
        CHARGE_CURRENT_CONTROL    = 0x02,
        PRECHARGE_CURRENT_CONTROL = 0x03,
        CHARGE_VOLTAGE_CONTROL    = 0x04,
        CHARGE_TIMER_CONTROL      = 0x05,
        THERMAL_REG_CONTROL       = 0x06,
        MISC_CONTROL              = 0x07,
        SYSTEM_STATUS             = 0x08,
        FAULT                     = 0x09,
        PMIC_VERSION              = 0x0A,
    };
    // Misc Operation Control Register
    bool setWatchdog(uint8_t time);

    // Thermal Regulation Control Register
    bool setThermalRegulationTemperature(int degree);
    int getThermalRegulationTemperature();

    // Power ON configuration register
    bool enableCharging(void);
    bool disableCharging(void);
    bool enableOTG(void);
    bool disableOTG(void);

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
