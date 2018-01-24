/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_H_
#define SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include "src/common.h"
#include "src/position.h"
#include "src/color.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class representing an entity within the arena. All entities
 * within the arena know how to :
 * 1. Update themselves each timestep (i.e. in accordance with current velocity
 *    and position).
 * 2. Reset themselves to a newly constructed state. This is so the user can
 *    click the reset button after completing a game and have things work as
 *    expected.
 *
 * Note that not all classes need to be able to do these two things.
 */
class ArenaEntity {
 public:
  ArenaEntity(double radius, const Position& pos,
              const csci3081::Color col) :
      radius_(radius), pos_(pos), color_(col), in_distress_(false) {}
  virtual ~ArenaEntity(void) {}

  /**
   * @brief Perform whatever updates are needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   */
  virtual void TimestepUpdate(__unused uint dt) {}

  /**
   * @brief Reset the entity to its newly constructed state.
   */
  virtual void Reset(void) {}

  /**
   * @brief Every entity needs to have a name.
   * This function is called in the graphics arena viewer,
   * so that the entity has its name on it.
   */
  virtual std::string name(void) const = 0;

  /*
  * @brief Setter for the Position.
  */
  void set_pos(const Position& pos) { pos_ = pos; }
  /*
  * @brief Getter for the position.
  */
  const Position& get_pos(void) const { return pos_; }

  /*
  * @brief Getter for the color.
  */
  const csci3081::Color& get_color(void) const { return color_; }
  /*
  * @brief Setter for the color.
  */
  void set_color(const csci3081::Color& color) { color_ = color; }

  /*
  * @brief pure virtual function that stores that mobile state of the
  * entities.
  */
  virtual bool is_mobile(void) = 0;

  /*
  * @brief Getter for the radius.
  */
  double get_radius(void) const { return radius_; }

  /**
   * @brief function return the distress state of the entity.
   * Distress state represent whether the entity is frozen by the palyer.
   * It could only be true for the Robot's when they register a collision
   * with the palyer
   */
  bool get_distress(void) {return in_distress_;}
  /**
   * @brief function to set the distress state of the entity.
   * Distress state represent whether the entity is frozen by the palyer.
   * It could only be true for the Robot's when they register a collision
   * with the palyer
   */
  void set_distress(bool d) { in_distress_ = d; }

  /**
   * @brief setters and getters for the entity_type of all the arena_entity
   */
  virtual entity_type get_entity_type(void) const = 0;
  /**
   * @brief setters and getters for the entity_type of all the arena_entity
   */
  virtual void set_entity_type(entity_type t) = 0;

 private:
  double radius_;
  Position pos_;
  csci3081::Color color_;
  bool in_distress_;
};

NAMESPACE_END(csci3081);

#endif /* SRC_ARENA_ENTITY_H_ */
