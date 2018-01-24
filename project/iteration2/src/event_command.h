/**
 * @file actuator_cmd_event.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COMMAND_H_
#define SRC_EVENT_COMMAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The event command class which is reponsible to handle all the user
 * command events and convert them to the right cmd keypress (up, down, left, right).
 */
class EventCommand : public EventBaseClass {
 public:
  explicit EventCommand(enum event_commands cmd) : cmd_(cmd) {}

  void EmitMessage(void) { printf("Motion cmd %d received\n", cmd_); }

  /**
   * @brief returns the cmd_ which depicts the arrow_key_press from the user
   */
  enum event_commands cmd(void) const { return cmd_; }

 private:
  enum event_commands cmd_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_COMMAND_H_
