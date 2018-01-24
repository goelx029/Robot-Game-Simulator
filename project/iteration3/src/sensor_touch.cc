/**
 * @file sensor_touch.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_touch.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorTouch::SensorTouch() :
  Sensor(),
  point_of_contact_(Position(0, 0)),
  angle_of_contact_(0),
  st_activated_(false),
  output_(0) {
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorTouch::Accept(EventCollision * e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->get_collided()) {
    activated_ = true;
    point_of_contact_ = e->get_point_of_contact();
    angle_of_contact_ = e->get_angle_of_contact();
  } else {
    activated_ = false;
  }
}

void SensorTouch::Accept(EventBaseClass* e) {
  ArenaEntity* sensing = e->get_sensing();
  ArenaEntity* sensed = e->get_sensed();
  double dist = get_dist(sensing->get_pos().x, sensing->get_pos().y,
                        sensed->get_pos().x, sensed->get_pos().y);
  if (dist > sensing->get_radius() + sensed->get_radius() +
      static_cast<ArenaMobileEntity*>(sensing)->get_collision_delta() * 3) {
    set_st_activated(get_st_activated());
    set_output(get_output());
  } else {
    set_st_activated(true);
    set_output(1);
  }
}

void SensorTouch::Reset(void) {
  activated_ = false;
  point_of_contact_ = Position(0.0, 0.0);
  angle_of_contact_ = 0.0;
  set_st_activated(false);
  set_output(0);
} /* reset() */

NAMESPACE_END(csci3081);
