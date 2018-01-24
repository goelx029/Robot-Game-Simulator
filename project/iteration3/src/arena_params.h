/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef SRC_ARENA_PARAMS_H_
#define SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_params.h"
#include "src/player_params.h"
#include "src/home_base_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
#define MAX_ROBOTS 5

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
 * @brief This is a structure definition for the parameters for the arena.
 * An arena will contain robot, home_base, recharge_station and obstacle(s).
 * Also the arena has finite dimensions and some predefined number of obstacles.
 * This struct helps in initializing the arena.
 *
 */
struct arena_params {
  arena_params(void) :
  superbot(),
  player(),
  recharge_station(),
  home_base(),
  n_obstacles(),
  n_robots(),
  x_dim(),
  y_dim() {
  }
  struct robot_params robots[MAX_ROBOTS];
  struct robot_params superbot;
  struct player_params player;
  struct arena_entity_params recharge_station;
  struct home_base_params home_base;
  struct arena_entity_params obstacles[MAX_OBSTACLES];
  size_t n_obstacles;
  size_t n_robots;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_PARAMS_H_ */
