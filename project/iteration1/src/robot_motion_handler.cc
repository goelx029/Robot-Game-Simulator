/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(-180),
  speed_(0),
  max_speed_(5),
  angle_delta_(30),
  speed_delta_(1) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  /**
   * This switch statement Implements the keypress by updating
   * either the speed or the heading_angle depending on the keypress.
   */
  switch (cmd) {
  case COM_TURN_LEFT: UpdateAngle(-angle_delta_);
  break;
  case COM_TURN_RIGHT: UpdateAngle(angle_delta_);
  break;
  case COM_SPEED_UP: UpdateSpeed(speed_delta_);
  break;
  case COM_SLOW_DOWN: UpdateSpeed(-speed_delta_);
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.get_activated()) {
    heading_angle_ = - st.get_angle_of_contact();
  }
}

/*
 * UpdateSpeed function used in accept_command function
 * to change the speed by some defined delta (increase/decrease)
 * depending on the keypress
 *
 */
void RobotMotionHandler::UpdateSpeed(double sp) {
  if (speed_ + sp < 0)
    speed_ = 0;
  else if (speed_ + sp > max_speed_)
    speed_ = max_speed_;
  else
    speed_ += sp;
}

/*
 * UpdateAngle function used in accept_command function
 * to change the heading_angle_ by some defined delta
 * in left or right direction depending on the keypress
 *
 */
void RobotMotionHandler::UpdateAngle(int delta) {
  heading_angle_ += delta;
  if (heading_angle_ >= 360) {
    heading_angle_ = fmod(heading_angle_ , 360);
  } else if (heading_angle_ < 0) {
    heading_angle_ += 360;
  }
}

void RobotMotionHandler::Reset(void) {
  set_speed(2);
  set_heading_angle(180);
  set_max_speed(5);
  set_angle_delta(30.0);
  set_speed_delta(1);
}

NAMESPACE_END(csci3081);
