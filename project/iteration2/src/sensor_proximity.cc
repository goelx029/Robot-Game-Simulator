/**
 * @file sensor_proximity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/sensor_proximity.h"
#include "src/arena_entity.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorProximity::SensorProximity(double r, double fow) :
  range_(r),
  field_of_view_(fow),
  sp_activated_(false),
  output_(-1),
  angle_contact_(0.0),
  dist_(2000),
  type_(kWall),
  Sensor() {
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
bool SensorProximity::InRange(double sensor_lower, double sensor_upper,
  double sensed_lower, double sensed_upper) {
  if (sensor_lower > sensor_upper) {
    double temp = sensor_lower;
    sensor_lower = sensor_upper;
    sensor_upper = temp;
  }
  if (sensed_lower > sensed_upper) {
    double temp = sensed_lower;
    sensed_lower = sensed_upper;
    sensed_upper = sensed_lower;
  }
  if (sensed_lower >= sensor_lower &&
  sensed_lower <= sensor_upper) {
    return true;
  }
  if (sensed_upper >= sensor_lower &&
  sensed_upper <= sensor_upper) {
    return true;
  }
  return false;
}

void SensorProximity::Accept(EventBaseClass* e) {
  ArenaEntity* sensing = e->get_sensing();
  ArenaEntity* sensed = e->get_sensed();

  double dist = get_dist(sensing->get_pos().x, sensing->get_pos().y,
                        sensed->get_pos().x, sensed->get_pos().y);

  double a_of_c = get_angle(sensing->get_pos().x, sensing->get_pos().y,
                        sensed->get_pos().x, sensed->get_pos().y);

  double t_angle = fabs(atan(sensed->get_radius()/dist)*180/M_PI);

  double sensing_h_a_ =
    static_cast<ArenaMobileEntity*>(sensing)->get_heading_angle();

  if (sensing_h_a_ >= 360) {
    sensing_h_a_ = fmod(sensing_h_a_, 360);
  } else if (sensing_h_a_ < 0) {
    while (sensing_h_a_ < 0) {
      sensing_h_a_ += 360;
    }
    sensing_h_a_ = fmod(sensing_h_a_, 360);
  }
  static_cast<ArenaMobileEntity*>(sensing)->set_heading_angle(sensing_h_a_);

  /**
   * solving the edge case properly.
   */
  if (sensing_h_a_ <= field_of_view_) {
    if (a_of_c >= 180) {
      a_of_c -= 360;
    }
  } else if (sensing_h_a_ >= 360 - field_of_view_) {
    if (a_of_c <= 180) {
      a_of_c += 360;
    }
  }

  double sensor_lower = sensing_h_a_ - field_of_view_;
  double sensor_upper = sensing_h_a_ + field_of_view_;
  double sensed_lower = a_of_c - t_angle;
  double sensed_upper = a_of_c + t_angle;

  if ( InRange(sensor_lower, sensor_upper, sensed_lower, sensed_upper) &&
    dist <= range_ + sensing->get_radius() + sensed->get_radius()) {
      set_sp_activated(true);
      if (dist < get_prox_dist()) {
        set_output(dist);
        set_angle_contact(a_of_c);
        set_prox_dist(dist);
        set_sensed_type(sensed->get_entity_type());
      } else {
        set_output(get_output());
        set_angle_contact(get_angle_contact());
        set_prox_dist(get_prox_dist());
        set_sensed_type(get_sensed_type());
      }
    } else {
      set_sp_activated(get_sp_activated());
      set_output(get_output());
      set_angle_contact(get_angle_contact());
    }
}

void SensorProximity::Reset(void) {
  activated_ = false;
  range_ = range_;
  field_of_view_ = field_of_view_;
  set_sp_activated(false);
  set_output(-1);
  set_angle_contact(0.0);
  set_prox_dist(2000);
  set_sensed_type(kWall);
} /* reset() */

NAMESPACE_END(csci3081);
