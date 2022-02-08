/**
* @file main.cpp
* @author argawaen
* @date 01/02/2022
* Copyright © 2022 All rights reserved.
* All modification must get authorization from the author.
*/
#ifdef ARDUINO
#include <Arduino.h>
#endif
#include <base/System.h>

/**
 * @brief Initialization function
 */
void setup() {
    sys::base::System::getInstance()->setup();
}

/**
 * @brief Iteration of the infinite loop
 */
void loop() {
    auto hardware = sys::base::System::getInstance();
    hardware->loop();
#ifdef ARDUINO
    if (hardware->doReset())
        setup();
#endif
}

#ifndef ARDUINO
#include <io/StringOutput.h>
#include <io/StringInput.h>
/**
 * @brief Main entry point
 * @retval 0
 */
int main(){
    auto hardware = sys::base::System::getInstance();
    hardware->setup();
    hardware->pushOutput(std::shared_ptr<sys::io::Output>(new sys::io::StringOutput()));
    hardware->pushInput(std::shared_ptr<sys::io::Input>(new sys::io::StringInput()));
    // =========
//    auto inputTemp = hardware->getInput(0);
//    auto input = std::static_pointer_cast<sys::io::StringInput>(inputTemp);

    /*
    setup();
    while (!sys::base::System::getInstance()->doReset()){
        loop();
    }
     */
    return 0;
}
#endif
