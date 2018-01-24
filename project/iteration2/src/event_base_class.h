/**
 * @file event_base_class.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_BASE_CLASS_H_
#define SRC_EVENT_BASE_CLASS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class ArenaEntity;
/**
 * @brief The base event class from which all events should derive from.
 */
class EventBaseClass {
 public:
  EventBaseClass(void) {}
  virtual ~EventBaseClass(void) {}

  /**
   * @brief Each event, upon its firing, should emit a message to the user on
   * stdout saying what happened, in order to aid debugging.
   *
   */
  virtual void EmitMessage(void) = 0;

  /**
   * @brief Every event saves the two entities involved in the event.
   * These functions helps to override the getters for the two entities.
   * These two entities are the sensing (which sensed some other entity)
   * and the sensed (entity that is getting sensed by sensing)
   */
  virtual ArenaEntity* get_sensing() {}

  virtual ArenaEntity* get_sensed() {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_BASE_CLASS_H_
