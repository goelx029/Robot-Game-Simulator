/**
 * @file event_type_emit.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_type_emit.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
EventTypeEmit::EventTypeEmit() :
  sensed_pos_(0, 0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void EventTypeEmit::EmitMessage(void) {
  printf("Entity type Provided");
} /* EmitMessage() */

NAMESPACE_END(csci3081);
