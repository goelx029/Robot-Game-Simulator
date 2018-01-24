/**
 * @file motion_handler_robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

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
* @brief MotionHandlerRobot class is reponsible to implement the features
* of motion for the Robot entity. This class is responsible to change the
* features like heading_angle_ and speed according to the interaction of
* Robot with other entities in the arena.
*/
class MotionHandlerRobot : public MotionHandler {
 public:
  MotionHandlerRobot();

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void);

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);

  /**
   * @brief The main function that takes in all the data from the
   * updated sensors of the robot and uses this information
   * to update the motion of the robot entity accordingly.
   *
   * This function is the main function that is called in every entity
   * when it is updaing itself, the parameters are the Sensors of the
   * entity which provide the information to MotionHandler about the
   * most current state of the entity with respect to other entities.
   */
  void Update_All(SensorTouch sensor_touch_,
    SensorEntityType sensor_entity_type_,
    SensorProximity sensor_proximity_,
    SensorDistress sensor_distress_);

  /**
   * @brief Getters and Setters for the member variables.
   */
  bool get_freeze() { return freeze_; }
  void set_freeze(bool f) { freeze_ = f; }

  bool get_distress() { return distress_; }
  void set_distress(bool d) { distress_ = d; }


 private:
  bool distress_;
  bool freeze_;
};

NAMESPACE_END(csci3081);

#endif   /* SRC_MOTION_HANDLER_ROBOT_H_ */
