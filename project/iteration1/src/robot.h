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
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/robot_battery.h"
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
    return "Robot" + std::to_string(id());
  }

  /**
   * @brief Update the charge of the battery of robot (decrease it) when robot collides with some entity or wall.
   */
  void update_charge(double dc) {battery_.decrease(-dc);}

 private:
  static unsigned int next_id_;

  int id_;
  double heading_angle_;  // contains original heading_angle_
  uint angle_delta_;  // contains original angle_delta_
  double max_speed_;  // contains original max_speed_
  double speed_delta_;  // contains original speed_delta_
  RobotBattery battery_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  Position orig_pos_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
