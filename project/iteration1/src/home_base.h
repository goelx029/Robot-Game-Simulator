/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_H_
#define SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/arena_mobile_entity.h"
#include "src/event_collision.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for the home base entity in arena.
 *
 * Implements all the function from ArenaMobileEntity.
 * Has it's own RobotMotionHandler, RobotMotionBehavior and SensorTouch
 * to help implement collisions with walls and other entities in the arena.
 */
class HomeBase: public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  std::string name(void) const { return "Home Base"; }

  // Setters and Getters.
  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle();
  }

  void set_heading_angle(double ha) {
    motion_handler_.set_heading_angle(ha);
  }

  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }

  /**
   * @brief change the state of home base to new state when it collides with entities or wall
   */
  void Accept(EventCollision * e);

  /**
   * @brief Because the HomeBase doesnt have a battery this is blank.
   * Need to implement this because this function is abstract in ArenaMobileEntity.
   */
  void Accept(EventRecharge * e) {}

  /**
   * @brief update the state of the home base based using motion_behavior_ and motion_handler_.
   Implement the random motion of the home_base using the rand_r function to change directions at random times.
   */
  void TimestepUpdate(uint dt);

  /**
   * @brief reset the state of home base to its original state
   */
  void Reset(void);

 private:
  static unsigned int next_id_;

  int id_;
  Position orig_pos_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_HOME_BASE_H_
