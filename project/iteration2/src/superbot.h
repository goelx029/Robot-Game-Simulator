/**
 * @file superbot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SUPERBOT_H_
#define SRC_SUPERBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/motion_handler_superbot.h"
#include "src/robot_motion_behavior.h"
#include "src/entity_type.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/event_command.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class that defines all the characterstics of the superbot
  * (entity) in arena. This class governs the features and methods of superbot.
  *
  * SuperBot class inherits from ArenaMobileEntity as it is a ArenaMobileEntity
  * with much more functionality. This class implements all the abstract functions
  * from ArenaMobileEntity class.
  *
  */
class SuperBot : public ArenaMobileEntity {
 public:
  explicit SuperBot(const struct robot_params* const params);


  /**
   * @brief Reset the superbot to its original configuration when the simulation started.
   */
  void Reset(void);


  /**
   * @brief Updates the superbot to a new state using motion_behavior_ and motion_handler_.
   */
  void TimestepUpdate(unsigned int dt);


  /**
   * @brief Accept the collision event and update the state of the robot.
   */
  void Accept(EventCollision * e);

  /**
   * @brief Accept the recharge event.
   * Need to implement this because it is part of the ArenaMobileEntity
   * class as a pure virtual function. This function does nothing
   * because the superbot does not have a battery.
   */
  void Accept(EventRecharge * e) {}

  /**
   * @brief getters and setters for different member variables.
   */
  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle(); }
  void set_heading_angle(double ang) { motion_handler_.set_heading_angle(ang); }

  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }

  double get_max_speed(void) { return motion_handler_.get_max_speed(); }

  /**
   * @brief getters and setters for freeze member variable. freeze
   * is a boolean variable that stores the current state of the entity
   * telling us whether the entity is frozen or not. In case of
   * superbot the freeze variable is never set to true for Iteration2.
   */
  bool get_freeze(void) { return motion_handler_.get_freeze(); }
  void set_freeze(bool f) { motion_handler_.set_freeze(f); }

  entity_type get_entity_type(void) const {return typ_;}
  void set_entity_type(entity_type t) {typ_ = t;}

  int id(void) const { return id_; }
  std::string name(void) const {
    return "SuperBot" + std::to_string(id());
  }

  /**
   * @brief Getters for all the different type of sensor that the
   * superbot contains.
   */
  SensorTouch* get_sensor_touch(void) {return &sensor_touch_;}

  SensorProximity* get_sensor_proximity(void) { return &sensor_proximity_;}

  SensorDistress* get_sensor_distress(void) { return &sensor_distress_;}

  SensorEntityType* get_sensor_entity_type(void) { return &sensor_entity_type_;}

  /**
   * @brief getters for the range and field of view of the sensor_proximity_.
   * This function is used to draw the sensor cone for the superbot.
   */
  const double get_sensor_proximity_range(void) const {
    return sensor_proximity_.get_range();
  }
  const double get_sensor_proximity_field_of_view(void) const {
    return sensor_proximity_.get_field_of_view();
  }

 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;  // contains original heading_angle_
  double max_speed_;  // contains original max_speed_
  entity_type typ_;
  MotionHandlerSuperBot motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorProximity sensor_proximity_;
  SensorDistress sensor_distress_;
  SensorEntityType sensor_entity_type_;
  Position orig_pos_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SUPERBOT_H_
