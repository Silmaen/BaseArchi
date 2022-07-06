/**
 * @file hardwareUtils.h
 * @author damien.lachouette 
 * @date 14/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <data/DString.h>

namespace sys::base::core {
/// Kilobytes modifier
constexpr uint32_t kb = 1024;

data::DString getSystemInfo();

}// namespace sys::base::core
