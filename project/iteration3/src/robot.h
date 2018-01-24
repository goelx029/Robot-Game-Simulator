/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/motion_handler_robot.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"
#include "src/robot_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/event_command.h"
#include "src/motion_handler_superbot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class that defines all the characterstics of the robot (entity)
  * in arena. This class governs the features and methods of robot.
  *
  * Robot class inherits from ArenaMobileEntity as it is a ArenaMobileEntity
  * with much more functionality. This class implements all the abstract functions
  * from ArenaMobileEntity class.
  *
  */
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);

  Robot(const Robot &);
  Robot& operator= (const Robot &);


  /**
   * @brief Reset the robot to its original configuration when the simulation started.
   */
  void Reset(void);


  /**
   * @brief Updates the robot to a new state using motion_behavior_ and motion_handler_.
   */
  void TimestepUpdate(unsigned int dt);


  /**
   * @brief Accept the collision event and update the state of the robot.
   */
  void Accept(EventCollision * e);

  /**
   * @brief Accept the recharge event and update the state of the robot.
   * This function is blank because the robot doesnt have a battery.
   */
  void Accept(EventRecharge * e) {
    (void)e;
  }

  /**
   * @brief Getters and Setters for different member variables.
   */
  double get_heading_angle(void) const {
    return motion_handler_->get_heading_angle(); }
  void set_heading_angle(double ang) {
    motion_handler_->set_heading_angle(ang); }

  double get_speed(void) { return motion_handler_->get_speed(); }
  void set_speed(double sp) { motion_handler_->set_speed(sp); }

  double get_max_speed(void) { return motion_handler_->get_max_speed(); }

  bool get_freeze(void) { return motion_handler_->get_freeze(); }
  void set_freeze(bool f) { motion_handler_->set_freeze(f); }


  int id(void) const { return id_; }
  std::string name(void) const {
    return name_;
  }

  entity_type get_entity_type(void) const {return typ_;}

  void set_entity_type(entity_type t) {typ_ = t;}

  /**
   * @brief Getters for all the different type of sensor that the
   * robot contains.
   */
  SensorTouch* get_sensor_touch(void) {return &sensor_touch_;}

  SensorProximity* get_sensor_proximity(void) { return &sensor_proximity_;}

  SensorDistress* get_sensor_distress(void) { return &sensor_distress_;}

  SensorEntityType* get_sensor_entity_type(void) { return &sensor_entity_type_;}

  /**
   * @brief getters for the range and field of view of the sensor_proximity_.
   * This function is used to draw the sensor cone for the robot.
   */
  double get_sensor_proximity_range(void) const {
    return sensor_proximity_.get_range();
  }
  double get_sensor_proximity_field_of_view(void) const {
    return sensor_proximity_.get_field_of_view();
  }

 private:
  static unsigned int next_id_;

  csci3081::Color orig_color_;
  csci3081::Color superbot_color_;
  entity_type typ_;
  double heading_angle_;  // contains original heading_angle_
  double orig_max_speed_;  // contains original max_speed_
  double superbot_max_speed_;   // contains max_speed_ of superbot
  Position orig_pos_;
  /**
   * @brief motion_handler_ is a pointer to MotionHandler base class
   * so that I can implement the strategy pattern to change the
   * behavior of the robot.
   */
  MotionHandler* motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorProximity sensor_proximity_;
  SensorDistress sensor_distress_;
  SensorEntityType sensor_entity_type_;
  double orig_range_;
  double orig_field_of_view_;
  double superbot_sp_range_;
  double superbot_sp_field_of_view_;
  std::string name_;
  int id_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
