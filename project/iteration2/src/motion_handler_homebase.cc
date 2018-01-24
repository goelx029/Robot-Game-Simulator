/**
 * @file motion_handler_homebase.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_homebase.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
// seed used for rand_r to implement the random motion of home base.
thread_local unsigned int seed2 = time(NULL);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerHomeBase::MotionHandlerHomeBase() :
  MotionHandler() {
    set_max_speed(20);
    set_speed(get_max_speed());
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void MotionHandlerHomeBase::UpdateVelocity(SensorTouch st) {
  if (st.get_activated()) {
    set_heading_angle(-st.get_angle_of_contact());
  }
}

void MotionHandlerHomeBase::Reset(void) {
  set_max_speed(get_max_speed());
  set_speed(get_max_speed());
  set_heading_angle(90);
}

void MotionHandlerHomeBase::randomize_dir() {
  int c1 = rand_r(&seed2)%1000;
  int c2 = rand_r(&seed2)%100;
  double ang = get_heading_angle();
  if (c1 < c2) {
    int dir = (rand_r(&seed2)%9)-4;
    set_heading_angle(ang+(dir*33.33));
  }
}

NAMESPACE_END(csci3081);
