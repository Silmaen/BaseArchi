/**
 * @file Device.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "baseDevice.h"

namespace sbs::io {

void baseDevice::selfCheck() {
    bool oPresence = present;
    present        = checkPresence();
    if (oPresence == present)
        return;
    if (present) {
        onConnect();
    } else {
        onDisconnect();
    }
}

}// namespace sbs::io
