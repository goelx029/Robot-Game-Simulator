/**
 * @file arena_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_PARAMS_H_
#define SRC_ARENA_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include "src/common.h"
#include "src/position.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
 * @brief This is a structure definition for the parameters for all the arena
 * entities. This structure contains member variables describing position,
 * color, and radius of all the entities (Assume all entities are circular)
 *
 */
struct arena_entity_params {
  arena_entity_params(void) : radius(), pos(), color() {
  }
  double radius;
  Position pos;
  csci3081::Color color;  // using the color.h for defining colors
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_ENTITY_PARAMS_H_
