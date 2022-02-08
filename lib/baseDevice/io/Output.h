/**
 * @file Output.h
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

#include "data/DString.h"

/**
 * @brief Namespace for user IO management
 */
namespace sys::io {

/**
 * @brief Class Output
 */
class Output {
public:
    /**
     * @brief Default copy constructor
     */
    Output(const Output&) = default;
    /**
     * @brief Default move constructor
     */
    Output(Output&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    Output& operator=(const Output&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    Output& operator=(Output&&) = default;
    /**
     * @brief Default constructor.
     */
    Output() = default;
    /**
     * @brief Destructor.
     */
    virtual ~Output() = default;//---UNCOVER---

    /**
      * @brief Output a string
      * @param str The string to output
      */
    virtual void print([[maybe_unused]] const data::DString& str) = 0;//---UNCOVER---

    /**
     * @brief Output a string with end line
     * @param str The string to output
     */
    void println(const data::DString& str);

    /**
     * @brief Get the name of the output
     * @return The name of the output
     */
    [[nodiscard]] virtual data::DString getName() const = 0; //---UNCOVER---

private:
};

}// namespace sys::io
