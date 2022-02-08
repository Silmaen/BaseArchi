/**
 * @file StringInput.h
 * @author argawaen
 * @date 04/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include "Input.h"

namespace sys::io {
/**
 * @brief base classe of input dedicated to debug
 */
class StringInput : Input {
public:
    /**
     * @brief Default constructor.
     */
    StringInput() = default;
    /**
     * @brief Default copy constructor
     */
    StringInput(const StringInput&) = default;
    /**
     * @brief Default move constructor
     */
    StringInput(StringInput&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    StringInput& operator=(const StringInput&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    StringInput& operator=(StringInput&&) = default;
    /**
     * @brief Destructor.
     */
    ~StringInput() override = default;

    /**
     * @brief Check for incoming data
     * @return True if data available
     */
    [[nodiscard]] bool available() const override;

    /**
     * @brief Read Input until next end of line
     * @return The read line
     */
    virtual data::DString getLine() override;

    /**
     * @brief Get the input name
     * @return the input name
     */
    [[nodiscard]] data::DString getName() const override { return F("string"); };

    /**
     * @brief Empty the input buffer
     */
    void flush() override;

    /**
     * @brief Append a line to the buffer
     * @param str The line to add
     */
    void pushToBuffer(const data::DString& str);

private:
    /// The buffer
    data::DString buffer;
};

}// namespace sys::io
