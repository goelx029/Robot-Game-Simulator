/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/motion_handler_player.h"
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
#include "src/player_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Player Class which is responsible to simulate the player entity
  * in the arena. This class is responsible to handle the user commands
  * to increase, decrease speed and change the heading angle. This class
  * implements every characterstic of the Player.
  *
  */
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);

  /**
   * @brief Reset the robot's battery so that it contains full charge.
   */
  void ResetBattery(void);

  /**
   * @brief Reset the robot to its original configuration when the simulation started.
   */
  void Reset(void);
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }

  /**
   * @brief Updates the robot to a new state using motion_behavior_ and motion_handler_.
   */
  void TimestepUpdate(unsigned int dt);

  /**
   * @brief Accept the Recharge Event and thus update the battery accordingly
   */
  void Accept(EventRecharge * e);

  /**
   * @brief Accept the collision event and update the state of the robot.
   */
  void Accept(EventCollision * e);

  /**
   * @brief Accept the Command event (user commands in form of keypress) to update the state of the robot.
   */
  void Accept(EventCommand * e);

  /**
   * @brief Use the cmd (user commands in form of keypress) to update the state of the robot.
   */
  void EventCmd(enum event_commands cmd);

  /**
   * Setters and Getters.
   */
  double get_battery_level(void) { return battery_.get_level(); }

  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle();
  }

  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }

  double get_speed(void) { return motion_handler_.get_speed(); }

  double get_chargelevel(void) const {return battery_.get_level();}

  double get_maxcharge(void) const {return battery_.get_maxcharge();}

  void set_speed(double sp) { motion_handler_.set_speed(sp); }

  int id(void) const { return id_; }
  std::string name(void) const {
    return "Player" + std::to_string(id());
  }

  /**
   * @brief Update the charge of the battery of robot (decrease it) when robot collides with some entity or wall.
   */
  void update_charge(double dc) {battery_.decrease(-dc);}

  entity_type get_entity_type(void) const {return typ_;}

  void set_entity_type(entity_type t) {typ_ = t;}

  /**
   * @brief Getters for all the different type of sensor that the
   * player contains.
   */
  SensorTouch* get_sensor_touch(void) {return &sensor_touch_;}

  SensorProximity* get_sensor_proximity(void) { return &sensor_proximity_;}

  SensorDistress* get_sensor_distress(void) { return &sensor_distress_;}

  SensorEntityType* get_sensor_entity_type(void) { return &sensor_entity_type_;}

  /**
   * @brief getters for the range and field of view of the sensor_proximity_.
   * This function is used to draw the sensor cone for the player.
   */
  double get_sensor_proximity_range(void) const {
    return sensor_proximity_.get_range();
  }
  /**
   * @brief getters for the range and field of view of the sensor_proximity_.
   * This function is used to draw the sensor cone for the player.
   */
  double get_sensor_proximity_field_of_view(void) const {
    return sensor_proximity_.get_field_of_view();
  }

 private:
  static unsigned int next_id_;
  static unsigned int time_step_;

  RobotBattery battery_;
  entity_type typ_;
  double heading_angle_;  // contains original heading_angle_
  uint angle_delta_;  // contains original angle_delta_
  double max_speed_;  // contains original max_speed_
  double speed_delta_;  // contains original speed_delta_
  Position orig_pos_;
  MotionHandlerPlayer motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorProximity sensor_proximity_;
  SensorDistress sensor_distress_;
  SensorEntityType sensor_entity_type_;
  bool super_bot_col_;
  int id_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_PLAYER_H_
