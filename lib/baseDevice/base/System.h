/**
 * @file System.h
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "io/Input.h"
#include "io/MultiOutput.h"
#include "Driver.h"
#include "core/memory.h"
/**
 * @namespace sys
 * @brief Namespace for architecture project
 */
/**
 * @brief Namespace for base objects
 */
namespace sys::base {

/**
 * @brief Class System
 */
class System {
public:
    System(const System&) = delete;
    System(System&&)      = delete;
    System& operator=(const System&) = delete;
    System& operator=(System&&) = delete;

    /// System pointer size
    using system_ptr = core::SharedPtr<System>;

    /// Input pointer type
    using input_ptr = core::SharedPtr<io::Input>;

    /// Driver pointer type
    using driver_ptr = core::SharedPtr<Driver>;

    /**
     * @brief Destructor.
     */
    virtual ~System() = default;//---UNCOVER---

    /**
     * @brief Access to system
     * @return Pointer to System instance
     */
    static system_ptr getInstance();

    /**
     * @brief Add an output to the list
     * @param newOutput The output to add
     */

    void pushOutput(const io::MultiOutput::item_type& newOutput);

    /**
     * @brief Access to system outputs
     * @return
     */
    [[nodiscard]] const io::MultiOutput& getOutput() const { return outputs; }

    /**
     * @brief Add an input to the list
     * @param newInput The input to add
     */
    void pushInput(const input_ptr& newInput);

    /**
     * @brief Get an input by its name
     * @param inputName The name of the input
     * @return Pointer to the input, nullptr if not exists
     */
    input_ptr getInput(const data::DString& inputName);
    /**
     * @brief Get a specific output by its name
     * @param outputName The name of the output
     * @return Pointer to the input, nullptr if not exists
     */
    io::MultiOutput::item_type getOutput(const data::DString& outputName);

    /**
     * @brief Initial setup
     */
    void setup();

    /**
     * @brief Interation of the quasi infinite loop
     */
    void loop();

    /**
     * @brief Should the device reset?
     * @return True if reset required
     */
    [[nodiscard]] bool doReset() const { return toReset; }

    /**
     * @brief Send a reset notification
     */
    void requestReset() { toReset = true; }

private:
    /**
     * @brief Default constructor.
     */
    System() = default;

    /// Instance of System
    static system_ptr instance_;

    /// Console outputs
    io::MultiOutput outputs;

    /// List of inputs type
    using Inputs = std::vector<input_ptr>;

    /// List of inputs
    Inputs inputs;

    /// List of driver's type
    using Drivers = std::vector<driver_ptr>;

    /// List of inputs
    Drivers drivers;

    /// If the device need reset
    bool toReset = false;
};

}// namespace sys::base
