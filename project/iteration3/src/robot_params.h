/**
 * @file robot_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_PARAMS_H_
#define SRC_ROBOT_PARAMS_H_

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
   * @brief A struct inheriting from arena_mobile_entity_params and responsible
   * for handling all the parameters for the robot entity of the arena.
   *
   */
struct robot_params : public arena_mobile_entity_params {
  robot_params(void) :
      arena_mobile_entity_params(),
      max_speed(),
      superbot_max_speed(),
      sp_range(),
      sp_field_of_view(),
      superbot_sp_range(),
      superbot_sp_field_of_view(),
      superbot_color() {}

  double max_speed;
  double superbot_max_speed;
  double sp_range, sp_field_of_view;
  double superbot_sp_range, superbot_sp_field_of_view;
  csci3081::Color superbot_color;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ROBOT_PARAMS_H_ */
