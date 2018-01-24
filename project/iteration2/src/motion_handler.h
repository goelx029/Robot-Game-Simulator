/**
 * @file motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_H_
#define SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief Parent MotionHandler class which is reponsible to provide an interface
 * for other type of motion handler which are specific to the entities.
 */
class MotionHandler {
 public:
  MotionHandler();

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  virtual void Reset(void) = 0;

  /**
   * @brief Getters and Setters for the member variables.
   */
  double get_speed() { return speed_; }
  void set_speed(double sp) { speed_ = sp; }

  double get_heading_angle() const { return heading_angle_;}
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  double get_max_speed() { return max_speed_; }
  void set_max_speed(double ms) { max_speed_ = ms; }

  /**
   * @brief vitual methods helps me override the definitions
   * of the functions through the child classes. Needed because
   * my robot contains the pointer to MotionHandler and not an object
   * of type MotionHandlerRobot
   */
  virtual void Update_All(SensorTouch sensor_touch_,
    SensorEntityType sensor_entity_type_,
    SensorProximity sensor_proximity_,
    SensorDistress sensor_distress_) {}

  virtual void UpdateVelocity(SensorTouch st) {}

  virtual bool get_freeze() {}

  virtual void set_freeze(bool f) {}

  virtual bool get_distress() {}

  virtual void set_distress(bool d) {}

  virtual bool get_change_type() {return change_type_;}

  virtual void set_change_type(bool d) {change_type_ = d;}

 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
  bool change_type_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_MOTION_HANDLER_H_ */
