/**
 * @file SerialInput.h
 * @author argawaen
 * @date 10/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "Input.h"
namespace sys::io {
/**
 * @brief Class SerialInput
 */
class SerialInput :public Input {
public:
    /**
     * @brief Default constructor.
     */
    SerialInput() = default;
    /**
     * @brief Default copy constructor
     */
    SerialInput(const SerialInput&) = default;
    /**
     * @brief Default move constructor
     */
    SerialInput(SerialInput&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    SerialInput& operator=(const SerialInput&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    SerialInput& operator=(SerialInput&&) = default;
    /**
     * @brief Destructor.
     */
    ~SerialInput() override = default;

    [[nodiscard]] bool available() const override;

    data::DString getLine() override;

    [[nodiscard]] data::DString getName() const override {return F("serial");}

    void flush() override;
private:
};
}// namespace sys::io
