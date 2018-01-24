/**
 * @file event_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_PROXIMITY_H_
#define SRC_EVENT_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/common.h"
#include "src/event_base_class.h"
#include "src/arena_entity.h"
// #include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief EventProximity class is responsible to hold information regarding the
 * entities involved in a proximity event. This information is then passed to the
 * proximity sensor of the entity so that it can set its member variables accordingly.
 *
 */
class EventProximity : public EventBaseClass {
 public:
  EventProximity();
  void EmitMessage(void);

  /**
   * Setters and Getters.
   */
  bool get_in_proximity() { return in_proximity_; }
  void set_in_proximity(bool c) { in_proximity_ = c; }

  double get_proximity() { return proximity_; }
  void set_proximity(double sp) { proximity_ = sp; }

  ArenaEntity* get_sensing() {return sensing_;}
  void set_sensing(ArenaEntity* ent) {sensing_ = ent;}

  ArenaEntity* get_sensed() {return sensed_;}
  void set_sensed(ArenaEntity* ent) {sensed_ = ent;}

 private:
  bool in_proximity_;
  double proximity_;
  ArenaEntity * sensing_;
  ArenaEntity * sensed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_PROXIMITY_H_
