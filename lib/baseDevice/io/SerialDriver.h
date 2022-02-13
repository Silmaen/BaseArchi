/**
 * @file SerialDriver.h
 * @author argawaen
 * @date 13/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <base/Driver.h>

namespace sys::io {
/**
 * @brief Class SerialDriver
 */
class SerialDriver: public base::Driver {
public:
    /**
     * @brief Default constructor.
     */
    SerialDriver() = default;
    /**
     * @brief Default copy constructor
     */
    SerialDriver(const SerialDriver&) = default;
    /**
     * @brief Default move constructor
     */
    SerialDriver(SerialDriver&&) = default;
    /**
     * @brief Default copy assignation
     * @return this
     */
    SerialDriver& operator=(const SerialDriver&) = default;
    /**
     * @brief Default move assignation
     * @return this
     */
    SerialDriver& operator=(SerialDriver&&) = default;
    /**
     * @brief Destructor.
     */
    ~SerialDriver() override = default;//---UNCOVER---

    void setup()override;

    void loop() override{};

    [[nodiscard]] data::DString name()const override {return F("serial");}
private:
};

}// namespace sys::io