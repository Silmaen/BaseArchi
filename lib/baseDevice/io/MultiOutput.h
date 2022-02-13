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
#include <base/core/memory.h>

namespace sys::io {

/**
 * @brief Class MultiOutput
 */
class MultiOutput: public Output {
public:
    /// Item's type
    using item_type = base::core::SharedPtr<Output>;
    /// List of outputs
    using Outputs = std::vector<item_type>;
    /// Iterator to outputs
    using iterator = Outputs::iterator;

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
    ~MultiOutput() override = default;//---UNCOVER---

    void print(const data::DString& str) override;

    /**
     * @brief Add output to the list
     * @param output The output to add
     */
    void pushOutput(const item_type& output);

    /**
     * @brief Get the name of the output
     * @return The name of the output
     */
    [[nodiscard]] data::DString getName()const override{return F("Multi");}//---UNCOVER---

    /**
     * @brief Begin iterator
     * @return Iterator to the first output
     */
    iterator begin(){return outputs.begin();}
    /**
     * @brief Begin iterator
     * @return Iterator to the first output
     */
    iterator end(){return outputs.end();}
private:
    /// List of outputs
    Outputs outputs;
};

}// namespace sys::io
