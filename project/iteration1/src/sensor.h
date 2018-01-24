/**
 * @file sensor_touch.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/position.h"
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
 * @brief A base Sensor Class that will act as a parent class
 * for different types of sensor in robot and other mobile entities.
 *
 * Will have many child classes when add different types of sensors
 * in further iterations.
 *
 */
class Sensor {
 public:
  Sensor() {
    activated_ = false;
    point_of_contact_ = Position(0, 0);
    angle_of_contact_ = 0;
  }

  /**
   * @brief Get the current activation reading from the sensor.
   */
  bool get_activated(void) { return activated_; }
  void set_activated(bool value) { activated_ = value; }

  /**
   * @brief Get the current point of contact from the sensor.
   */
  Position get_point_of_contact() { return point_of_contact_; }
  void set_point_of_contact(Position p) {
  point_of_contact_.x = p.x;
  point_of_contact_.y = p.y;
  }

  double get_angle_of_contact(void) { return angle_of_contact_; }
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

  /**
   * @brief Compute a new reading based on the collision event.
   *
   * Note that collision events can report "no collision" which
   * will inactivate the sensor.
   *
   */

  virtual void Accept(EventCollision * e) = 0;

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  virtual void Reset(void) = 0;

 protected:
  bool activated_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_H_
