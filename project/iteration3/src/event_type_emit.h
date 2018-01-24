/**
 * @file event_type_emit.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_TYPE_EMIT_H_
#define SRC_EVENT_TYPE_EMIT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/common.h"
#include "src/position.h"
#include "src/event_base_class.h"
#include "src/arena_entity.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief EventTypeEmit class is reponsible to contain information about entities
 * that are involved in the distress event. This information is then used to
 * find the entity_type of the sensed arena_entity, and thus set the member variables
 * accordingly in the sensor_entity_type of the arena_mobile_entity.
 *
 */
class EventTypeEmit : public EventBaseClass {
 public:
  EventTypeEmit();
  EventTypeEmit(const EventTypeEmit &);
  EventTypeEmit& operator= (const EventTypeEmit &);
  void EmitMessage(void);

  /**
   * @brief Setters and Getters.
   */
  entity_type get_emit_type() { return emit_type_; }
  /**
   * @brief Setters and Getters.
   */
  void set_emit_type(entity_type c) { emit_type_ = c; }

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
  entity_type emit_type_;
  Position sensed_pos_;
  ArenaEntity * sensing_;
  ArenaEntity * sensed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_TYPE_EMIT_H_
