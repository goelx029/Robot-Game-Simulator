/**
 * @file sensor_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_DISTRESS_H_
#define SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/sensor.h"
#include "src/event_base_class.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;
class Sensor;

/**
 * @brief SensorDistress class is responsible to check whether there is a sensed
 * entity in a range of the sensing entity which is in distress. An entity is
 * distress only if it is frozen. It means that only a robot can be sensed to be
 * in distressed. This information from the SensorDistress is used to check whether
 * the entity should avoid the entity or not.
 */
class SensorDistress : public Sensor {
 public:
  explicit SensorDistress(double r = 0.0);

  /**
   * @brief Setter for range of the sensor.
   */
  void set_range(double r) {range_ = r;}
  /**
   * @brief Getter for range of the sensor.
   */
  double get_range() {return range_;}

  /**
   * @brief Getter for activation state of the sensor.
   */
  bool get_sd_activated(void) { return sd_activated_;}
  /**
   * @brief Setter for activation state of the sensor.
   */
  void set_sd_activated(bool s) { sd_activated_ = s;}

  /**
   * @brief Getter for output (distance to sensed).
   */
  int get_output(void) { return output_;}
  /**
   * @brief Setter for output (distance to sensed).
   */
  void set_output(int o) { output_ = o;}

   /**
   * @brief Reset the distress sensor to its newly constructed state.
   */
  void Reset(void);

  /**
   * @brief This is the main function called in the arena to change the
   * state of the sensor_distress_. This function is the main function that
   * implements the observer pattern for the classes Arena and Sensor.
   * This function basically imitates the update_observer method from the
   * observer pattern.
   */
  void Accept(EventBaseClass* e);

 private:
  bool sd_activated_;
  int output_;
  double range_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_DISTRESS_H_
