/**
 * @file sensor.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Sensor::Sensor():
  activated_(false) {
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
double Sensor::get_dist(double sensing_x, double sensing_y,
  double sensed_x, double sensed_y) {
  double dist = std::sqrt(
    std::pow(sensed_x - sensing_x, 2) + std::pow(sensed_y - sensing_y, 2));
  return dist;
}

/**
 * for this function I hardcode all the casses, so that the function
 * returns the right value. I had to do this because the range of the
 * atan function is only between -PI/2 to PI/2.
 */
double Sensor::get_angle(double sensing_x, double sensing_y,
double sensed_x, double sensed_y) {
  double deltaY = sensed_y - sensing_y;
  double deltaX = sensing_x - sensed_x;
  double a_of_c = 0.0;

  if (sensed_x - sensing_x == 0) {
    if (sensing_y < sensed_y) {
      // sensing is present above the sensed.
      // arrow from sensing to sensed goes down
      // so angle is 90
      a_of_c = M_PI - M_PI/2;
    } else {
      // sensing is present below the sensed.
      // arrow from sensing to sensed goes up
      // so angle is 270
      a_of_c = M_PI + M_PI/2;
    }
  } else {
    if (sensing_x > sensed_x) {
      // sensing is present on the right of sensed
      if (sensing_y < sensed_y) {
        a_of_c = (-1*atan(fabs(deltaY)/fabs(deltaX))) + M_PI;
      } else {
        a_of_c = atan(fabs(deltaY)/fabs(deltaX)) + M_PI;
      }
    } else {
        // sensing is present on the left of sensed
        if (sensing_y < sensed_y) {
          a_of_c = atan(fabs(deltaY)/fabs(deltaX));
        } else {
          a_of_c = (-1)*atan(fabs(deltaY)/fabs(deltaX)) + 2*M_PI;
        }
    }
  }
  a_of_c = a_of_c*180/M_PI;
  return a_of_c;
}
NAMESPACE_END(csci3081);
