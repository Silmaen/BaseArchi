
#include <core/Print.h>
#include <physic/conversions.h>
#include <sbs.h>
#include <sensor/Bme280.h>
#include <sensor/Bq24195l.h>
#include <shield/MKREnv.h>
#include <time/timing.h>

sbs::shield::MKREnv ENV;
sbs::sensor::Bq24195l PowerManager;
sbs::sensor::BME280 bme;


#ifdef ARDUINO_SAMD_MKRWIFI1010
#include <Arduino.h>
#endif

void sbs::setup() {
    ENV.init();
    ENV.gerPTSensor().setPressureOffset(2.4119);
    PowerManager.init();
    bme.init();
#ifdef ARDUINO_SAMD_MKRWIFI1010
    pinMode(ADC_BATTERY, INPUT);
#endif
    //PowerManager.getSettings().setFastChargeCurrent(2.2);
    //PowerManager.getSettings().setChargeVoltage(4.208);
    //PowerManager.getSettings().battPreChargeToFastCharge = sbs::sensor::Bq24195l::Settings::BattPreChargeToFastCharge::V28;
    //PowerManager.getSettings().dpdmDetection = sbs::sensor::Bq24195l::Settings::DPDMDetection::No;
    //PowerManager.ApplySettings();
}

void sbs::loop() {
    ENV.selfCheck();
    PowerManager.selfCheck();
    bme.selfCheck();
    // ENV Shield
    if (false) {
        auto data_e = ENV.getValue();
        {
            sbs::io::logger(" ENV: T=");
            sbs::io::logger(data_e.temperature);
            sbs::io::logger(" P=");
            sbs::io::logger(data_e.pressure);
            sbs::io::logger(" QNH=");
            sbs::io::logger(sbs::physic::computeQnh(295, data_e.pressure, data_e.temperature));
            sbs::io::logger(" H=");
            sbs::io::logger(data_e.humidity);
        }
        auto data_b = bme.getValue();
        {

            sbs::io::logger(" BME: T=");
            sbs::io::logger(data_b.temperature);
            sbs::io::logger(" P=");
            sbs::io::logger(data_b.pressure);
            sbs::io::logger(" QNH=");
            sbs::io::logger(sbs::physic::computeQnh(295, data_b.pressure, data_b.temperature));
            sbs::io::logger(" H=");
            sbs::io::logger(data_b.humidity);
        }
        {
            sbs::io::logger(" Delta: T=");
            sbs::io::logger(data_e.temperature - data_b.temperature);
            sbs::io::logger(" P=");
            sbs::io::logger(data_e.pressure - data_b.pressure);
            sbs::io::logger(" QNH=");
            sbs::io::logger(sbs::physic::computeQnh(295, data_e.pressure, data_e.temperature) - sbs::physic::computeQnh(295, data_b.pressure, data_b.temperature));
            sbs::io::logger(" H=");
            sbs::io::loggerln(data_e.humidity - data_b.humidity);
        }
    }
    // power management
    if (true) {
#ifdef ARDUINO_SAMD_MKRWIFI1010
        double voltage = analogRead(ADC_BATTERY) * (4.3 / 1023.0);
        sbs::io::logger("BaT: V=");
        sbs::io::loggerln(voltage);
        //sbs::io::logger(" ");
        PowerManager.setChargingMode(sbs::sensor::Bq24195l::ChargingMode::Normal);
        sbs::io::loggerln("Status registers: ");
        sbs::io::loggerln(PowerManager.readSystemStatusRegister(),sbs::io::IntFormat::Binary);
        sbs::io::loggerln(PowerManager.readFaultRegister(),sbs::io::IntFormat::Binary);

#endif
        sbs::io::logger(" -- Power Status: ");
        if (!PowerManager.presence()) {
            sbs::io::loggerln("No Power Manager. ");
        } else {
            switch (PowerManager.getVbusStatus()) {
            case sbs::sensor::Bq24195l::VBusStatus::unknown:
                sbs::io::logger("Unknown .");
                break;
            case sbs::sensor::Bq24195l::VBusStatus::usb:
                sbs::io::logger("USB power. ");
                break;
            case sbs::sensor::Bq24195l::VBusStatus::AdapterPort:
                sbs::io::logger("Battery power. ");
                break;
            case sbs::sensor::Bq24195l::VBusStatus::otg:
                sbs::io::logger("Powering USB by battery. ");
                break;
            }
            if (PowerManager.isInDPM()) {
                switch (PowerManager.getChargeStatus()) {
                case sbs::sensor::Bq24195l::ChargeStatus::NotCharging:
                    sbs::io::logger("Not charging. ");
                    break;
                case sbs::sensor::Bq24195l::ChargeStatus::PreCharge:
                    sbs::io::logger("Pre charge. ");
                    break;
                case sbs::sensor::Bq24195l::ChargeStatus::FastCharging:
                    sbs::io::logger("Fast charge. ");
                    break;
                case sbs::sensor::Bq24195l::ChargeStatus::ChargeTerminaison:
                    sbs::io::logger("End charge. ");
                    break;
                }
            } else {
                sbs::io::logger("No battery detected.");
            }
            sbs::io::loggerln(PowerManager.isPowerGood() ? " Good power" : "Bad power");
        }
    }
    sbs::time::delay(1000);
}
