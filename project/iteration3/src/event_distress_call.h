/**
 * @file event_distress_call.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_DISTRESS_CALL_H_
#define SRC_EVENT_DISTRESS_CALL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/common.h"
#include "src/position.h"
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
 * @brief Event distress call class is responsible to handle the distress call
 * events from the arena. This class holds information about the two entities
 * involved in the distress call event and pass it to the sensor_distress so that
 * it can use this information and change its member variables accordingly.
 *
 */
class EventDistressCall : public EventBaseClass {
 public:
  EventDistressCall();
  EventDistressCall(const EventDistressCall &);
  EventDistressCall& operator= (const EventDistressCall &);

  void EmitMessage(void);

  /**
   * @brief Setters and Getters.
   */
  bool get_in_distress() { return in_distress_; }
  /**
   * @brief Setters and Getters.
   */
  void set_in_distress(bool c) { in_distress_ = c; }

  /**
   * @brief Setters and Getters.
   */
  Position get_sensed_pos() { return sensed_pos_; }
  /**
   * @brief Setters and Getters.
   */
  void set_sensed_pos(Position sp) { sensed_pos_ = sp; }


  /**
   * @brief Getter for the entity that is sensing.
   */
  ArenaEntity* get_sensing() {return sensing_;}
  /**
   * @brief Setter for the entity that is sensing.
   */
  void set_sensing(ArenaEntity* ent) {sensing_ = ent;}

  /**
   * @brief Getter for the entity being sensed.
   */
  ArenaEntity* get_sensed() {return sensed_;}
  /**
   * @brief Setter for the entity being sensed.
   */
  void set_sensed(ArenaEntity* ent) {sensed_ = ent;}

 private:
  bool in_distress_;
  Position sensed_pos_;
  ArenaEntity * sensing_;
  ArenaEntity * sensed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_DISTRESS_CALL_H_
