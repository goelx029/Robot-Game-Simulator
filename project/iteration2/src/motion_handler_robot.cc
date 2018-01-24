/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerRobot::MotionHandlerRobot() :
  MotionHandler(),
  distress_(false),
  freeze_(false) {
    set_max_speed(5);
    set_speed(get_max_speed());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerRobot::UpdateVelocity(SensorTouch st) {
  if (st.get_activated()) {
    set_heading_angle(-st.get_angle_of_contact());
  }
}

void MotionHandlerRobot::Update_All(SensorTouch sensor_touch_,
  SensorEntityType sensor_entity_type_,
  SensorProximity sensor_proximity_,
  SensorDistress sensor_distress_) {
  // first check whether the robot has collided with something.
  // Use this information and information from the SensorEntityType,
  // To find the entity type of the entity with which the robot
  // collided and implement appropriate behavior.
  set_change_type(false);
  if (sensor_touch_.get_st_activated()) {
    switch (sensor_entity_type_.get_sensed_type()) {
      case kPlayer:
      set_speed(0);
      set_distress(true);
      break;
      case kSuperBot:
      case kRobot:
      set_speed(get_max_speed());
      set_distress(false);
      break;
      case kHomeBase:
      set_speed(get_max_speed());
      set_distress(false);
      set_change_type(true);
      default:
      break;
    }
  }
  // If the robot has not collided with anything check for entities in proximity
  // Use this information and information from the SensorProximity,
  // to find the entity type of the entity which is within the
  // proximity of the Robot.
  // Then change the motion of the robot accordingly to implement the
  // Iteration2 functionality.
  if (sensor_proximity_.get_sp_activated()) {
    switch (sensor_proximity_.get_sensed_type()) {
      case kPlayer:
      case kSuperBot:
      case kRechargeStation:
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
      case kHomeBase:
      break;
      default:
      break;
    }
  } else {
    if (!get_distress())
      set_speed(get_max_speed());
  }
}

void MotionHandlerRobot::Reset(void) {
  set_max_speed(get_max_speed());
  set_speed(get_max_speed());
  set_heading_angle(270);
  set_freeze(false);
  set_distress(false);
}

NAMESPACE_END(csci3081);
