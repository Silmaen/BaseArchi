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
#include <algorithm>

namespace sys::base {

std::shared_ptr<System> System::instance_{nullptr};

void System::setup() {
    toReset = false;
    outputs.pushOutput(std::shared_ptr<io::Output>(new io::SerialOutput()));
}

void System::loop() {
    // check for inputs
    for (auto& input : inputs) {
        if (!input->available())
            continue;
        outputs.println(input->getName() + F("> ") + input->getLine());
    }
}

void System::pushOutput(const std::shared_ptr<io::Output>& newOutput) {
    outputs.pushOutput(newOutput);
}

std::shared_ptr<System> System::getInstance() {
    if (instance_ == nullptr) {
        instance_ = std::shared_ptr<System>(new System());
    }
    return instance_;
}

void System::pushInput(const std::shared_ptr<io::Input>& newInput) {
    inputs.push_back(newInput);
}

std::shared_ptr<io::Input> System::getInput(const data::DString& inputName) {
    auto result = std::find_if(inputs.begin(), inputs.end(),
                               [&inputName](const auto& out) { return out->getName() == inputName; });
    if (result == inputs.end())
        return nullptr;
    return *result;
}
std::shared_ptr<io::Output> System::getOutput(const data::DString& outputName) {
    auto result = std::find_if(outputs.begin(), outputs.end(),
                               [&outputName](const auto& out) { return out->getName() == outputName; });
    if (result == outputs.end())
        return nullptr;
    return *result;
}

}// namespace sys::base
