/**
 * @file System.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "System.h"
#include "io/SerialOutput.h"
#include "io/SerialInput.h"
#include "io/SerialDriver.h"
#include <algorithm>
#include "core/hardwareUtils.h"


namespace sys::base {

System::system_ptr System::instance_{nullptr};

void System::setup() {
    toReset = false;
    drivers.push_back(core::SharedPtr<Driver>(new io::SerialDriver()));
    // initialize all the drivers
    for(auto& driver : drivers){
        driver->setup();
    }
}

void System::loop() {
    // check for inputs
    for (auto& input : inputs) {
        if (!input->available())
            continue;
        // get first line and flush it
        auto line = input->getLine();
        // echo this line to outputs
        outputs.println(input->getName() + F("> ") + line);
        if (treatCommand(line)) {
            // treat only one command per cycle
            break;
        }
        outputs.println(F("error: Command not found"));
    }
    // frame all the drivers
    for(auto& driver : drivers){
        driver->loop();
    }
}

void System::pushOutput(const io::MultiOutput::item_type& newOutput) {
    outputs.pushOutput(newOutput);
}

System::system_ptr System::getInstance() {
    if (instance_ == nullptr) {
        instance_ = core::SharedPtr<System>(new System());
    }
    return instance_;
}

void System::pushInput(const input_ptr& newInput) {
    inputs.push_back(newInput);
}

System::input_ptr System::getInput(const data::DString& inputName) {
    auto result = std::find_if(inputs.begin(), inputs.end(),
                               [&inputName](const input_ptr& out) { return out->getName() == inputName; });
    if (result == inputs.end())
        return {};
    return *result;
}
io::MultiOutput::item_type System::getOutput(const data::DString& outputName) {
    auto result = std::find_if(outputs.begin(), outputs.end(),
                               [&outputName](const io::MultiOutput::item_type& out) { return out->getName() == outputName; });
    if (result == outputs.end())
        return {};
    return *result;
}


System::driver_ptr System::findDriver(const data::DString& drvName) {
    auto result = std::find_if(drivers.begin(), drivers.end(),
                               [&drvName](const driver_ptr & out) { return out->getName() == drvName; });
    if (result == drivers.end())
        return {};
    return *result;
}

bool System::treatCommand(const data::DString& cmdLine) {
    auto keyword = cmdLine.getFirstWord();
    // the system commands
    if (keyword == F("dmesg")){
        printSystemInfos();
        return true;
    }
    if (keyword == F("halt") || keyword == F("reboot")){
        requestReset();
        return true;
    }
    // find a driver with that name to transmit the command
    auto driver = findDriver(keyword);
    if (driver == nullptr) // no driver found
        return false;
    driver->treatCommand(cmdLine.substr(cmdLine.firstIndexOf(F(" "))));
    return false;
}

void System::printSystemInfos() {
    outputs.println(F("System informations"));
#if defined(ARDUINO_AVR_MEGA2560)
    outputs.println(F("Arduino Mega 2560"));
#elif defined(ARDUINO_AVR_MICRO)
    outputs.println(F("Arduino Micro"));
#elif defined(ARDUINO_SAMD_MKRWIFI1010)
    outputs.println(F("Arduino MKR Wifi 1010"));
#elif defined(ARDUINO_ESP8266_WEMOS_D1MINI)
    outputs.println(F("ESP8266 Wemos D1 mini"));
#elif defined(NATIVE)
    outputs.println(F("Native"));
#else
    outputs.println(F("Unknown platform"));
#endif

}

}// namespace sys::base

