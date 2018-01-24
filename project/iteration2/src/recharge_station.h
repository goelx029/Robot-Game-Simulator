/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_RECHARGE_STATION_H_
#define SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for the recharge_station in the arena.
  *
  * RechargeStation inherits from Obstacle because it is just like an obstacle
  * with more features that help the robot recharge when it collides with it.
  *
  */
class RechargeStation: public Obstacle {
 public:
  RechargeStation(double radius, const Position& pos,
                  const csci3081::Color col) :
      Obstacle(radius, pos, col) {
        set_distress(false);
      }
  std::string name(void) const {
    return "Recharge Station";
  }

  entity_type get_entity_type(void) const { return kRechargeStation;}

  void set_entity_type(entity_type t) {}
};

NAMESPACE_END(csci3081);

#endif /* SRC_RECHARGE_STATION_H_ */
