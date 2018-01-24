/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/sensor_entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorEntityType::SensorEntityType(entity_type typ, double r) :
  Sensor(),
  senttyp_activated_(false),
  range_(r),
  dist_(2000),
  type_(typ) {
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorEntityType::Accept(EventBaseClass* e) {
  ArenaEntity* sensing = e->get_sensing();
  ArenaEntity* sensed = e->get_sensed();
  double dist = get_dist(sensing->get_pos().x, sensing->get_pos().y,
                        sensed->get_pos().x, sensed->get_pos().y);
  if (dist > sensing->get_radius() + sensed->get_radius() + range_) {
    set_senttyp_activated(get_senttyp_activated());
    set_sensed_type(get_sensed_type());
  } else {
    set_senttyp_activated(true);
    if (dist < get_senttyp_dist()) {
      set_sensed_type(sensed->get_entity_type());
      set_senttyp_dist(dist);
    } else {
      set_sensed_type(get_sensed_type());
      set_senttyp_dist(get_senttyp_dist());
    }
  }
}

void SensorEntityType::Reset(void) {
  set_senttyp_activated(false);
  set_range(get_range());
  set_sensed_type(kWall);
  set_senttyp_dist(2000);
}
NAMESPACE_END(csci3081);
