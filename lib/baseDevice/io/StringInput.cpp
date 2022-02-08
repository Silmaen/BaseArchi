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
    data::DString result = buffer.getFirstLine();
    data::DString::size_type lineIdx = buffer.firstIndexOf('\n');
    buffer = buffer.substr(lineIdx+1,0);
    return result;
}

void StringInput::flush() {
    buffer = "";
}

void StringInput::pushToBuffer(const data::DString& str) {
    buffer += str + F("\n");
}
bool StringInput::available() const {
    return !buffer.empty();
}


}// namespace sys::io
