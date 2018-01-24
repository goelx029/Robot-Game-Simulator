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
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
  }
}

void RobotMotionHandler::UpdateSpeed(double sp) {
  // std::cout<<speed_<<"\n\n\n"<<sp<<"\n\n\n";
  if (speed_ + sp < 0)
    speed_ = 0;
  else if (speed_ + sp > max_speed_)
    speed_ = max_speed_;
  else
    speed_ += sp;
}

void RobotMotionHandler::UpdateAngle(int delta) {
  heading_angle_ += delta;
  if (heading_angle_ >= 360) {
    heading_angle_ = fmod(heading_angle_ , 360);
  } else if (heading_angle_ < 0) {
    heading_angle_ += 360;
  }
}

void RobotMotionHandler::Reset(void) {
  speed(2);
  heading_angle(-180);
  max_speed(5);
  angle_delta(30.0);
  speed_delta(1);
}

NAMESPACE_END(csci3081);
