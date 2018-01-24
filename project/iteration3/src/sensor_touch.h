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
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;
class ArenaMobileEntity;

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

 /**
  * @brief Get the current point of contact from the sensor.
  */
  const Position get_point_of_contact() { return point_of_contact_; }
  /**
   * @brief Set the current point of contact from the sensor.
   */
  void set_point_of_contact(Position p) {
    point_of_contact_.x = p.x;
    point_of_contact_.y = p.y;
  }

  /**
   * @brief Get the current angle of contact
   */
  double get_angle_of_contact(void) { return angle_of_contact_; }
  /**
   * @brief Set the current angle of contact
   */
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

  /**
   * @brief This function returns the state of activation for the sensor
   * touch. This variable is updated in the Accept(EventBaseClass * e)
   * function accordingly.
   */
  bool get_st_activated(void) { return st_activated_;}
  /**
   * @brief This function sets the state of activation for the sensor
   * touch. This variable is updated in the Accept(EventBaseClass * e)
   * function accordingly.
   */
  void set_st_activated(bool s) { st_activated_ = s;}

  /**
   * @brief function returns the output member variable. Output
   * stores the state of the sensor touch such that 1 is on, 0 is
   * off.
   */
  int get_output(void) { return output_;}
  /**
   * @brief function sets the output member variable. Output
   * stores the state of the sensor touch such that 1 is on, 0 is
   * off.
   */
  void set_output(int o) { output_ = o;}

  /**
   * @brief Called in the arena to update the sensor_touch_ accordingly
   */
  void Accept(EventCollision * e);

  /**
   * @brief Reset the sensor_touch_ to its newly constructed state.
   */
  void Reset(void);

  /**
   * @brief This is the main function called in the arena to change the
   * state of the sensor_touch_. This function is the main function that
   * implements the observer pattern for the classes Arena and Sensor.
   * This function basically imitates the update_observer method from the
   * observer pattern.
   */
  void Accept(EventBaseClass* e);

 private:
  Position point_of_contact_;
  double angle_of_contact_;
  bool st_activated_;
  int output_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_TOUCH_H_
