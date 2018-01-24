/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_PROXIMITY_H_
#define SRC_SENSOR_PROXIMITY_H_

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
 * @brief SensorProximity class checks whether there is any entity
 * in a certain field of view in front of it upto some distance.
 * This class helps to avoid obstacles that are in a entities field of
 * view by updating the heading angle and speed of the motionhandler,
 * of entity accordingly.
 */
class SensorProximity : public Sensor {
 public:
  explicit SensorProximity(double r = 0.0, double fow = 0.0);

  /**
   * @brief Setter for range of the sensor.
   */
  void set_range(double r) {range_ = r;}
  /**
   * @brief Getter for range of the sensor.
   */
  double get_range() const {return range_;}

  /**
   * @brief Setter for field_of_view_ of the sensor.
   */
  void set_field_of_view(double fow) {field_of_view_ = fow;}
  /**
   * @brief Getter for field_of_view_ of the sensor.
   */
  double get_field_of_view() const {return field_of_view_;}

  /**
   * @brief This function returns the state of activation for the sensor
   * proximity. This variable is updated in the Accept(EventBaseClass * e)
   * function accordingly.
   */
  bool get_sp_activated(void) { return sp_activated_;}
  /**
   * @brief This function sets the state of activation for the sensor
   * proximity. This variable is updated in the Accept(EventBaseClass * e)
   * function accordingly.
   */
  void set_sp_activated(bool s) { sp_activated_ = s;}

  /**
   * @brief function returns the output member variable. Output
   * stores the state of the sensor proximity such that -1 is
   * off and if the sensor_proximity is on it stores the distance.
   */
  int get_output(void) { return output_;}
  /**
   * @brief function sets the output member variable. Output
   * stores the state of the sensor proximity such that -1 is
   * off and if the sensor_proximity is on it stores the distance.
   */
  void set_output(int o) { output_ = o;}

  /**
   * @brief getters and setters of angle of contact of the
   * sensing with the sensed.
   */
  double get_angle_contact(void) { return angle_contact_; }
  /**
   * @brief getters and setters of angle of contact of the
   * sensing with the sensed.
   */
  void set_angle_contact(double a) { angle_contact_ = a; }

  /**
   * @brief getters and setters of sensed entity_type which
   * is in proximity.
   */
  entity_type get_sensed_type(void) { return type_; }
  /**
   * @brief getters and setters of sensed entity_type which
   * is in proximity.
   */
  void set_sensed_type(entity_type t) { type_ = t; }

  /**
   * @brief Stores the dist between the sensing and sensed of the
   * closest entity to sensing if in proximity.
   */
  double get_prox_dist(void) { return dist_; }
  void set_prox_dist(double d) { dist_ = d; }

  /**
   * @brief function that calculates whether some sensed entity
   * is in proximity based on the field_of_view_.
   */
  bool InRange(double sensor_lower, double sensor_upper,
               double sensed_lower, double sensed_upper);

   /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

  /**
   * @brief This is the main function called in the arena to change the
   * state of the sensor_proximity_. This function is the main function that
   * implements the observer pattern for the classes Arena and Sensor.
   * This function basically imitates the update_observer method from the
   * observer pattern.
   */
  void Accept(EventBaseClass* e);

 private:
  double range_;
  double field_of_view_;
  bool sp_activated_;
  int output_;
  double angle_contact_;
  double dist_;
  entity_type type_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_SENSOR_PROXIMITY_H_
