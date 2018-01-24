/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/robot.h"
#include "src/superbot.h"
#include "src/player.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"
#include "src/event_proximity.h"
#include "src/event_distress_call.h"
#include "src/event_type_emit.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  lost(false),
  win(false),
  n_robots_(params->n_robots),
  n_obstacles_(params->n_obstacles),
  paused_(false),
  player_(new Player(&params->player)),
  robot_(NULL),
  superbot_(new SuperBot(&params->superbot)),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  player_->set_heading_angle(0);
  home_base_->set_heading_angle(215);
  home_base_->set_speed(10);
  entities_.push_back(player_);
  entities_.push_back(superbot_);
  entities_.push_back(home_base_);
  mobile_entities_.push_back(player_);
  mobile_entities_.push_back(superbot_);
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);

  for (size_t i = 0; i < n_robots_; ++i) {
    robot_ = new Robot(&params->robots[i]);
    mobile_entities_.push_back(robot_);
    entities_.push_back(robot_);
  } /* for(i..) */

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::Reset(void) {
  lost = false;
  win = false;
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> res;
  for (auto ent : entities_) {
    Robot* r = dynamic_cast<Robot*>(ent);
    if (r) {
      res.push_back(r);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

void Arena::AdvanceTime(void) {
  if (!paused_) {
    // std::cout << "Advancing simulation time by 1 timestep\n";
    UpdateEntitiesTimestep();
  }
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First check whether we have won or lost
   * For winning check whether the remaining robots
   * are distress. For losing check whether all the
   * robot entity we had became superbot or not.
   */
  bool all_frozen = true;
  bool all_superbot = true;
  for (auto ent : mobile_entities_) {
    Robot* r = dynamic_cast<Robot*>(ent);
    if (r) {
      switch (r->get_entity_type()) {
        case kSuperBot:
        break;
        case kRobot:
        all_frozen = all_frozen && r->get_distress();
        all_superbot = false;
        break;
        default:
        break;
      }
    }
  }
  /*
   * If all the robots are frozen we win!
   */
  if (all_frozen) {
    printf("You have frozen every Robot\n");
    printf("YOU WIN\n");
    win = true;
  }
  /*
   * If all robots become superbot than lose.
   */
  if (all_superbot) {
    printf("Every Robot has become SuperBot\n");
    printf("YOU LOST\n");
    lost = true;
  }
  /*
   * Next, check if the robot has run out of battery
   */
  if (player_->get_battery_level() <=0) {
    printf("Battery Level = 0\n");
    printf("YOU LOST\n");
    lost = true;
  }
  /*
   * Next, update the sensors of all entities, according to their current
   * state with respect to all other entities in the arena
   */
  for (auto ent : mobile_entities_) {
    Sensor* st = ent->get_sensor_touch();
    Sensor* sp = ent->get_sensor_proximity();
    Sensor* sd = ent->get_sensor_distress();
    Sensor* senttyp = ent->get_sensor_entity_type();

    for (size_t i = 0; i < entities_.size(); ++i) {
      if (entities_[i] == ent) {
        continue;
      } else {
        EventCollision evc;
        EventProximity evpr;
        EventDistressCall evd;
        EventTypeEmit ete;

        evc.set_sensing(ent);
        evc.set_sensed(entities_[i]);
        evpr.set_sensing(ent);
        evpr.set_sensed(entities_[i]);
        evd.set_sensing(ent);
        evd.set_sensed(entities_[i]);
        ete.set_sensing(ent);
        ete.set_sensed(entities_[i]);

        st->Accept(&evc);
        sp->Accept(&evpr);
        sd->Accept(&evd);
        senttyp->Accept(&ete);
      }
    }  // for entities_
  }  // for mobile_entities_

  /*
   * Once the sensors of all entities have updated to a new state,
   * update the entities, which will use the information from the
   * updated sensors.
   */
  for (auto ent : mobile_entities_) {
    ent->TimestepUpdate(1);
  }

  /*
   * Need to reset the sensors for next cycle.
   * This is required because of the way in which
   * the sensors update themselves.
   */
  for (auto ent : mobile_entities_) {
    Sensor* st = ent->get_sensor_touch();
    Sensor* sp = ent->get_sensor_proximity();
    Sensor* sd = ent->get_sensor_distress();
    Sensor* senttyp = ent->get_sensor_entity_type();
    st->Reset();
    sp->Reset();
    sd->Reset();
    senttyp->Reset();
  }  // for mobile_entities_

  /*
   * Next, check if the player has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * player away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;
  double colldel = player_->get_collision_delta();

  CheckForEntityCollision(player_, home_base_, &ec, colldel);
  if (ec.get_collided()) {
    player_->Accept(&ec);  // Accept CollisionEvent
  }

  CheckForEntityCollision(player_, recharge_station_,
    &ec, player_->get_collision_delta());
  if (ec.get_collided()) {
    EventRecharge er;
    player_->Accept(&ec);  // Accept CollisionEvent
    player_->Accept(&er);  // Accept RechargeEvent
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    assert(ent->is_mobile());
    CheckForEntityOutOfBounds(ent, &ec);

    Position p_of_c = ec.get_point_of_contact();
    Position newpos = ent->get_pos();
    int del = ent->get_collision_delta();

    /*
     * To avoid the robot to stick to the walls and jitter
     * I use the Position from CollisionEvent to find the new
     * Position of the robot and hard code it to reach there
     */
    if (p_of_c.x == 0) {
      newpos = Position(ent->get_radius()+del, ent->get_pos().y);
      ent->set_pos(newpos);
    } else if (p_of_c.x == x_dim_) {
      newpos = Position(x_dim_-ent->get_radius()-del, ent->get_pos().y);
      ent->set_pos(newpos);
    } else if (p_of_c.y == 0) {
      newpos = Position(ent->get_pos().x, ent->get_radius()+del);
      ent->set_pos(newpos);
    } else if (p_of_c.y == y_dim_) {
      newpos = Position(ent->get_pos().x, y_dim_-ent->get_radius()-del);
      ent->set_pos(newpos);
    }

    /*
     * If the entity collided with the wall and it is
     * a robot then I update its speed to 70% original
     * speed and decrease charge by 5 points
     */

    if (ec.get_collided() && ent == player_) {
      player_->set_speed(player_->get_speed()*0.7);
      player_->update_charge(5.0);
    }


    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.get_collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        colldel = ent->get_collision_delta();
        CheckForEntityCollision(ent, entities_[i], &ec, colldel);
        /*
         * If the entity collided with a obstacle and it is
         * a robot then I update its speed to 70% original
         * speed and decrease charge by 5 points
         */
        if (ec.get_collided()) {
          if (ent == player_ && entities_[i] != recharge_station_) {
            player_->set_speed(player_->get_speed()*0.7);
            player_->update_charge(5.0);
          }
          /*
           * To avoid the robot to stick to the obstacles and stay there
           * till the battery drops which happens when the new speed due
           * to the collision is almost 0, I use the line external division ratio formula
           * to find the new center for my center.
           *
           *
           * Formula with two points (x1, y1) and (x2, y2), and find (xk, yk)
           * such that the ratio between (xk, yk) and (x1, y1) is k1 and
           * ratio between (xk, yk) and (x2, y2) is k2 is given as
           *
           * xk = (k1*x2 - k2*x1) / (k1-k2)
           * and similarly for y
           */
          p_of_c = ec.get_point_of_contact();
          int k1 = 2*ent->get_collision_delta();
          int k2 = k1+ent->get_radius();
          int total = k1-k2;
          newpos = Position(0.0, 0.0);
          newpos.x = ((k1*(p_of_c.x)-k2*(ent->get_pos().x))/total);
          newpos.y = ((k1*(p_of_c.y)-k2*(ent->get_pos().y))/total);
          ent->set_pos(newpos);
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  if (ent->get_pos().x+ ent->get_radius() >= x_dim_) {
    // Right Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(x_dim_, ent->get_pos().y));
    event->set_angle_of_contact(ent->get_heading_angle()-180);
  } else if (ent->get_pos().x- ent->get_radius() <= 0) {
    // Left Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(0, ent->get_pos().y));
    event->set_angle_of_contact(180+ent->get_heading_angle());
  } else if (ent->get_pos().y+ ent->get_radius() >= y_dim_) {
    // Bottom Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->set_angle_of_contact(ent->get_heading_angle());
  } else if (ent->get_pos().y - ent->get_radius() <= 0) {
    // Top Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(ent->get_pos().x, 0));
    event->set_angle_of_contact(ent->get_heading_angle()+360);
  } else {
    event->set_collided(false);
    event->set_point_of_contact(ent->get_pos());
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaEntity* const ent1,
  const ArenaEntity* const ent2,
  EventCollision * event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x;
  double ent1_y = ent1->get_pos().y;
  double ent2_x = ent2->get_pos().x;
  double ent2_y = ent2->get_pos().y;
  double dist = std::sqrt(
    std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->set_collided(false);
    event->set_point_of_contact(ent1->get_pos());
  } else {
    // Populate the collision event.
    // Collided is true
    // Point of contact is point along perimeter of ent1
    // Angle of contact is angle to that point of contact

    /**
     * First set CollisionEvent true
     * then I calculate the angle of contact using invere tangent
     * three cases
     *    1) if vertical collision - a_of_c = 90 or 270
     *    2) if collision from left a_of_c between -90 to 90 (atan range)
     *    3) if collision from right a_of_c between 90 to 270 (add 180)
     *
     * I find the point_of_contact using the line intersection formula
     */
    event->set_collided(true);
    double a_of_c = 0.0;
    if (ent2_x - ent1_x == 0) {
      if (ent1_y < ent2_y) {
        a_of_c = M_PI + M_PI/2;
      } else {
        a_of_c = M_PI - M_PI/2;
      }
    } else {
      if (ent1_x > ent2_x)
        a_of_c = atan((ent1_y - ent2_y)/(ent2_x - ent1_x));
      else
        a_of_c = atan((ent1_y - ent2_y)/(ent2_x - ent1_x))+M_PI;
    }

    /**
     * Finding the point of contact using the line ratio division theorem as follows.
     *
     * Formula with two points (x1, y1) and (x2, y2), and find (xk, yk)
     * such that the ratio between (xk, yk) and (x1, y1) is k1 and
     * ratio between (xk, yk) and (x2, y2) is k2 is given as
     *
     * xk = (k1*x2 + k2*x1) / (k1+k2)
     * and similarly for y
     */
    Position p_of_c;
    double total = ent1->get_radius()+ent2->get_radius();
    p_of_c.x = (ent2_x*(ent1->get_radius())+ent1_x*ent2->get_radius())/(total);
    p_of_c.y = (ent2_y*(ent1->get_radius())+ent1_y*ent2->get_radius())/(total);
    event->set_angle_of_contact(a_of_c*180/M_PI);
    event->set_point_of_contact(p_of_c);
  }
} /* entities_have_collided() */

void Arena::Accept(__unused EventKeypress * e) {
  player_->EventCmd(e->get_key_cmd());
}

NAMESPACE_END(csci3081);
