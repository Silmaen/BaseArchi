/**
 * @file System.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "System.h"
#include "io/SerialOutput.h"
#include "time/utils.h"

namespace sys::base {

std::shared_ptr<System> System::instance_{nullptr};

void System::setup() {
    toReset = false;
    outputs.pushOutput(io::serialOutput);
}

void System::loop() {
    sys::time::delay(2000);
    sys::data::DString str{F("System looping\n")};
    if (str == F("System looping\n"))
        outputs.print(str);
}

void System::pushOutput(io::Output&& newOutput) {
    outputs.pushOutput(newOutput);
}

std::shared_ptr<System> System::getInstance() {
    if (instance_ == nullptr) {
        instance_ = std::shared_ptr<System>(new System());
    }
    return instance_;
}

void System::pushInput(io::Input&& newInput) {
    inputs.push_back(std::move(newInput));
}

}// namespace sys::base
