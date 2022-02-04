/**
 * @file Input.h
 * @author argawaen
 * @date 04/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "data/DString.h"
namespace sys::io {

/**
 * @brief Base class for user input
 */
class Input {
public:
    /**
     * @brief Default constructor.
     */
    Input() = default;
    /**
     * @brief Default copy constructor
     */
    Input(const Input&) = default;
    /**
     * @brief Default move constructor
     */
    Input(Input&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    Input& operator=(const Input&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    Input& operator=(Input&&) = default;
    /**
     * @brief Destructor.
     */
    virtual ~Input() = default;

    /**
     * @brief Check for incoming data
     * @return True if data available
     */
    [[nodiscard]] virtual bool available()const{return false;};

    /**
     * @brief Read Input until next end of line
     * @return The read line
     */
    virtual data::DString getLine() {return {};};

    /**
     * @brief Get the input name
     * @return the input name
     */
    [[nodiscard]] virtual data::DString getName()const {return F("unknown");};

    /**
     * @brief Empty the input buffer
     */
    virtual void flush(){}
private:
};

}// namespace sys::io
