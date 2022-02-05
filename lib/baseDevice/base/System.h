/**
 * @file System.h
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <memory>
#include "io/MultiOutput.h"

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
    System(const System& ) =delete;
    System(System&& ) =delete;
    System& operator=(const System& ) =delete;
    System& operator=(System&& ) =delete;
    /**
     * @brief Destructor.
     */
    virtual ~System() = default;

    /**
     * @brief Access to system
     * @return Pointer to System instance
     */
    static std::shared_ptr<System> getInstance();

    /**
     * @brief Access to system outputs
     * @return
     */
    [[nodiscard]] const io::MultiOutput& getOutput() const { return outputs; }

    /**
     * @brief Add an output to the list
     * @param newOutput The output to add
     */
    void pushOutput(io::Output&& newOutput);

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
    [[nodiscard]] bool doReset() const{return toReset;}

    /**
     * @brief Send a reset notification
     */
    void requestReset(){toReset=true;}
private:
    /**
     * @brief Default constructor.
     */
    System() = default;

    static std::shared_ptr<System> instance_;

    /// Console outputs
    io::MultiOutput outputs;

    /// If the device need reset
    bool toReset = false;
};

}// namespace sys::base
