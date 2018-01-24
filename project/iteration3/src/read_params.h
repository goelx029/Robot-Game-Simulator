/**
 * @file read_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_READ_PARAMS_H_
#define SRC_READ_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <fstream>
#include <string>
#include "src/common.h"
#include "src/robot_params.h"
#include "src/arena_params.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Class that is responsible to read the parameters from the file.
  */
class ReadParams {
 public:
    static csci3081::arena_params params_read();

 private:
};

#endif  // SRC_READ_PARAMS_H_
