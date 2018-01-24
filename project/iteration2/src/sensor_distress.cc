/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor_distress.h"
#include "src/arena_entity.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorDistress::SensorDistress(double r) :
  range_(r),
  sd_activated_(false),
  output_(0),
  Sensor() {
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorDistress::Accept(EventBaseClass* e) {
  ArenaEntity* sensing = e->get_sensing();
  ArenaEntity* sensed = e->get_sensed();
  double dist = get_dist(sensing->get_pos().x, sensing->get_pos().y,
                        sensed->get_pos().x, sensed->get_pos().y);
  if (dist > sensing->get_radius() + sensed->get_radius() + range_) {
    set_sd_activated(get_sd_activated());
    set_output(get_output());
  } else {
    if (sensed->get_distress()) {
      set_sd_activated(true);
      set_output(dist);
    } else {
      set_sd_activated(get_sd_activated());
      set_output(get_output());
    }
  }
}

void SensorDistress::Reset(void) {
  activated_ = false;
  range_ = range_;
  set_sd_activated(false);
  set_output(0);
} /* reset() */

NAMESPACE_END(csci3081);
