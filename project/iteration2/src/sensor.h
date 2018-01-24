/**
 * @file sensor.h
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
 * for different types of sensor in player and other mobile entities.
 *
 * It has many child classes which represent different type of sensors.
 * All of these child sensor classes are responsible for implemnting
 * the pure virtual functions.
 *
 */
class Sensor {
 public:
  Sensor() {
    activated_ = false;
  }

  virtual ~Sensor(void) {}

  virtual void Accept(EventBaseClass* e) = 0;

  /**
   * @brief Get the current activation reading from the sensor.
   */
  bool get_activated(void) { return activated_; }
  void set_activated(bool value) { activated_ = value; }

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  virtual void Reset(void) = 0;

  /**
   * @brief function that is called in the child sensor classes
   * to get the distance between the sensing and the sensed arena
   * entity.
   */
  double get_dist(double sensing_x, double sensing_y,
    double sensed_x, double sensed_y);

  /**
   * @brief function that is called in the child sensor classes
   * to get the angle between the sensing and sensed arena entity.
   * The angle that is returned is in degrees and measures the clockwise
   * angle from x-axis to line connecting the sensing and sensed.
   */
  double get_angle(double sensing_x, double sensing_y,
    double sensed_x, double sensed_y);

 protected:
  bool activated_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_H_
