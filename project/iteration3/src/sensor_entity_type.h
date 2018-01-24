/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_ENTITY_TYPE_H_
#define SRC_SENSOR_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class Sensor;

/**
 * @brief SensorEntityType stores the entity_type of the sensed entity, which
 * is closest to the sensing entity. It has a default value of kWall which shows
 * that no other entity is present within a defined range of the sensing entity.
 * This class is used to get the entity_type of the sensed entity when the sensing
 * entity registers a collision so that the sensing entity can update itself.

 */
class SensorEntityType : public Sensor {
 public:
  explicit SensorEntityType(entity_type typ = kWall, double r = 30.0);

  /**
   * @brief Getter for entity type of the sensed entity.
   */
  entity_type get_sensed_type() {return type_;}
  /**
   * @brief Setter for entity type of the sensed entity.
   */
  void set_sensed_type(entity_type e) {type_ = e;}

  /**
   * @brief Getter for range of the sensor.
   */
  double get_range(void) { return range_; }
  /**
   * @brief Setter for range of the sensor.
   */
  void set_range(double r) { range_ = r; }

  /**
   * @brief Getter for activation state of the sensor.
   */
  bool get_senttyp_activated(void) { return senttyp_activated_;}
  /**
   * @brief Setter for activation state of the sensor.
   */
  void set_senttyp_activated(bool s) { senttyp_activated_ = s;}

  /**
   * @brief Getter for output (distance to sensed).
   */
  double get_senttyp_dist(void) { return dist_; }
  /**
   * @brief Setter for output (distance to sensed).
   */
  void set_senttyp_dist(double d) { dist_ = d; }

  /**
   * @brief This is the main function called in the arena to change the
   * state of the sensor_entity_type. This function is the main function that
   * implements the observer pattern for the classes Arena and Sensor.
   * This function basically imitates the update_observer method from the
   * observer pattern.
   */
  void Accept(EventBaseClass* e);

  /**
   * @brief Reset the sensor_entity_type_ to its newly constructed state.
   */
  void Reset(void);

 private:
  double range_;
  bool senttyp_activated_;
  entity_type type_;
  double dist_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_ENTITY_TYPE_H_
