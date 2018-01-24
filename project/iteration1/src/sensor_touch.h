/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_TOUCH_H_
#define SRC_SENSOR_TOUCH_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/position.h"
#include "src/sensor.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a touch sensor. Touch or "bump" sensors are
 * "active" when pressed. For our purposes, imagine a series of bump sensors
 * around the perimeter of the robot. A collision will activate the sensor
 * at a particular point of contact, which translates to an angle of contact
 *
 * Inherits from the Sensor base class which will act as a base class for other
 * types of sensor that we may add in other iterations. Sensor class is abstract
 * and this class implements all the abstract functions of the Sensor base class.
 */
class SensorTouch : public Sensor {
 public:
  SensorTouch();

    /**
   * @brief Compute a new reading based on the collision event.
   *
   * Note that collision events can report "no collision" which
   * will inactivate the sensor.
   *
   */

  void Accept(EventCollision * e);

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

 private:
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_TOUCH_H_
