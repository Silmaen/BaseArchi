/**
 * @file Bq24195l.h
 * @author Silmaen
 * @date 15/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "io/i2c/Device.h"
#include "math/base.h"

namespace sbs::sensor {

/**
 * @brief Class Bq24195l
 *
 * The BQ24125L is a battery charge controler
 */
class Bq24195l : public io::i2c::Device {
public:
    Bq24195l(const Bq24195l&)            = delete;
    Bq24195l(Bq24195l&&)                 = delete;
    Bq24195l& operator=(const Bq24195l&) = delete;
    Bq24195l& operator=(Bq24195l&&)      = delete;
    /**
     * @brief Default constructor.
     */
    Bq24195l();
    /**
     * @brief Destructor.
     */
    ~Bq24195l() override = default;

    /**
     * @brief Initialize the device
     */
    void init() override;

    /**
     * @brief Get device's name
     * @return The device's name.
     */
    [[nodiscard]] string getName() const override { return "BQ24195L"; }

    /**
     * @brief Check the presence of the device.
     * @return Return true if the device is found.
     */
    [[nodiscard]] bool checkPresence() const override;

    /**
     * @brief Device settings
     */
    struct Settings {
        // -------------- REG0 -----------------------
        /**
         * @brief Input current limit
         */
        enum struct InputCurrentLimit {
            I0100 = 0b000,///< 100mA default
            I0150 = 0b001,///< 150mA
            I0500 = 0b010,///< 500mA
            I0900 = 0b011,///< 900mA
            I1200 = 0b100,///< 1.2A
            I1500 = 0b101,///< 1.5A
            I2000 = 0b110,///< 2A
            I3000 = 0b111,///< 3A
        };
        /// Input current limit
        InputCurrentLimit inputCurLim = InputCurrentLimit::I0100;
        /**
         * @brief Define input voltage
         * @param volts Input voltage
         */
        void setInputVoltage(double volts) {
            vindpm = static_cast<uint8_t>((math::clamp(volts, 3.88, 5.08) - 3.88) / 0.080);
        }
        /**
         * @brief Get the input voltage
         * @return Input voltage
         */
        [[nodiscard]] double getInoutVoltage() const {
            return 3.504 + vindpm * 0.016;
        }
        /**
         * @brief Convert to Input Source register
         * @return The register
         */
        [[nodiscard]] uint8_t toInputSourceReg() const {
            return static_cast<uint8_t>(vindpm) << 3U | static_cast<uint8_t>(inputCurLim);
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromInputSourceReg(uint8_t input) {
            vindpm      = (input & 0b01111000) >> 3;
            inputCurLim = static_cast<InputCurrentLimit>(input & 0b0111);
        }

        // -------------- REG1 -----------------------
        /**
         * @brief Main operation mode
         */
        enum struct ChargerConfiguration {
            disable = 0x00,///< No charge
            normal  = 0x01,///< Charge from USB to Battery
            otg     = 0x10,///< Allow power from Battery to USB
        };
        /// Main operation mode
        ChargerConfiguration chgConfig = ChargerConfiguration::normal;
        /**
         * @brief Define the minimum system voltage
         * @param volt The minimum system voltage
         */
        void setMinimumSystemVoltage(double volt) {
            sysMin = static_cast<uint8_t>((math::clamp(volt, 3.0, 3.7) - 7.0) / 0.1);
        }
        /**
         * @brief Get the minimum system voltage
         * @return The minimum system voltage
         */
        [[nodiscard]] double getMinimumSystemVoltage() const {
            return 3.0 + sysMin * 0.1;
        }

        /**
         * @brief Convert to Input Source register
         * @return The register
         */
        [[nodiscard]] uint8_t toPowerOnReg() const {
            return static_cast<uint8_t>(chgConfig) << 4U | static_cast<uint8_t>(sysMin) << 1 | 1;
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromPowerOnReg(uint8_t input) {
            chgConfig = static_cast<ChargerConfiguration>((input & 0b00110000) >> 4);
            sysMin    = (input & 0b00001110) >> 1;
        }

        // -------------- REG2 -----------------------
        /**
         * @brief Define the fast charge phase's current
         * @param current The fast charge current
         */
        void setFastChargeCurrent(double current) {
            ichg = static_cast<uint8_t>((math::clamp(current, 0.512, 2.496) - 0.512) / 0.064);
        }
        /**
         * @brief Get the fast charge current
         * @return The fast charge current
         */
        [[nodiscard]] double getFastChargeCurrent() const {
            return 0.512 + ichg * 0.064;
        }
        /// If we should reduce the currents
        bool force20pct = false;
        /**
         * @brief Convert to Current Control register
         * @return The register
         */
        [[nodiscard]] uint8_t toCurrentControlReg() const {
            return static_cast<uint8_t>(ichg) << 2U | static_cast<uint8_t>(force20pct);
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromCurrentControlReg(uint8_t input) {
            ichg       = (input & 0b11111100) >> 2;
            force20pct = (input & 0x1) == 1;
        }

        // -------------- REG3 -----------------------
        /**
         * @brief Define the pre-charge phase current
         * @param current Teh pre-charge current
         */
        void setPreChargeCurrent(double current) {
            iprechg = static_cast<uint8_t>((math::clamp(current, 0.128, 2.048) - 0.128) / 0.128);
        }
        /**
         * @brief Get the pre-charge current
         * @return The pres-charge current
         */
        [[nodiscard]] double getPreChargeCurrent() const {
            return 0.128 + iprechg * 0.128;
        }
        /**
         * @brief Define the Terminaison phase current
         * @param current Teh terminaison current
         */
        void setTerminaisonChargeCurrent(double current) {
            iterm = static_cast<uint8_t>((math::clamp(current, 0.128, 2.048) - 0.128) / 0.128);
        }
        /**
         * @brief Get the terminaison current
         * @return The terminaison current
         */
        [[nodiscard]] double getTerminaisonChargeCurrent() const {
            return 0.128 + iterm * 0.128;
        }
        /**
         * @brief Convert to precharge Current Control register
         * @return The register
         */
        [[nodiscard]] uint8_t toPreChargeCurrentControlReg() const {
            return static_cast<uint8_t>(iprechg) << 4U | static_cast<uint8_t>(iterm);
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromPreChargeCurrentControlReg(uint8_t input) {
            iprechg = (input & 0xF0) >> 4;
            iterm   = input & 0x0F;
        }

        // -------------- REG4 -----------------------
        /**
         * @brief Define the charge voltage
         * @param current Teh charge voltage
         */
        void setChargeVoltage(double current) {
            vreg = static_cast<uint8_t>((math::clamp(current, 3.504, 4.4) - 3.504) / 0.016);
        }
        /**
         * @brief Get the charge voltage
         * @return The charge voltage
         */
        [[nodiscard]] double getChargeVoltage() const {
            return 3.504 + vreg * 0.016;
        }
        /**
         * @brief Battery precharge voltage
         */
        enum struct BattPreChargeToFastCharge {
            V28 = 0x00,///< 2.8V (default)
            V30 = 0x01 ///< 3.0V
        };
        /// Battery precharge voltage
        BattPreChargeToFastCharge battPreChargeToFastCharge = BattPreChargeToFastCharge::V30;
        /**
         * @brief Battery recharge threshold
         */
        enum struct BattRechargeThrs {
            V0100 = 0x00,///< 100mV (default)
            V0300 = 0x01 ///< 300mV
        };
        ///  Battery recharge threshold
        BattRechargeThrs battRechargeThrs = BattRechargeThrs::V0100;

        /**
         * @brief Convert to Current Control register
         * @return The register
         */
        [[nodiscard]] uint8_t toChargeVoltageReg() const {
            return vreg << 2U | static_cast<uint8_t>(battPreChargeToFastCharge) << 1 | static_cast<uint8_t>(battRechargeThrs);
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromChargeVoltageReg(uint8_t input) {
            vreg                      = (input & 0b11111100) >> 2;
            battPreChargeToFastCharge = static_cast<BattPreChargeToFastCharge>((input & 0b10) >> 1);
            battRechargeThrs          = static_cast<BattRechargeThrs>((input & 0b01));
        }
        // -------------- REG5 -----------------------
        /**
         * @brief Charge terminaison status
         */
        enum struct ChargingTerminaison {
            disable = 0x00,///< enable
            enable  = 0x01 ///< disable
        };
        /// Charge terminaison status
        ChargingTerminaison chargingTerminaison = ChargingTerminaison::enable;
        /**
         * @brief Terminaison indicator status
         */
        enum struct TerminaisonIndicator {
            match    = 0x00,///< mathc ITHERM
            external = 0x01 ///< STAT pin High
        };
        /// Terminaison indicator status
        TerminaisonIndicator terminaisonIndicator = TerminaisonIndicator::match;
        /**
         * @brief Watchdog timer
         */
        enum struct WatchDog {
            disable = 0x00,///< disable timer
            T40     = 0x01,///< 40s
            T80     = 0x02,///< 80s
            T160    = 0x03 ///< 160s
        };
        /// Watchdog timer
        WatchDog watchDog = WatchDog::T40;
        /**
         * @brief Safety Timer
         */
        enum struct SafetyTimer {
            disable = 0x00,///< enable
            enable  = 0x01 ///< disable
        } ;
        /// Safety Timer
        SafetyTimer safetyTimer = SafetyTimer::enable;
        /**
         * @brief Charge timer
         */
        enum struct ChargeTimer {
            T5  = 0x00,///< 5h
            T8  = 0x01,///< 8h
            T12 = 0x02,///< 12h
            T20 = 0x03 ///< 20
        };
        /// Charge timer
        ChargeTimer chargeTimer = ChargeTimer::T8;

        /**
         * @brief Convert to Current Control register
         * @return The register
         */
        [[nodiscard]] uint8_t toChargeTimerReg() const {
            return static_cast<uint8_t>(chargingTerminaison) << 7U | static_cast<uint8_t>(terminaisonIndicator) << 6 |
                   static_cast<uint8_t>(watchDog) << 4 | static_cast<uint8_t>(safetyTimer) << 3 | static_cast<uint8_t>(chargeTimer) << 1;
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromChargeTimerReg(uint8_t input) {
            chargingTerminaison  = static_cast<ChargingTerminaison>((input & 0b10000000) >> 7);
            terminaisonIndicator = static_cast<TerminaisonIndicator>((input & 0b01000000) >> 6);
            watchDog             = static_cast<WatchDog>((input & 0b00110000) >> 4);
            safetyTimer          = static_cast<SafetyTimer>((input & 0b00001000) >> 3);
            chargeTimer          = static_cast<ChargeTimer>((input & 0b00000110) >> 1);
        }
        // -------------- REG6 -----------------------
        /**
         * @brief Thermal regulation threshold
         */
        enum struct ThermalRegulationThreshold {
            T60D  = 0x00,///< 60°C
            T80D  = 0x01,///< 80°C
            T100D = 0x02,///< 100°C
            T120D = 0x03 ///< 120°C (default)
        };
        /// Thermal regulation threshold
        ThermalRegulationThreshold thermalRegulationThreshold = ThermalRegulationThreshold::T120D;
        /**
         * @brief Convert to Thermal regulation Control register
         * @return The register
         */
        [[nodiscard]] uint8_t toThermalReg() const {
            return static_cast<uint8_t>(thermalRegulationThreshold);
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromThermalReg(uint8_t input) {
            thermalRegulationThreshold = static_cast<ThermalRegulationThreshold>((input & 0b0000011));
        }
        // -------------- REG7 -----------------------
        /**
         * @brief D+/D- detection
         */
        enum struct DPDMDetection {
            No     = 0b0,///< No D+/D- detection (default)
            Forced = 0b1,///< Force D+/D- detection

        };
        /// D+/D- detection
        DPDMDetection dpdmDetection = DPDMDetection::No;
        /**
         * @brief Safety timer
         */
        enum struct SafetyTimerSetting {
            Normal = 0b0,///<< Safty timer not slowed
            Slow   = 0b1 ///< Safety timer slowed by 2X during input DPM or thermal regulation (default)
        };
        /// Safety timer
        SafetyTimerSetting safetyTimerSetting = SafetyTimerSetting::Slow;
        /// To disconnect the battery from system
        bool batFetDisable = false;
        /**
         * @brief Interrupt mode
         */
        enum struct InterruptMode {
            none            = 0b00,///< no interrupt
            BatFaultOnly    = 0b01,///< Interrupt only if Bat Fault
            ChargeFaultOnly = 0b10,///<< Interrupt only if charge fault
            Both            = 0b11 ///< all interrupt (default)
        };
        /// Interrupt mode
        InterruptMode interruptMode = InterruptMode::Both;
        /**
         * @brief Convert to Thermal regulation Control register
         * @return The register
         */
        [[nodiscard]] uint8_t toMiscOpReg() const {
            return static_cast<uint8_t>(dpdmDetection) << 7 | static_cast<uint8_t>(safetyTimerSetting) << 6 |
                   static_cast<uint8_t>(batFetDisable) << 5 | 0x8 | static_cast<uint8_t>(interruptMode);
        }
        /**
         * @brief Define parameter according to register
         * @param input The register
         */
        void fromMiscOpReg(uint8_t input) {
            dpdmDetection = static_cast<DPDMDetection>((input&0b10000000)>>7);
            safetyTimerSetting = static_cast<SafetyTimerSetting>((input&0b01000000)>>6);
            batFetDisable = (input&0b00100000) != 0;
            interruptMode = static_cast<InterruptMode>((input&0b00000011));
        }
    private:
        /// Voltage input
        uint8_t vindpm  = 0b00000110;
        /// System minimum voltage
        uint8_t sysMin  = 0b00000101;
        /// Charging current
        uint8_t ichg    = 0b00011000;
        /// Pre-charging current
        uint8_t iprechg = 0b00000001;
        /// Terminaison current
        uint8_t iterm   = 0b00000001;
        /// Regulation voltage
        uint8_t vreg    = 0b00101100;
    };

    /**
     * @brief Power mode
     */
    enum struct ChargingMode {
        Disable,     ///< Charging disconnected
        Normal,      ///< Charge at normale rate
        OTG,         ///< Send power to USB
        Disconnected,///< Disconnect battery
    };
    /**
     * @brief Define the th charging mode
     * @param mode The new mode
     */
    void setChargingMode(const ChargingMode& mode);

    // System Status Register
    /**
     * @brief Status of the input
     */
    enum struct VBusStatus {
        unknown     = 0b00,///< unknown
        usb         = 0b01,///< Use usb power
        AdapterPort = 0b10,///< Use battery
        otg         = 0b11 ///< Power usb using battery
    };
    /**
     * @brief Get input status
     * @return  the Input status
     */
    [[nodiscard]] VBusStatus getVbusStatus() const;
    /**
     * @brief Charging status
     */
    enum struct ChargeStatus {
        NotCharging       = 0b00,/// not charging
        PreCharge         = 0b01,///< Pre-charge phase
        FastCharging      = 0b10,///< Fast charge phase
        ChargeTerminaison = 0b11 ///< Terminaison charge phase
    };
    /**
     * @brief Get the charging status
     * @return The charging status
     */
    [[nodiscard]] ChargeStatus getChargeStatus() const;
    /**
     * @brief Return if battery detected
     * @return True if a battery is detected
     */
    [[nodiscard]] bool isInDPM() const;
    /**
     * @brief Get if the supply power is in good shape
     * @return True if power is good
     */
    [[nodiscard]] bool isPowerGood() const;
    /**
     * @brief Check if device is in thermal regulation
     * @return True if in thermal regulation
     */
    [[nodiscard]] bool isInThermalRegulation() const;
    /**
     * @brief Get if the battery voltage bellow min system
     * @return True: battery is low voltage, and Vsys regulation is active
     */
    [[nodiscard]] bool isInVSYSRegulation() const;

    // Fault Register
    /**
     * @brief Thermal fault codes
     */
    enum struct ThermalFault {
        Ok,                       ///< Everything ok
        LowerThresholdTemperature,///< Too cold
        UpperThresholdTemperature,///< Too hot
        Unknown                   ///< Unknown status
    };
    /**
     * @brief Charge Fault codes
     */
    enum struct ChargeFault {
        Ok,                     ///< Everything ok
        InputOverVoltage,       ///< Inout over voltage
        ThermalShutDown,        /// Shutdown due to too high temperature
        ChargeSafetyTimeExpired///< Expiration of safety timer
    };
    /**
     * @brief Get the thermal fault status
     * @return The thermal fault Status
     */
    [[nodiscard]] ThermalFault getThermalFault() const;
    /**
     * @brief Get the charge fault status
     * @return The Charge fault status
     */
    [[nodiscard]] ChargeFault getChargeFault() const;
    /**
     * @brief Check if watchdog timer is expired
     * @return
     */
    [[nodiscard]] bool isWatchdogExpired() const;
    /**
     * @brief If battery over-voltage fault occurs
     * @return True if battery over-voltage
     */
    [[nodiscard]] bool isBatteryInOverVoltage() const;

    /**
     * @brief Access to settings
     * @return internal settings
     */
    Settings& getSettings() { return settings; }

    /**
     * @brief Read setting from device and update internal settings
     */
    void ReadSettings();
    /**
     * @brief Apply current setting to device
     */
    void ApplySettings();


    [[nodiscard]] uint8_t readSystemStatusRegister() const;
    [[nodiscard]] uint8_t readFaultRegister() const;
private:
    /// Setting, initialize as Constructor default
    Settings settings = Settings{};

    enum Registers {
        /**
         * @brief Inpout source control
         *  bits 7   6   5   4   3   2   1   0
         *    EnHiz --- VINDPM ---   - IINLM -
         *
         *  Enhiz : is set to 0 when charge timeout
         *  VINDPM : Input voltage limit =  3.88V + 80mv * VINDPM   (default 4.36V  0110 )
         *  IINLM : Input current limit (default 100mA OTG pin=0 or 500mA OTG Pin 1)
         *            000 100mA   001 150mA
         *            010 500mA   011 900mA
         *            100 1.2A    101 1.5A
         *            110 2A      111 3A
         */
        INPUT_SOURCE = 0x00,
        /**
         * @brief Power On register
         *  bits 7   6   5   4   3   2   1   0
         *      RST WTR Charge  - SYS_MIN -
         *
         *  RST register reset: 1 reset to default
         *  WTR Watchdog Timer reset: 0 normal, 1 reset
         *  Charge, 00: disable, 01: charge, 10/11: OTG
         *  SYS_MIN, Minimum system voltage limit = 3.0V + 0.1V * SYS_MIN (default 101: 3.5V)
         */
        POWERON_CONFIG = 0x01,
        /**
         * @brief Control charge current
         *  bits 7   6   5   4   3   2   1   0
         *       -------- ICHG --------  0  20PCT
         *
         *  ICHG: Fast charge current limit = 512mA + 64mA * ICHG (max 2496mA if version L else 4544mA)
         *  20PCT if active, ICHG reduce by 20% & IPRECH by 50%
         */
        CHARGE_CURRENT_CONTROL = 0x02,
        /**
         * @brief Control charge current
         *  bits 7   6   5   4   3   2   1   0
         *       --- IPRECH ---  --- ITERM ---
         *
         *  IPRECH: Precharge current limit = 128mA + 128mA * IPRECH
         *  ITERM:  Terminaison current limit = 128mA + 128mA * ITERM
         */
        PRECHARGE_CURRENT_CONTROL = 0x03,
        /**
         * @brief Charge voltage control
         *  bits 7   6   5   4   3   2   1   0
         *       -------- VREG -------- BTL VRECHG
         *
         *  VREG Charge voltage limit = 3.504V + 16mv * VREG (max 4.4V, default 4.208V)
         *  BTL Battery precharge to charge threshold 0: 2.8V, 1: 3.0V (default 3V)
         *  VRECHG Battery Recharge Threshold 0 – 100 mV, 1 – 300 mV (default 100mV)
         */
        CHARGE_VOLTAGE_CONTROL = 0x04,
        /**
         * @brief Charge Time control
         *  bits 7   6   5   4   3   2   1   0
         *      chg TIT WATHDOG ENT CHGTIME  0
         *
         * chg, charge terminaison 1: enable
         * TIT, Termination Indicator Threshold 0 – Match ITERM, Default Match ITERM (0) 1 – STAT pin high before actual termination when charge current below 800 mA
         * WATHDOG, I2C Watchdog Timer Setting 00 – Disable timer, 01 – 40 s, 10 – 80 s, 11 – 160 s
         * ENT, Charging Safety Timer Enable 0 – Disable, 1 – Enable
         * CHGTIME, Fast Charge Timer Setting 00 – 5 hrs, 01 – 8 hrs, 10 – 12hrs, 11 – 20 hrs
         */
        CHARGE_TIMER_CONTROL = 0x05,
        /**
         * @brief Thermal regulation control
         *  bits 7   6   5   4   3   2   1   0
         *       0   0   0   0   0   0  - TREG
         *
         * TREG: Thermal Regulation Threshold 00 – 60°C, 01 – 80°C, 10 – 100°C, 11 – 120°C (Default 120°)
         */
        THERMAL_REG_CONTROL = 0x06,
        /**
         * @brief Miscelaneous configuration
         *  bits 7   6   5   4   3   2   1   0
         *      DPD TMR BFT  0   1   0  INT_MASK
         *
         *  DPD Force DPDM detection 0 – Not in D+/D– detection; 1 – Force D+/D– detection
         *  TMR Safety Timer Setting during Input DPM and Thermal Regulation 0 – Safety timer not slowed by 2X during input DPM or thermal regulation, 1 – Safety timer slowed by 2X duringinput DPM or thermal regulation
         *  BFT Force BATFET Off 0 – Allow Q4 turn on, 1 – Turn off Q4
         *  INT_MASK[1] 0 – No INT during CHRG_FAULT, 1 – INT on CHRG_FAULT
         *  INT_MASK[0] 0 – No INT during BAT_FAULT, 1 – INT on BAT_FAULT
         */
        MISC_CONTROL = 0x07,
        /**
         * @brief System status (Read Only)
         *  bits 7   6   5   4   3   2   1   0
         *       VBUS    CHRG   DPM  PG THS VSYS
         *
         *   VBUS 00 – Unknown (no input, or DPDM detection incomplete), 01 – USB host, 10 – Adapter port, 11 – OTG
         *   CHRG 00 – Not Charging, 01 – Pre-charge (<VBATLOWV), 10 – Fast Charging, 11 – Charge Termination Done
         *   DPM  0 – Not DPM, 1 – VINDPM or IINDPM
         *   PG   0 – Not Power Good, 1 – Power Good
         *   THS  0 – Normal, 1 – In Thermal Regulation
         *   VSYS 0 – Not in VSYSMIN regulation (BAT > VSYSMIN), 1 – In VSYSMIN regulation (BAT <VSYSMIN)
         */
        SYSTEM_STATUS = 0x08,
        /**
         * @brief Fault register (Read Only)
         *  bits 7   6   5   4   3   2   1   0
         *       WE  0  ChgFlt  IOV ThermalFault
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

    /**
     * @brief Read the version register
     * @return The version register
     */
    [[nodiscard]] uint8_t getVersion() const;
};

}// namespace sbs::sensor
