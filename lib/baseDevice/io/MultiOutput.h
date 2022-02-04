/**
 * @file MultiOutput.h
 * @author argawaen
 * @date 01/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "Output.h"
#include <vector>

namespace sys::io {

/**
 * @brief Class MultiOutput
 */
class MultiOutput: public Output {
public:
    MultiOutput(const MultiOutput&) = delete;
    MultiOutput(MultiOutput&&) = delete;
    MultiOutput& operator=(const MultiOutput&) = delete;
    MultiOutput& operator=(MultiOutput&&) = delete;
    /**
     * @brief Default constructor.
     */
    MultiOutput() = default;
    /**
     * @brief Destructor.
     */
    ~MultiOutput() override = default;

    void print(const data::DString& str) override;

    /**
     * @brief Add output to the list
     * @param output The output to add
     */
    void pushOutput(const Output& output);

    /**
     * @brief Add output to the list
     * @param output The output to add
     */
    void pushOutput(Output&& output);
private:
    using Outputs = std::vector<Output>;
    /// List of outputs
    Outputs outputs;
};

}// namespace sys::io
