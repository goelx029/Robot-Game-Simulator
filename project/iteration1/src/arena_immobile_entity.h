/**
 * @file arena_immobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_IMMOBILE_ENTITY_H_
#define SRC_ARENA_IMMOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

 /*******************************************************************************
  * Class Definitions
  ******************************************************************************/
 /**
  * @brief A base class representing an entity within the arena which is immobile.
  *
  * This class inherits from ArenaEntity because every ArenaImmobileEntity is a
  * a ArenaEntity with extra characterstic of not being able to move. Here the characterstic
  * of not being able to move is depcited through the function is_mobile(void) which
  * return false always.
  *
  */
class ArenaImmobileEntity : public ArenaEntity {
 public:
  ArenaImmobileEntity(double radius, const Position& pos,
                    const csci3081::Color col) :
      ArenaEntity(radius, pos, col) {}

  /**
   * @brief always returns false becaue the entity is immobile
   */
  bool is_mobile(void) { return false; }
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_IMMOBILE_ENTITY_H_ */
