/**
 * @file player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Player::next_id_ = 0;
uint Player::time_step_ = 51;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Player::Player(const struct player_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  battery_(params->battery_max_charge),
  typ_(kPlayer),
  heading_angle_(180),
  angle_delta_(params->angle_delta),
  max_speed_(params->max_speed),
  speed_delta_(params->speed_delta),
  orig_pos_(params->pos),
  motion_handler_(max_speed_, angle_delta_, speed_delta_),
  motion_behavior_(),
  sensor_touch_(),
  sensor_proximity_(100.0, 30.0),
  sensor_distress_(30.0),
  sensor_entity_type_(kPlayer, 30.0),
  super_bot_col_(false),
  id_(-1) {
  motion_handler_.set_heading_angle(heading_angle_);
  motion_handler_.set_speed(2);
  id_ = next_id_++;
  set_distress(false);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Player::TimestepUpdate(uint dt) {
  // check whether the player has been frozen for the
  // minimum amount of time before updating it.
  time_step_++;
  if (time_step_ > 50 && super_bot_col_) {
    motion_handler_.set_speed(2);
    super_bot_col_ = false;
  }
  // if player registers a collision with the superbot.
  // freeze it by decreasing the time_step_ to 0,
  // which ensures that the player would not update
  // itself until 50 TimestepUpdates.
  if (sensor_touch_.get_st_activated()) {
    switch (sensor_entity_type_.get_sensed_type()) {
      case kSuperBot:
      motion_handler_.set_speed(0);
      super_bot_col_ = true;
      time_step_ = 0;
      break;
      default:
      break;
    }
  }
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Player::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Player::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void Player::Accept(EventCommand * e) {
  if (time_step_ > 50)
    motion_handler_.AcceptCommand(e->cmd());
}

// User input commands to change heading or speed
void Player::EventCmd(enum event_commands cmd) {
  if (time_step_ > 50)
    motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

void Player::Reset(void) {
  set_pos(orig_pos_);
  battery_.Reset();
  motion_handler_.Reset();
  motion_handler_.set_heading_angle(heading_angle_);
  motion_handler_.set_speed_delta(speed_delta_);
  motion_handler_.set_max_speed(max_speed_);
  motion_handler_.set_angle_delta(angle_delta_);
  sensor_touch_.Reset();
} /* Reset() */

void Player::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
