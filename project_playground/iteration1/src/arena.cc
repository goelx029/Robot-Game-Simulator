/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <simple_graphics/graphics_app.h>

#include "src/arena.h"
#include "src/robot.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  robot_(new Robot(&params->robot)),
  csci3081::GraphicsApp(180, 150, "Controls"),
  paused_(false),
  pause_btn_(nullptr),
  n_robots_(1),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  robot_->heading_angle(180);
  home_base_->heading_angle(215);
  entities_.push_back(robot_);
  mobile_entities_.push_back(robot_);
  mobile_entities_.push_back(home_base_);
  entities_.push_back(recharge_station_);

  entities_.push_back(home_base_);

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


void Arena::OnPlayAgainBtnPressed(void) {
  Reset();
  paused_ = false;
}

void Arena::OnQuitBtnPressed(void) {
  assert(0);
}

void Arena::AdvanceTime(void) {
  if (!paused_) {
    std::cout << "Advancing simulation time by 1 timestep\n";
    UpdateEntitiesTimestep();
  } else {
    // std::cout << "Simulation is Paused\n";
  }
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   */
  if (robot_->battery_level() <=0) {
    // printf("Battery Level = 0\n");
    paused_ = true;
    printf("YOU LOST\n");
    nanogui::FormHelper *gui = new nanogui::FormHelper(this);
    nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                         "YOU LOST");
    gui->addButton("PLAY AGAIN",
      std::bind(&Arena::OnPlayAgainBtnPressed, this));
    pause_btn_ = gui->addButton("QUIT!!!",
      std::bind(&Arena::OnQuitBtnPressed, this));

      performLayout();

    // printf("Do you want to play again? (1 for YES)\n");
    // std::cin>>x;
    // if(x!=1)
      // assert(0); /* not implemented yet */
    // Reset();
  }

  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;

  CheckForEntityCollision(robot_, home_base_, &ec, robot_->collision_delta());
  if (ec.collided()) {
      paused_ = true;
      printf("YOU WIN\n");
      nanogui::FormHelper *gui = new nanogui::FormHelper(this);
      nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                           "YOU WIN");
      gui->addButton("PLAY AGAIN",
        std::bind(&Arena::OnPlayAgainBtnPressed, this));
      pause_btn_ = gui->addButton("QUIT!!!",
        std::bind(&Arena::OnQuitBtnPressed, this));
        performLayout();
      // printf("Do you want to play again? (1 for YES)\n");
      // std::cin>>x;
      // if(x!=1)
        // assert(0); /* not implemented yet */
      // Reset();
  }

  CheckForEntityCollision(robot_, recharge_station_,
    &ec, robot_->collision_delta());
  if (ec.collided()) {
    EventRecharge er;
    robot_->Accept(&ec);
    robot_->Accept(&er);
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
    Position p_of_c = ec.point_of_contact();
    Position newpos = ent->get_pos();
    if (p_of_c.x == 0) {
      newpos = Position(ent->radius(), ent->get_pos().y);
      ent->set_pos(newpos);
    } else if (p_of_c.x == x_dim_) {
      newpos = Position(x_dim_-ent->radius(), ent->get_pos().y);
      ent->set_pos(newpos);
    } else if (p_of_c.y == 0) {
      newpos = Position(ent->get_pos().x, ent->radius());
      ent->set_pos(newpos);
    } else if (p_of_c.y == y_dim_) {
      newpos = Position(ent->get_pos().x, y_dim_-ent->radius());
      ent->set_pos(newpos);
    }


    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->collision_delta());
        if (ec.collided()) {
          if (ent == robot_ && entities_[i] != recharge_station_) {
            robot_->EventCmd(COM_SLOW_DOWN);
            robot_->update_charge(5.0);
            // robot_->Accept(&ec);
          }
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  if (ent->get_pos().x+ ent->radius() >= x_dim_) {
    // Right Wall
    event->collided(true);
    event->point_of_contact(Position(x_dim_, ent->get_pos().y));
    event->angle_of_contact(ent->heading_angle()-180);
    // move the robot manually
  } else if (ent->get_pos().x- ent->radius() <= 0) {
    // Left Wall
    event->collided(true);
    event->point_of_contact(Position(0, ent->get_pos().y));
    event->angle_of_contact(180+ent->heading_angle());
  } else if (ent->get_pos().y+ ent->radius() >= y_dim_) {
    // Bottom Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->angle_of_contact(ent->heading_angle());
  } else if (ent->get_pos().y - ent->radius() <= 0) {
    // Top Wall
    event->collided(true);
    event->point_of_contact(Position(ent->get_pos().x, 0));
    event->angle_of_contact(ent->heading_angle()+360);
  } else {
    event->collided(false);
    event->point_of_contact(ent->get_pos());
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
  if (dist > ent1->radius() + ent2->radius() + collision_delta) {
    event->collided(false);
    event->point_of_contact(ent1->get_pos());
  } else {
    // Populate the collision event.
    // Collided is true
    // Point of contact is point along perimeter of ent1
    // Angle of contact is angle to that point of contact

    //*******************************************************************************//
    // Added this //
    //*******************************************************************************//
    event->collided(true);
    double a_of_c = 0.0;
    if (ent2_x - ent1_x == 0) {
      a_of_c = M_PI + (ent1_y - ent2_y)*M_PI/2;
    } else {
      if (ent1_x > ent2_x)
        a_of_c = atan((ent1_y - ent2_y)/(ent2_x - ent1_x));
      else
        a_of_c = atan((ent1_y - ent2_y)/(ent2_x - ent1_x))+M_PI;
    }
    Position p_of_c;
    p_of_c.x = (ent2_x*ent1->radius()+ent1_x*ent2->radius())/(ent2_x+ent1_x);
    p_of_c.y = (ent2_y*ent1->radius()+ent1_y*ent2->radius())/(ent2_y+ent1_y);
    event->angle_of_contact(a_of_c*180/M_PI);
    event->point_of_contact(p_of_c);
    // Position newpos = Position(ent1_x,ent1_y);
    // robot_->pos(newpos);
    //*******************************************************************************//

    /// >>>>>>> FILL THIS IN
  }
} /* entities_have_collided() */

void Arena::Accept(__unused EventKeypress * e) {
  //*******************************************************************************//
  // Added this //
  //*******************************************************************************//
  robot_->EventCmd(e->get_key_cmd());
  //*******************************************************************************//
}

NAMESPACE_END(csci3081);
