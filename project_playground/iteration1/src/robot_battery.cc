/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double RobotBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
  /* @todo deplete battery by some value based on movement and speed */


  //*******************************************************************************//
  // Added this //
  //*******************************************************************************//
  if (dt > 0) {
    double x_change = new_pos.x - old_pos.x;
    double y_change = new_pos.y - old_pos.y;
    double dist = std::sqrt(
      std::pow(x_change, 2) + std::pow(y_change, 2));
    charge_ = charge_ - (kLINEAR_SCALE_FACTOR*dist/dt) - kBASE_DEPLETION;
    if (charge_ < 0) {
      charge_ = 0;
    }
  }
  //*******************************************************************************//



  return charge_;
} /* deplete() */

void RobotBattery::Accept(__unused EventCollision * e) {
  /* @todo deplete battery by some value -- arbitrary selected for bumping */
  if (e->collided())
    decrease(-5.0);
}

NAMESPACE_END(csci3081);
