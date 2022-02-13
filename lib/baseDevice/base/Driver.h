/**
 * @file Driver.h
 * @author argawaen
 * @date 13/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "core/memory.h"
#include <data/DString.h>

namespace sys::base {
/**
 * @brief Class Driver
 */
class Driver {
public:
    /**
     * @brief Default constructor.
     */
    Driver() = default;
    /**
     * @brief Default copy constructor
     */
    Driver(const Driver&) = default;
    /**
     * @brief Default move constructor
     */
    Driver(Driver&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    Driver& operator=(const Driver&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    Driver& operator=(Driver&&) = default;
    /**
     * @brief Destructor.
     */
    virtual ~Driver() = default;//---UNCOVER---

    /**
     * @brief Initialize the driver
     */
    virtual void setup() = 0;

    /**
     * @brief Execute one frame of the driver
     */
    virtual void loop() = 0;

    /**
     * @brief The specific name of the driver
     * @return Driver's name
     */
    [[nodiscard]] virtual data::DString name() const { return F("driver"); }
private:
};

}// namespace sys::base
