/**
 * @file StringInput.cpp
 * @author argawaen
 * @date 04/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "StringInput.h"
#include <iostream>
namespace sys::io {

data::DString StringInput::getLine() {
    data::DString result = buffer.getFirstLine();
    buffer.removeFirstLine();
    return result;
}

void StringInput::flush() {
    buffer = "";
}

void StringInput::pushToBuffer(const data::DString& str) {
    buffer += str;
}
bool StringInput::available() const {
    return !buffer.empty();
}


}// namespace sys::io
