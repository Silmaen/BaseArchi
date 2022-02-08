/**
 * @file StringOutput.h
 * @author argawaen
 * @date 08/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "Output.h"

namespace sys::io {

/**
 * @brief Class Output class used for debugging
 */
class StringOutput : public Output {
public:
    /**
     * @brief Default constructor.
     */
    StringOutput() = default;
    /**
     * @brief Default copy constructor
     */
    StringOutput(const StringOutput&) = default;
    /**
     * @brief Default move constructor
     */
    StringOutput(StringOutput&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    StringOutput& operator=(const StringOutput&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    StringOutput& operator=(StringOutput&&) = default;
    /**
     * @brief Destructor.
     */
    ~StringOutput() override = default;//---UNCOVER---
    /**
     * @brief Get the name of the output
     * @return The name of the output
     */
    [[nodiscard]] data::DString getName()const override{return F("String");}

    void print(const data::DString& str) override{buffer += str; };

    /**
     * @brief Empty the buffer
     */
    void flush(){buffer = data::DString{};}

    /**
     * @brief Read access to the buffer
     * @return The buffer
     */
    [[nodiscard]] const data::DString& getBuffer()const {return buffer;}
private:
    /// internal buffer
    data::DString buffer;
};

}// namespace sys::io
