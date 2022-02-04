/**
 * @file StringInput.cpp
 * @author argawaen
 * @date 04/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "StringInput.h"

namespace sys::io {

data::DString StringInput::getLine() {
    return Input::getLine();
}

void StringInput::flush() {
    buffer = "";
}

void StringInput::pushToBuffer(const data::DString& str) {
    buffer += str + F("\n");
}


}// namespace sys::io
