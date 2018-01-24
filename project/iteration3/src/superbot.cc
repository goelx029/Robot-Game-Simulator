/**
 * @file superbot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/superbot.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint SuperBot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SuperBot::SuperBot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  typ_(kSuperBot),
  heading_angle_(180),
  max_speed_(params->max_speed),
  orig_pos_(params->pos),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  sensor_proximity_(params->sp_range, params->sp_field_of_view),
  sensor_distress_(params->sp_range),
  sensor_entity_type_(kSuperBot, params->sp_range),
  id_(-1) {
  id_ = next_id_++;
  set_distress(false);
  motion_handler_.set_max_speed(params->max_speed);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void SuperBot::TimestepUpdate(uint dt) {
  motion_handler_.Update_All(sensor_touch_, sensor_entity_type_,
                            sensor_proximity_, sensor_distress_);
  motion_handler_.UpdateVelocity(sensor_touch_);
  motion_behavior_.UpdatePosition(this, dt);
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void SuperBot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}


/**
 * @brief Reset the state of the SuperBot.
 * We reset all the sensors, and the motion_handler_.
 * Also set the Position of the superbot to be the
 * original position which was passed in by the user
 * through the params_file.txt.
 */
void SuperBot::Reset(void) {
  motion_handler_.Reset();
  set_heading_angle(0);
  set_pos(orig_pos_);
  sensor_touch_.Reset();
  sensor_proximity_.Reset();
  sensor_distress_.Reset();
  sensor_entity_type_.Reset();
} /* Reset() */


NAMESPACE_END(csci3081);
