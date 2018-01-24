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
  orig_color_(params->color),
  superbot_color_(params->superbot_color),
  typ_(kRobot),
  heading_angle_(180),
  orig_max_speed_(params->max_speed),
  superbot_max_speed_(params->superbot_max_speed),
  orig_pos_(params->pos),
  motion_behavior_(),
  sensor_touch_(),
  sensor_proximity_(params->sp_range, params->sp_field_of_view),
  sensor_distress_(params->sp_range),
  sensor_entity_type_(kRobot, params->sp_range),
  orig_range_(params->sp_range),
  orig_field_of_view_(params->sp_field_of_view),
  superbot_sp_range_(params->superbot_sp_range),
  superbot_sp_field_of_view_(params->superbot_sp_field_of_view),
  id_(-1) {
  id_ = next_id_++;
  name_ = "Robot" + std::to_string(id());
  motion_handler_ = new MotionHandlerRobot();
  set_distress(motion_handler_->get_distress());
  motion_handler_->set_max_speed(params->max_speed);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  motion_handler_->Update_All(sensor_touch_, sensor_entity_type_,
                            sensor_proximity_, sensor_distress_);
  set_distress(motion_handler_->get_distress());
  /**
   * if the entity should change its motion behavior that I change
   * the characterstics of the robot accordingly.
   */
  if (motion_handler_->get_change_type()) {
    motion_handler_ = new MotionHandlerSuperBot();
    motion_handler_->set_max_speed(superbot_max_speed_);
    set_entity_type(kSuperBot);
    set_color(superbot_color_);
    name_ = "SuperBot" + std::to_string(id()+1);
    sensor_proximity_.set_range(superbot_sp_range_);
    sensor_proximity_.set_field_of_view(superbot_sp_field_of_view_);
    sensor_distress_.set_range(superbot_sp_range_);
    sensor_entity_type_.set_range(superbot_sp_range_);
  }

  motion_handler_->UpdateVelocity(sensor_touch_);
  motion_behavior_.UpdatePosition(this, dt);
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}


void Robot::Reset(void) {
  name_ = "Robot" + std::to_string(id());
  set_color(orig_color_);
  set_entity_type(kRobot);
  motion_handler_ = new MotionHandlerRobot();
  motion_handler_->Reset();
  motion_handler_->set_max_speed(orig_max_speed_);
  set_heading_angle(0);
  set_pos(orig_pos_);
  set_distress(false);
  sensor_touch_.Reset();
  sensor_proximity_.Reset();
  sensor_distress_.Reset();
  sensor_entity_type_.Reset();
  sensor_proximity_.set_range(orig_range_);
  sensor_proximity_.set_field_of_view(orig_field_of_view_);
  sensor_distress_.set_range(orig_range_);
  sensor_entity_type_.set_range(orig_range_);
} /* Reset() */


NAMESPACE_END(csci3081);
