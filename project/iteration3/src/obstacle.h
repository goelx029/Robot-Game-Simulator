/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_immobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for all the obstacles in the arena.
  *
  */
class Obstacle: public ArenaImmobileEntity {
 public:
  Obstacle(double radius, const Position& pos,
                   const csci3081::Color col);

  std::string name(void) const {
    return "Obstacle" + std::to_string(id_);
  }

  entity_type get_entity_type(void) const { return kObstacle;}

  void set_entity_type(entity_type t) {
    (void)t;
  }

 private:
  static uint next_id_;

  int id_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_OBSTACLE_H_ */
