/**
 * @file entity_type.h
 *
 * @copyright 2017, All rights reserved.
 *
 */

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
 /**
  * @brief enum that contains the name of different type of entities present in
  * the arena. kWall is used as a default type in sensors which denote that the
  * entity is in no harm.
  */
enum entity_type {
  kPlayer = 0,
  kSuperBot = 1,
  kRobot = 2,
  kHomeBase = 3,
  kRechargeStation = 4,
  kObstacle = 5,
  kWall = 6
};
NAMESPACE_END(csci3081);

#endif /* SRC_ENTITY_TYPE_H_ */
