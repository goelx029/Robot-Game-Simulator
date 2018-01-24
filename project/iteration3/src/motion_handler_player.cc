/**
 * @file motion_handler_player.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_player.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerPlayer::MotionHandlerPlayer(double max_s,
  int angle_d, double speed_d) :
  MotionHandler(),
  angle_delta_(angle_d),
  speed_delta_(speed_d) {
    set_max_speed(max_s);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerPlayer::AcceptCommand(enum event_commands cmd) {
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

void MotionHandlerPlayer::UpdateVelocity(SensorTouch st) {
  if (st.get_activated()) {
    set_heading_angle(-st.get_angle_of_contact());
  }
}

/*
 * UpdateSpeed function used in accept_command function
 * to change the speed by some defined delta (increase/decrease)
 * depending on the keypress
 *
 */
void MotionHandlerPlayer::UpdateSpeed(double sp) {
  if (get_speed() + sp < 0)
    set_speed(0);
  else if (get_speed() + sp > get_max_speed())
    set_speed(get_max_speed());
  else
    set_speed(get_speed() + sp);
}

/*
 * UpdateAngle function used in accept_command function
 * to change the heading_angle_ by some defined delta
 * in left or right direction depending on the keypress
 *
 */
void MotionHandlerPlayer::UpdateAngle(int delta) {
  set_heading_angle(get_heading_angle() + delta);
  if (get_heading_angle() >= 360) {
    set_heading_angle(fmod(get_heading_angle() , 360));
  } else if (get_heading_angle() < 0) {
    set_heading_angle(get_heading_angle() + 360);
  }
}

void MotionHandlerPlayer::Reset(void) {
  set_speed(1);
  set_heading_angle(0);
  set_max_speed(get_max_speed());
  set_angle_delta(get_angle_delta());
  set_speed_delta(get_speed_delta());
}

NAMESPACE_END(csci3081);
