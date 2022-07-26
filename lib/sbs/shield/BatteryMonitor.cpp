/**
 * @file BatteryMonitor.cpp
 * @author Silmaen
 * @date 25/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "BatteryMonitor.h"

#ifdef ARDUINO
#include <Arduino.h>
#endif
#ifdef ARDUINO_SAMD_MKRWIFI1010
#include "sensor/Bq24195l.h"
static sbs::sensor::Bq24195l BatteryControler;
#endif
#ifdef ESP8266
ADC_MODE(ADC_VCC);
#endif


namespace sbs::shield {

/**
 * @brief Read input voltage depending on the base architecture
 * @return The input voltage
 */
inline double readVcc() {
#ifdef ARDUINO_ARCH_AVR
    int32_t result;
    // Read 1.1V reference against AVcc
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    delay(2);           // Wait for Vref to settle
    ADCSRA |= _BV(ADSC);// Convert
    while (bit_is_set(ADCSRA, ADSC))
        ;
    result = ADCL;
    result |= ADCH << 8;
    result = 1126400L / result;// Back-calculate AVcc in mV
    return result / 1000.0;
#endif
#ifdef ARDUINO_ARCH_SAMD
    return 0;
#endif
#ifdef ESP8266
    return EspClass::getVcc() / 1024.0;
#endif
    return 0;
}

BatteryMonitor::BatteryMonitor() :
#if defined(ARDUINO_SAMD_MKRWIFI1010)
    BatteryPin{ADC_BATTERY}
#elif defined(NATIVE)
    BatteryPin{0}
#else
    BatteryPin{A0}
#endif
{
}

BatteryMonitor::BatteryMonitor(double minV, double maxV, uint8_t pin) :
    minTension{minV}, maxTension{maxV}, BatteryPin{pin} {}

void BatteryMonitor::init() {
#ifdef ARDUINO
    pinMode(BatteryPin, INPUT);
#ifdef ARDUINO_SAMD_MKRWIFI1010
    BatteryControler.init();
#endif
#endif
}

BatteryMonitor::Status BatteryMonitor::getStatus() const {
#ifdef ARDUINO_SAMD_MKRWIFI1010
    if (BatteryControler.presence()) {
        if (!BatteryControler.isInDPM())
            return Status::Disabled;
        if (BatteryControler.getVbusStatus() == sbs::sensor::Bq24195l::VBusStatus::unknown || BatteryControler.getVbusStatus() == sbs::sensor::Bq24195l::VBusStatus::unknown)
            return Status::External;
        if (BatteryControler.getChargeStatus() == sbs::sensor::Bq24195l::ChargeStatus::NotCharging)
            return Status::Discharging;
        return Status::Charging;
    }
#endif
    return Status::Disabled;
}

double BatteryMonitor::getBatteryPercent() const {
    return (getBatteryVolt() - minTension) / (maxTension - minTension);
}
double BatteryMonitor::getBatteryVolt() const {
#ifdef ARDUINO
    return analogRead(BatteryPin) * (4.3 / 1023.0);

#else
    return minTension;
#endif
}
double BatteryMonitor::getInputVoltage() const {
    return readVcc();
}


}// namespace sbs::shield
