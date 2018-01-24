/**
 * @file motion_handler_player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_PLAYER_H_
#define SRC_MOTION_HANDLER_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief MotionHandlerPlayer is a class that helps to implement the functionality
 * for the motion of the player. This class is responsible for taking care of
 * the change in motion of the player entity because of the users keypress events.
 */
class MotionHandlerPlayer : public MotionHandler {
 public:
  MotionHandlerPlayer(double max_s, int angle_d, double speed_d);

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

  // Getters and Setters for the member variables.
  double get_speed_delta() { return speed_delta_;}
  void set_speed_delta(double sp) {speed_delta_ = sp;}

  uint get_angle_delta() { return angle_delta_; }
  void set_angle_delta(uint dl) {angle_delta_ = dl;}

  /**
   * @brief Updates the speed to a different value based on the sp parameter. Used when handling up and down keypress.
   Also ensures that the speed doesnt go below 0.
   */
  void UpdateSpeed(double sp);

  /**
   * @brief Updates the angle based on the delta parameter. Used when handling left and right keypress.
   */
  void UpdateAngle(int delta);

 private:
  uint angle_delta_;
  double speed_delta_;
};

NAMESPACE_END(csci3081);

#endif   // SRC_MOTION_HANDLER_PLAYER_H_
