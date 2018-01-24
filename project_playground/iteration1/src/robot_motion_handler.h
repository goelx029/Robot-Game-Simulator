/**
 * @file actuator_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_MOTION_HANDLER_H_
#define SRC_ROBOT_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the robot's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * RobotMotionHandler manages the modification to the velocity based on
 * user input and collisions.
 * RobotMotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class RobotMotionHandler {
 public:
  RobotMotionHandler();

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void);

  /**
   * @brief Command from user keypress via the viewer.
   *
   * @param cmd The command.
   */
  void AcceptCommand(enum event_commands cmd);

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);

  double speed() { return speed_; }
  void speed(double sp) {
    if (sp > max_speed_)
      max_speed_ += sp;
    speed_ = sp;
  }

  double heading_angle() const { return heading_angle_;}
  void heading_angle(double ha) { heading_angle_ = ha; }

  double speed_delta() { return speed_delta_;}
  void speed_delta(double sp) {speed_delta_ = sp;}

  double max_speed() { return max_speed_; }
  void max_speed(double ms) { max_speed_ = ms; }

  uint angle_delta() { return angle_delta_; }
  void angle_delta(uint dl) {angle_delta_ = dl;}

  void UpdateSpeed(double sp);
  void UpdateAngle(int delta);

 private:
  double heading_angle_;
  uint angle_delta_;
  double speed_;
  double max_speed_;
  double speed_delta_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_ROBOT_MOTION_HANDLER_H_ */
