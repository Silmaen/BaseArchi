/**
 * @file SerialOutput.h
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "Output.h"

namespace sys::io {

/**
 * @brief Class SerialOutput
 */
class SerialOutput:public Output {
public:
    /**
     * @brief Default constructor.
     */
    SerialOutput() = default;
    /**
     * @brief Destructor.
     */
    virtual ~SerialOutput() = default;


    void print(const data::DString& str) override;
private:
};

extern SerialOutput serialOutput;

}// namespace sys::io
