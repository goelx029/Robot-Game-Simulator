/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Robot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  battery_(params->battery_max_charge),
  heading_angle_(180),
  angle_delta_(params->angle_delta),
  max_speed_(params->max_speed),
  speed_delta_(params->speed_delta),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  id_(-1) {
  orig_pos_ = params->pos,
  motion_handler_.set_heading_angle(heading_angle_);
  motion_handler_.set_speed(2);
  motion_handler_.set_angle_delta(angle_delta_);
  motion_handler_.set_max_speed(max_speed_);
  motion_handler_.set_speed_delta(speed_delta_);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
  // Deplete battery as appropriate given distance and speed of movement
  battery_.Deplete(old_pos, get_pos(), dt);
} /* TimestepUpdate() */

void Robot::Accept(__unused EventRecharge * e) {
  battery_.EventRecharge();
}

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void Robot::Accept(EventCommand * e) {
  motion_handler_.AcceptCommand(e->cmd());
}

// User input commands to change heading or speed
void Robot::EventCmd(enum event_commands cmd) {
  motion_handler_.AcceptCommand(cmd);
} /* event_cmd() */

void Robot::Reset(void) {
  set_pos(orig_pos_);
  battery_.Reset();
  motion_handler_.Reset();
  motion_handler_.set_heading_angle(heading_angle_);
  motion_handler_.set_speed_delta(speed_delta_);
  motion_handler_.set_max_speed(max_speed_);
  motion_handler_.set_angle_delta(angle_delta_);
  sensor_touch_.Reset();
} /* Reset() */

void Robot::ResetBattery(void) {
  battery_.Reset();
}

NAMESPACE_END(csci3081);
