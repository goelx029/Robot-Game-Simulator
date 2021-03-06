/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Obstacle::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Obstacle::Obstacle(double radius, const Position& pos,
                                   const csci3081::Color col) :
    ArenaImmobileEntity(radius, pos, col),
    id_(-1) {
  id_ = next_id_++;
  set_distress(false);
}

NAMESPACE_END(csci3081);
