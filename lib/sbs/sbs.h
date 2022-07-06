/**
 * @file sbs.h
 * @author damien.lachouette 
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
/**
 * @brief Namespace for the Silmaen base System
 */
namespace sbs {

/**
 * @brief Function called once at the beginning of execution
 */
void setup();

/**
 * @brief Function called in an infinite loop
 */
void loop();

/**
 * @brief Define the return code of program
 * @param returnCode The new return code
 */
void setExecReturn(int returnCode);

/**
 * @brief Kill the main loop
 */
void killLoop();

}// namespace sbs
