/**
 * @file motion_handler_homebase.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_HOMEBASE_H_
#define SRC_MOTION_HANDLER_HOMEBASE_H_

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
 * @brief This class is responsible to implement the motion for the HomeBase.
 */
class MotionHandlerHomeBase : public MotionHandler {
 public:
  MotionHandlerHomeBase();

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

  // function that changes the heading angle randomly.
  void randomize_dir();

 private:
};

NAMESPACE_END(csci3081);

#endif   // SRC_MOTION_HANDLER_HOMEBASE_H_
