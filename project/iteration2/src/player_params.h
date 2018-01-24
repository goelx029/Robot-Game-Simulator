/**
 * @file player_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_PARAMS_H_
#define SRC_PLAYER_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
   /**
   * @brief structure that stores the params for the player from the
   * params_file.txt. 
   *
   */
struct player_params : public arena_mobile_entity_params {
  player_params(void) :
      arena_mobile_entity_params(),
      battery_max_charge(),
      angle_delta(),
      speed_delta(),
      max_speed() {}

  double battery_max_charge;
  uint angle_delta;
  double speed_delta;
  double max_speed;
};

NAMESPACE_END(csci3081);

#endif /* SRC_PLAYER_PARAMS_H_ */
