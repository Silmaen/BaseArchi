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

System::system_ptr System::instance_{nullptr};

void System::setup() {
    toReset = false;
#ifdef HAS_SMART_PTR
    outputs.pushOutput(std::shared_ptr<io::Output>(new io::SerialOutput()));
#else
    outputs.pushOutput(new io::SerialOutput());
#endif
}

void System::loop() {
    // check for inputs
    for (auto& input : inputs) {
        if (!input->available())
            continue;
        outputs.println(input->getName() + F("> ") + input->getLine());
    }
}

void System::pushOutput(const io::MultiOutput::item_type& newOutput) {
    outputs.pushOutput(newOutput);
}

System::system_ptr System::getInstance() {
    if (instance_ == nullptr) {
#ifdef HAS_SMART_PTR
        instance_ = std::shared_ptr<System>(new System());
#else
        instance_ = new System();
#endif
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
        return nullptr;
    return *result;
}
io::MultiOutput::item_type System::getOutput(const data::DString& outputName) {
    auto result = std::find_if(outputs.begin(), outputs.end(),
                               [&outputName](const io::MultiOutput::item_type& out) { return out->getName() == outputName; });
    if (result == outputs.end())
        return nullptr;
    return *result;
}

}// namespace sys::base
