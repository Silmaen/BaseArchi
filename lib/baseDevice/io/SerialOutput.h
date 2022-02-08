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
     * @brief Default copy constructor
     */
    SerialOutput(const SerialOutput&) = default;
    /**
     * @brief Default move constructor
     */
    SerialOutput(SerialOutput&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    SerialOutput& operator=(const SerialOutput&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    SerialOutput& operator=(SerialOutput&&) = default;
    /**
     * @brief Destructor.
     */
    ~SerialOutput() override = default;//---UNCOVER---


    void print(const data::DString& str) override;
    /**
     * @brief Get the name of the output
     * @return The name of the output
     */
    [[nodiscard]] data::DString getName()const override{return F("Serial");}
private:
};

extern SerialOutput serialOutput;

}// namespace sys::io
