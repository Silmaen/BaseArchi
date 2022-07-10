/**
 * @file Bme280.h
 * @author damien.lachouette 
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "io/i2c/Device.h"

/**
 * @brief Namespace for the sensors
 */
namespace sbs::sensor {

/**
 * @brief Class BME280
 */
class BME280 : public io::i2c::Device {
public:
    BME280(const BME280&)            = delete;
    BME280(BME280&&)                 = delete;
    BME280& operator=(const BME280&) = delete;
    BME280& operator=(BME280&&)      = delete;
    /**
     * @brief Default constructor.
     */
    BME280();
    /**
     * @brief Destructor.
     */
    ~BME280() override = default;//---UNCOVER---

    /**
     * @brief Sensor Data
     */
    struct SensorData {
        double temperature = 0.0;///< Atmospheric Temperature
        double humidity    = 0.0;///< Atmospheric Humidity
        double pressure    = 0.0;///< Atmospheric pressure
        /**
         * @brief Internal addition
         * @param other Data to add
         * @return updated data
         */
        SensorData& operator+=(const SensorData& other) {
            temperature += other.temperature;
            humidity += other.humidity;
            pressure += other.pressure;
            return *this;
        }
        /**
         * @brief Internal subtract
         * @param other Data to subtract
         * @return updated data
         */
        SensorData& operator-=(const SensorData& other) {
            temperature -= other.temperature;
            humidity -= other.humidity;
            pressure -= other.pressure;
            return *this;
        }
        /**
         * @brief Internal product
         * @param other Scalar to multiply
         * @return updated data
         */
        SensorData& operator*=(const double& other) {
            temperature *= other;
            humidity *= other;
            pressure *= other;
            return *this;
        }
        /**
         * @brief Internal division
         * @param other Scalar to divide
         * @return updated data
         */
        SensorData& operator/=(const double& other) {
            temperature /= other;
            humidity /= other;
            pressure /= other;
            return *this;
        }
        /**
         * @brief Addition
         * @param other Data to add.
         * @return Updated data
         */
        SensorData operator+(const SensorData& other) const {
            SensorData result{*this};
            result += other;
            return result;
        }
        /**
         * @brief Subtract
         * @param other Data to subtract.
         * @return Updated data
         */
        SensorData operator-(const SensorData& other) const {
            SensorData result{*this};
            result -= other;
            return result;
        }
        /**
         * @brief Product
         * @param other constant to multipliy
         * @return updated data
         */
        SensorData operator*(const double& other) const {
            SensorData result{*this};
            result *= other;
            return result;
        }
        /**
         * @brief Division
         * @param other constant to divide
         * @return updated data
         */
        SensorData operator/(const double& other) const {
            SensorData result{*this};
            result /= other;
            return result;
        }
        /**
         * @brief Get altitude based on QNH
         * @param qnh the MSL-corrected pressure
         * @return The sensor altitude
         */
        [[nodiscard]] double getAltitude(double qnh) const;
        /**
         * @brief Get MSL-Corrected pressure base on sensor altitude
         * @param actualAltitude Sensor altitude
         * @return The MSL-Corrected pressure
         */
        [[nodiscard]] double getQnh(double actualAltitude) const;
    };

    /**
     * \brief device settings
     */
    struct Setting {
        /**
         * @brief The internal modes of work
         */
        enum struct WorkingMode {
            Sleep  = 0b00,///< No operation, all register accessible, lowest power, startup mode
            Forced = 0b01,///< Perform 1 measurement, store results, then sleep (wake up only on demand)
            Normal = 0b11,///< Perpetual measurement and inactive period cycle (set by StandyByTime)
        };

        /**
         * @brief oversampling possibilities
         *
         * The oversampling is set for each sensor. the values are the same.
         */
        enum struct Oversampling {
            Off   = 0,    ///< sensor deactivated
            O_X1  = 0b001,///< one sample
            O_X2  = 0b010,///< 2 sample
            O_X4  = 0b011,///< 4 sample
            O_X8  = 0b100,///< 8 sample
            O_X16 = 0b101,///< 16 sample
        };

        /**
         * @brief filtering options
         */
        enum struct FilterCoefficient {
            Off  = 0b000,///< filter off
            F_2  = 0b001,///< filter coefficient 2
            F_4  = 0b010,///< filter coefficient 4
            F_8  = 0b011,///< filter coefficient 8
            F_16 = 0b100,///< filter coefficient 16
        };

        /**
         * @brief The stand by time between two measure
         */
        enum struct StandByTime {
            SBT_0_5  = 0b000,///< 0.5 ms
            SBT_62_5 = 0b001,///< 62.5 ms
            SBT_125  = 0b010,///< 125 ms
            SBT_250  = 0b011,///< 250 ms
            SBT_500  = 0b100,///< 500 ms
            SBT_100  = 0b101,///< 100 ms
            SBT_10   = 0b110,///< 10 ms
            SBT_20   = 0b111,///< 20 ms
        };

        WorkingMode mode                     = WorkingMode::Sleep;    ///< Operating mode
        Oversampling pressureOversampling    = Oversampling::Off;     ///< Oversampling for pressure
        Oversampling temperatureOversampling = Oversampling::Off;     ///< Oversampling for temperature
        Oversampling humidityOversampling    = Oversampling::Off;     ///< Oversampling for humidity
        StandByTime sdTime                   = StandByTime::SBT_0_5;  ///< Stand by time
        FilterCoefficient filter             = FilterCoefficient::Off;///< Filter coefficient

        /**
         * @brief Constructor
         * @param m WorkingMode
         * @param po Pressure over sampling
         * @param to Temperature over sampling
         * @param ho Humidity over sampling
         * @param sdt Stand by time
         * @param fc Filter coefficient
         */
        constexpr Setting(const WorkingMode& m,
                          const Oversampling& po,
                          const Oversampling& to,
                          const Oversampling& ho,
                          const StandByTime& sdt,
                          const FilterCoefficient& fc) :
            mode{m},
            pressureOversampling{po}, temperatureOversampling{to}, humidityOversampling{ho}, sdTime{sdt}, filter{fc} {}

        /**
         * @brief Convert to Humidity register
         * @return Humidity register
         */
        [[nodiscard]] uint8_t toCtrlHumReg() const { return static_cast<uint8_t>(humidityOversampling); }
        /**
         * @brief Convert to Measure register
         * @return Measure register
         */
        [[nodiscard]] uint8_t toCtrlMeasReg() const {
            return (static_cast<uint8_t>(temperatureOversampling) << 5U) + (static_cast<uint8_t>(pressureOversampling) << 2U) +
                   static_cast<uint8_t>(mode);
        }
        /**
         * @brief Convert to Config register
         * @return Config register
         */
        [[nodiscard]] uint8_t toConfigReg() const { return (static_cast<uint8_t>(sdTime) << 5U) + (static_cast<uint8_t>(filter) << 2U); }
        /**
         * @brief Get the estimated max measurement time.
         * @return The estimated max measurement time.
         */
        [[nodiscard]] uint16_t maxMeasurementTime() const {
            float estimation = 1.25F + (2.3F * static_cast<float>(temperatureOversampling));
            if (pressureOversampling != Oversampling::Off)
                estimation += (2.3F * static_cast<float>(pressureOversampling) + 0.575F);
            if (humidityOversampling != Oversampling::Off)
                estimation += (2.3F * static_cast<float>(humidityOversampling) + 0.575F);
            return estimation + 0.5F;
        }
        /**
         * @brief PREDEFINED SETTINGS as mention in the datasheet
         */
        enum struct PredefinedSettings {
            /**
         * @brief Weather monitoring set of parameters
         *
         *  Only 1 measure/minute is recommended
         *  Current consumption: 0.16µA
         *  RMS Noise: 3.3Pa/30cm, 0.07%RH
         *  Data output rate: 1/60Hz
         */
            WeatherMonitor,
            /**
         * @brief Humidity sensing set of parameters
         *
         *  Only 1 measure/second is recommended, presure measurment is deactivated
         *  Current consumption: 2.9µA
         *  RMS Noise: 0.07%RH
         *  Data output rate: 1Hz
         */
            HumiditySensing,
            /**
         * @brief Indoor navigation set of parameters
         *
         *  Current consumption: 633µA
         *  RMS Noise: 0.2Pa/1.7cm
         *  Data output rate: 25Hz
         *  Filter bandwidth: 0.53Hz
         *  Response time (75%): 0.9s
         */
            IndoorNavigation,
            /**
         * @brief Gaming set of parameters
         *
         *  Humidity sensor is deactivated
         *  Current consumption: 581
         *  RMS Noise: 0.3Pa/2.5cm
         *  Data output rate: 83Hz
         *  Filter bandwidth: 1.75Hz
         *  Response time (75%): 0.3s
         */
            Gaming
        };
        /**
         * @brief Get predefined setting
         * @param which Which wanted profile
         * @return The Settings.
         */
        static Setting getPredefined(const PredefinedSettings& which) {
            switch (which) {
            case PredefinedSettings::WeatherMonitor:
                return {WorkingMode::Forced, Oversampling::O_X1, Oversampling::O_X1,
                        Oversampling::O_X1, StandByTime::SBT_0_5, FilterCoefficient::Off};
            case PredefinedSettings::HumiditySensing:
                return {WorkingMode::Forced, Oversampling::Off, Oversampling::O_X1,
                        Oversampling::O_X1, StandByTime::SBT_0_5, FilterCoefficient::Off};
            case PredefinedSettings::IndoorNavigation:
                return {WorkingMode::Normal, Oversampling::O_X16, Oversampling::O_X2,
                        Oversampling::O_X1, StandByTime::SBT_0_5, FilterCoefficient::F_16};
            case PredefinedSettings::Gaming:
                return {WorkingMode::Normal, Oversampling::O_X4, Oversampling::O_X1,
                        Oversampling::Off, StandByTime::SBT_0_5, FilterCoefficient::F_16};
            }
            return {WorkingMode::Forced, Oversampling::O_X1, Oversampling::O_X1,
                    Oversampling::O_X1, StandByTime::SBT_0_5, FilterCoefficient::Off};
        }
    };

    /**
     * @brief Get measured values
     * @return The mease of the sensor
     */
    [[nodiscard]] const SensorData& getValue();

    /**
     * @brief Init device
     */
    void init() override;

    /**
     * @brief Get device's name
     * @return The device's name.
     */
    [[nodiscard]] string getName() const override { return "BME280"; }

    /**
     * @brief Check the presence of the device.
     * @return Return true if the device is found.
     */
    [[nodiscard]] bool checkPresence() const override;

    /**
     * @brief Make the data backup void
     */
    void voidData() {
        data = SensorData{};
    }

    /**
     * @brief Get a copy of actual settings.
     * @return The actual settings.
     */
    [[nodiscard]] Setting getSetting() const { return setting; }

    /**
     * @brief Get a copy of actual settings.
     * @param set The new settings.
     */
    void setSetting(const Setting& set) {
        setting = set;
        applySetting();
    }
    /**
     * @brief Set the device in some predefined mode
     * @param predefined The desired mode
     */
    void setPredefinedSettings(const Setting::PredefinedSettings& predefined) {
        setting = Setting::getPredefined(predefined);
        applySetting();
    }

private:
    /// Device Settings
    Setting setting = Setting::getPredefined(Setting::PredefinedSettings::WeatherMonitor);

    /// Sensor Data
    SensorData data = SensorData{};

    /**
     * @brief Write setting into the registers.
     */
    void applySetting();

    /**
     * @brief Definition of registers constants
     */
    enum Registers {
        // config
        R_ID        = 0xD0,///< Chip ID
        R_RESET     = 0xE0,///< soft reset
        R_CTRL_HUM  = 0xF2,///< Humidity options register
        R_STATUS    = 0xF3,///< Status of the device bit 0 : im_update (1 copying, 0 ready) bit 3 measuring (0: ready)
        R_CTRL_MEAS = 0xF4,///< pressure/temp (need to be set after ctrl_hum)
        R_CONFIG    = 0xF5,///< set rates, filter & interface
        // measure data
        R_PRESS_MSB  = 0xF7,///< pressure data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_PRESS_LSB  = 0xF8,///< pressure data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_PRESS_XLSB = 0xF9,///< pressure data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_TEMP_MSB   = 0xFA,///< temperature data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_TEMP_LSB   = 0xFB,///< temperature data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_TEMP_XLSB  = 0xFC,///< temperature data = `(MSB << 16 + LSB << 8 + XLSB) >> 4`
        R_HUM_MSB    = 0xFD,///< humidity data = `MSB << 8 + LSB`
        R_HUM_LSB    = 0xFE,///< humidity data = `MSB << 8 + LSB`
        // calibration data
        R_T1_LSB = 0x88,///< T1 coefficient LSB-first
        R_T2_LSB = 0x8A,///< T2 coefficient LSB-first
        R_T3_LSB = 0x8C,///< T3 coefficient LSB-first
        R_P1_LSB = 0x8E,///< P1 coefficient LSB-first
        R_P2_LSB = 0x90,///< P2 coefficient LSB-first
        R_P3_LSB = 0x92,///< P3 coefficient LSB-first
        R_P4_LSB = 0x94,///< P4 coefficient LSB-first
        R_P5_LSB = 0x96,///< P5 coefficient LSB-first
        R_P6_LSB = 0x98,///< P6 coefficient LSB-first
        R_P7_LSB = 0x9A,///< P7 coefficient LSB-first
        R_P8_LSB = 0x9C,///< P8 coefficient LSB-first
        R_P9_LSB = 0x9E,///< P9 coefficient LSB-first
        R_H1     = 0xA1,///< H1 coefficient
        R_H2_LSB = 0xE1,///< H2 coefficient LSB-first
        R_H3     = 0xE3,///< H3
        R_H4_MSB = 0xE4,///< H4 must bust left-shited by 4
        R_H4_H5  = 0xE5,///< H4 the firsts 4 bits are the first four bits of H4, the last 4bit are the LSB for H5
        R_H5_MSB = 0xE6,///< H5 must bust left-shited by 4
        R_H6     = 0xE7,///< H6
    };

    /**
     * @brief Sensor Calibration constants for compensation computation
     */
    struct CalibrationDataDbl {
        double T1=0; ///< T1
        double T2=0; ///< T2
        double T3=0; ///< T3
        double P1=0; ///< P1
        double P2=0; ///< P2
        double P3=0; ///< P3
        double P4=0; ///< P4
        double P5=0; ///< P5
        double P6=0; ///< P6
        double P7=0; ///< P7
        double P8=0; ///< P8
        double P9=0; ///< P9
        double H1=0; ///< H1
        double H2=0; ///< H2
        double H3=0; ///< H3
        double H4=0; ///< H4
        double H5=0; ///< H5
        double H6=0; ///< H6
    };

    CalibrationDataDbl cal;///< storage of calibration data

    /**
     * \brief read & store calibration data
     */
    void readCalibration();

    /**
     * @brief Get data from device and compute the compensations
     */
    void readAndCompensate();
};

}// namespace sbs::sensor
