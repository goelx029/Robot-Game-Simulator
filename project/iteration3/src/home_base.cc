/**
 * @file home_base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/home_base.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint HomeBase::next_id_ = 0;
// seed used for rand_r to implement the random motion of home base.
thread_local unsigned int seed = time(NULL);
/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
HomeBase::HomeBase(const struct home_base_params* const params) :
ArenaMobileEntity(params->radius, 1,
  params->pos, params->color),
  typ_(kHomeBase),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  sensor_proximity_(30.0, 45.0),
  sensor_distress_(30.0),
  sensor_entity_type_(kHomeBase, 30.0),
  orig_pos_(params->pos),
  id_(-1) {
  motion_handler_.set_heading_angle(215);
  motion_handler_.set_speed(20);
  id_ = next_id_++;
  set_distress(false);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void HomeBase::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void HomeBase::TimestepUpdate(uint dt) {
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  /*
   * implementing the random motion of homebase
   * to change directions at random time
   */
  int c1 = rand_r(&seed)%1000;
  int c2 = rand_r(&seed)%100;
  double ang = motion_handler_.get_heading_angle();
  if (c1 < c2) {
    int dir = (rand_r(&seed)%9)-4;
    motion_handler_.set_heading_angle(ang+(dir*33.33));
  }
  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
} /* TimestepUpdate() */

void HomeBase::Reset(void) {
  set_pos(orig_pos_);
  motion_handler_.Reset();
  motion_handler_.set_speed(20);
  motion_handler_.set_heading_angle(215);
  sensor_touch_.Reset();
} /* Reset() */

NAMESPACE_END(csci3081);
