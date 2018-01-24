/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COLLISION_H_
#define SRC_EVENT_COLLISION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/common.h"
#include "src/event_base_class.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief A class that inherits from the EventBaseClass and handles all the collision
 * of entities in the arena. This class is responsible to handle collision of mobile
 * entity and walls, mobile entity with other mobile entity and mobile entity with
 * obstacles.
 *
 */
class EventCollision : public EventBaseClass {
 public:
  EventCollision();

  EventCollision(const EventCollision &);
  EventCollision& operator= (const EventCollision &);

  void EmitMessage(void);
  /**
   * @brief Setters and Getters.
   */
  bool get_collided() { return collided_; }
  /**
   * @brief Setters and Getters.
   */
  void set_collided(bool c) { collided_ = c; }

  /**
   * @brief Setters and Getters.
   */
  Position get_point_of_contact() { return point_of_contact_; }
  /**
   * @brief Setters and Getters.
   */
  void set_point_of_contact(Position p) { point_of_contact_ = p; }

  /**
   * @brief Setters and Getters.
   */
  double get_angle_of_contact() { return angle_of_contact_; }
  /**
   * @brief Setters and Getters.
   */
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

  /**
   * @brief Getter for the entity that is sensing.
   */
  ArenaEntity* get_sensing() {
    return sensing_;
  }
  /**
   * @brief Setter for the entity that is sensing.
   */
  void set_sensing(ArenaEntity* ent) {
    sensing_ = ent;
  }

  /**
   * @brief Getter for the entity being sensed.
   */
  ArenaEntity* get_sensed() {
    return sensed_;
  }
  /**
   * @brief Setter for the entity being sensed.
   */
  void set_sensed(ArenaEntity* ent) {
    sensed_ = ent;
  }

 private:
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
  ArenaEntity * sensing_;
  ArenaEntity * sensed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_COLLISION_H_
