/**
 * @file mobile_arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include "src/arena_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/entity_type.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class representing an entity within the arena which is mobile.
 * This includes robots and homebase.
 *
 * This class inherits from ArenaEntity because every ArenaMobileEntity is a
 * an ArenaEntity with extra characterstic of being able to move.
 *
 * As a ArenaMobileEntity we have to add many other characterstic which include
 * heading_angle, speed, collision_delta to be able to handle the movement of
 * entity in arena. We also need to implement the Accept functions that help to
 * accept recharge and collision events.
 *
 */
class ArenaMobileEntity : public ArenaEntity {
 public:
  ArenaMobileEntity(double radius, double collision_delta,
                    const Position& pos, const csci3081::Color col) :
      ArenaEntity(radius, pos, col),
      collision_delta_(collision_delta) {}
  /**
   * @brief always returns true becaue the entity is mobile
   */
  bool is_mobile(void) { return true; }

  /*
  * Setters and Getters for the member variables.
  */
  virtual double get_heading_angle(void) const = 0;
  /*
  * Setters and Getters for the member variables.
  */
  virtual void set_heading_angle(double heading_angle) = 0;

  /*
  * Setters and Getters for the member variables.
  */
  virtual double get_speed(void) = 0;
  /*
  * Setters and Getters for the member variables.
  */
  virtual void set_speed(double sp) = 0;

  /*
  * Setters and Getters for the member variables.
  */
  double get_collision_delta(void) const { return collision_delta_; }
  /**
   * @brief function that updates entity to its new state (because of dt change in time)
   */
  void TimestepUpdate(uint dt);
  /**
   * @brief Accept collision event and update to a new state representing the state after the collision
   */
  virtual void Accept(EventCollision * e) = 0;
  /**
   * @brief Accept recharge event and update to a new state representing the state after the recharge
   * Beware of using it when the entity is not a robot
   */
  virtual void Accept(EventRecharge * e) = 0;

  /**
   * @brief function that return the sensor_touch
   * for all the mobile entities.
   */
  virtual Sensor* get_sensor_touch(void) = 0;

  /**
   * @brief function that return the sensor_proximity
   * for all the mobile entities.
   */
  virtual Sensor* get_sensor_proximity(void) = 0;

  /**
   * @brief function that return the sensor_distress
   * for all the mobile entities.
   */
  virtual Sensor* get_sensor_distress(void) = 0;

  /**
   * @brief function that return the sensor_entity_type
   * for all the mobile entities.
   */
  virtual Sensor* get_sensor_entity_type(void) = 0;

 private:
  double collision_delta_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_MOBILE_ENTITY_H_
