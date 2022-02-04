/**
 * @file Output.cpp
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Output.h"

namespace sys::io {

void Output::println(const data::DString& str) {
    print(str + F("\n"));
}

}// namespace sys::io
