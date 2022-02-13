/**
 * @file MultiOutput.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "MultiOutput.h"

namespace sys::io {

void MultiOutput::print(const sys::data::DString& str) {
    for (auto& out : outputs) {
        out->print(str);
    }
}

void MultiOutput::pushOutput(const item_type& output) {
    outputs.push_back(output);
}

}// namespace sys::io
