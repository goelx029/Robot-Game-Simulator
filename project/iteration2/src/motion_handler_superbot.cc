/**
 * @file motion_handler_superbot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_superbot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerSuperBot::MotionHandlerSuperBot() :
  freeze_(false),
  MotionHandler() {
    set_max_speed(8);
    set_speed(get_max_speed());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerSuperBot::UpdateVelocity(SensorTouch st) {
  if (st.get_activated()) {
    set_heading_angle(-st.get_angle_of_contact());
  }
}

void MotionHandlerSuperBot::Update_All(SensorTouch sensor_touch_,
  SensorEntityType sensor_entity_type_,
  SensorProximity sensor_proximity_,
  SensorDistress sensor_distress_) {
  // It doesnt matter whether superbot collides with anything because it doesnt
  // change its motion. Hence check for entities in proximity of the superbot.
  // Use information from the SensorProximity, to find the entity
  // type of the entity
  // which is within the proximity of the superbot.
  // Then change the motion of the robot accordingly to implement the
  // Iteration2 functionality.
  set_change_type(false);
  if (sensor_proximity_.get_sp_activated()) {
    switch (sensor_proximity_.get_sensed_type()) {
      case kPlayer: {
        set_speed(get_max_speed());
        double a_of_c = sensor_proximity_.get_angle_contact();
        set_heading_angle(a_of_c);
      }
      break;
      case kSuperBot:
      case kRechargeStation:
      case kHomeBase:
      case kObstacle: {
        if (get_heading_angle() > sensor_proximity_.get_angle_contact())
          set_heading_angle(get_heading_angle() + 5);
        else
          set_heading_angle(get_heading_angle() - 5);
        double speed = get_speed();
        double dist = sensor_proximity_.get_output();
        double new_speed = speed - (20/dist)*speed;
        set_speed(new_speed);
      }
      break;
      case kRobot: {
        if (!sensor_distress_.get_sd_activated()) {
          if (get_heading_angle() > sensor_proximity_.get_angle_contact())
            set_heading_angle(get_heading_angle() + 5);
          else
            set_heading_angle(get_heading_angle() - 5);
          double speed = get_speed();
          double dist = sensor_proximity_.get_output();
          double new_speed = speed - (20/dist)*speed;
          set_speed(new_speed);
        } else {
          double a_of_c = sensor_proximity_.get_angle_contact();
          set_heading_angle(a_of_c);
        }
      }
      break;
      default:
      break;
    }
  } else {
    set_speed(get_max_speed());
  }
}

void MotionHandlerSuperBot::Reset(void) {
  set_max_speed(get_max_speed());
  set_speed(get_max_speed());
  set_heading_angle(270);
}

NAMESPACE_END(csci3081);
