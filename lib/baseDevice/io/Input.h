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
    virtual ~Input() = default;//---UNCOVER---

    /**
     * @brief Check for incoming data
     * @return True if data available
     */
    [[nodiscard]] virtual bool available() const = 0;//---UNCOVER---

    /**
     * @brief Read Input until next end of line
     * @return The read line
     */
    virtual data::DString getLine() = 0;//---UNCOVER---

    /**
     * @brief Get the input name
     * @return the input name
     */
    [[nodiscard]] virtual data::DString getName() const = 0;//---UNCOVER---

    /**
     * @brief Empty the input buffer
     */
    virtual void flush() = 0;//---UNCOVER---

private:
};

}// namespace sys::io
