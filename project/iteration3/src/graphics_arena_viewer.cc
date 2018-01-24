/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>

#include "src/robot.h"
#include "src/player.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(params->x_dim, params->y_dim, "Robot Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(10, 10),
                                                       "Simulation Controls");
  gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    last_dt += dt;
    while (last_dt > 0.05) {
      arena_->AdvanceTime();
      last_dt -= 0.05;
    }
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  paused_ = false;
  arena_->Reset();
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(int x, int y) {
  std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseDown(int x, int y) {
  std::cout << "Left mouse button DOWN (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseUp(int x, int y) {
  std::cout << "Left mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnRightMouseDown(int x, int y) {
  std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

void GraphicsArenaViewer::OnRightMouseUp(int x, int y) {
  std::cout << "Right mouse button UP (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnKeyDown(const char *c, int modifiers) {
  std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnKeyUp(const char *c, int modifiers) {
  std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, int scancode,
  int modifiers) {
  EventKeypress e(key);
  arena_->Accept(&e);
  std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyUp(int key, int scancode, int modifiers) {
  std::cout << "Special Key UP key=" << key << " scancode=" << scancode
            << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
void GraphicsArenaViewer::DrawPlayer(NVGcontext *ctx,
  const Player* const player) {
  // outer bar that stays same of black color
  nvgBeginPath(ctx);
  nvgRect(ctx, 1024 - 2*player->get_maxcharge(),
    0, 2*player->get_maxcharge(), 50);
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(0),
                            static_cast<int>(0),
                            static_cast<int>(0),
                            125));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // Making the inner bar that decrease to represent battery
  double charge_ratio = 255*player->get_chargelevel()/player->get_maxcharge();
  nvgBeginPath(ctx);
  nvgRect(ctx, 1024 - 2*player->get_maxcharge(),
    0, 2*player->get_chargelevel(), 49);
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(255-charge_ratio),
                            static_cast<int>(charge_ratio),
                            static_cast<int>(0),
                            200));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  std::string st = "BATTERY LEVEL";
  nvgFillColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgText(ctx, 925, 60,
          st.c_str(), NULL);
  // translate and rotate all graphics calls that follow so that they are
  // centered, at the position and heading for this player
  nvgSave(ctx);
  nvgTranslate(ctx, player->get_pos().x, player->get_pos().y);
  nvgRotate(ctx, player->get_heading_angle());

  // player's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, player->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(player->get_color().r),
                            static_cast<int>(player->get_color().g),
                            static_cast<int>(player->get_color().b),
                            static_cast<int>(player->get_color().a)));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // player id text label
  nvgSave(ctx);
  nvgRotate(ctx, M_PI / 2.0);
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, 0.0, 10.0, player->name().c_str(), NULL);
  nvgRestore(ctx);
  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
    obstacle->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(obstacle->get_color().r),
                            static_cast<int>(obstacle->get_color().g),
                            static_cast<int>(obstacle->get_color().b),
                            static_cast<int>(obstacle->get_color().a)));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, obstacle->get_pos().x, obstacle->get_pos().y,
          obstacle->name().c_str(), NULL);
}

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, home->get_pos().x, home->get_pos().y, home->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(home->get_color().r),
                            static_cast<int>(home->get_color().g),
                            static_cast<int>(home->get_color().b),
                            static_cast<int>(home->get_color().a)));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, home->get_pos().x, home->get_pos().y, home->name().c_str(),
    NULL);
}

void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx,
                               const Robot* const robot) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, robot->get_pos().x, robot->get_pos().y, robot->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(robot->get_color().r),
                            static_cast<int>(robot->get_color().g),
                            static_cast<int>(robot->get_color().b),
                            static_cast<int>(robot->get_color().a)));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, robot->get_pos().x, robot->get_pos().y, robot->name().c_str(),
    NULL);
}

void GraphicsArenaViewer::DrawRobotSensors(NVGcontext *ctx,
                               const Robot* const robot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered at the position and heading for this robot
  double xpos = robot->get_pos().x;
  double ypos = robot->get_pos().y;
  double angle = robot->get_heading_angle()*M_PI/180;
  double sensor_angle = robot->get_sensor_proximity_field_of_view();
  sensor_angle = sensor_angle*M_PI/90;
  // here I divide by 90 rather than 180 because
  // I only have one sensor_proximity in an entity
  // which is responsible to check for the +- field_of_view
  // range for the entity.
  double sensor_dist = robot->get_radius() +
                      robot->get_sensor_proximity_range();

  nvgSave(ctx);
  nvgTranslate(ctx, xpos, ypos);
  nvgRotate(ctx, angle);

  // sensor cone outline
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 100));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // blue for right sensor cone
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(100, 100, 255, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  // yellow for left sensor cone
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(255, 255, 100, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  nvgRestore(ctx);
}

void GraphicsArenaViewer::DrawSuperBot(NVGcontext *ctx,
                               const SuperBot* const superbot) {
  nvgBeginPath(ctx);
  nvgCircle(ctx, superbot->get_pos().x, superbot->get_pos().y,
            superbot->get_radius());
  nvgFillColor(ctx, nvgRGBA(static_cast<int>(superbot->get_color().r),
                            static_cast<int>(superbot->get_color().g),
                            static_cast<int>(superbot->get_color().b),
                            static_cast<int>(superbot->get_color().a)));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx, superbot->get_pos().x, superbot->get_pos().y,
          superbot->name().c_str(),
    NULL);
}

void GraphicsArenaViewer::DrawSuperBotSensors(NVGcontext *ctx,
                               const SuperBot* const superbot) {
  // translate and rotate all graphics calls that follow so that they are
  // centered at the position and heading for this robot
  double xpos = superbot->get_pos().x;
  double ypos = superbot->get_pos().y;
  double angle = superbot->get_heading_angle()*M_PI/180;
  double sensor_angle = superbot->get_sensor_proximity_field_of_view();
  sensor_angle = sensor_angle*M_PI/90;
  // here I divide by 90 rather than 180 because
  // I only have one sensor_proximity in an entity
  // which is responsible to check for the +- field_of_view
  // range for the entity.
  double sensor_dist = superbot->get_radius() +
                      superbot->get_sensor_proximity_range();

  nvgSave(ctx);
  nvgTranslate(ctx, xpos, ypos);
  nvgRotate(ctx, angle);
  // sensor cone outline
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 100));
  nvgStroke(ctx);
  nvgRestore(ctx);

  // blue for right sensor cone
  nvgSave(ctx);
  nvgRotate(ctx, 0.5 * sensor_angle);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(100, 100, 255, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  // yellow for left sensor cone
  nvgSave(ctx);
  nvgBeginPath(ctx);
  nvgMoveTo(ctx, 0.0, 0.0);
  nvgLineTo(ctx, sensor_dist, 0.0);
  nvgArc(ctx, 0.0, 0.0, sensor_dist, 0.0, -0.5 * sensor_angle, NVG_CCW);
  nvgLineTo(ctx, 0.0, 0.0);
  nvgFillColor(ctx, nvgRGBA(255, 255, 100, 150));
  nvgFill(ctx);
  nvgRestore(ctx);

  nvgRestore(ctx);
}

void GraphicsArenaViewer::draw_status(NVGcontext *ctx) {
  if (arena_->get_lose_status()) {
    nvgBeginPath(ctx);
    nvgCircle(ctx, 512, 384, 300);
    nvgFillColor(ctx, nvgRGBA(255, 0, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgStroke(ctx);
    std::string st = "YOU LOSE";
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgText(ctx, 512, 384,
            st.c_str(), NULL);
  } else if (arena_->get_win_status()) {
    nvgBeginPath(ctx);
    nvgCircle(ctx, 512, 384, 300);
    nvgFillColor(ctx, nvgRGBA(0, 255, 0, 255));
    nvgFill(ctx);
    nvgStrokeColor(ctx, nvgRGBA(0, 255, 0, 255));
    nvgStroke(ctx);
    std::string st = "YOU WIN";
    nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
    nvgText(ctx, 512, 384, st.c_str(), NULL);
  }
}

// This is the primary driver for drawing all entities in the arena.
// It is called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  std::vector<Robot*> robots = arena_->robots();
  for (size_t i = 0; i < robots.size(); i++) {
    DrawRobot(ctx, robots[i]);
    DrawRobotSensors(ctx, robots[i]);
  } /* for(i..) */

  DrawPlayer(ctx, arena_->player());
  DrawSuperBot(ctx, arena_->superbot());
  DrawSuperBotSensors(ctx, arena_->superbot());
  DrawHomeBase(ctx, arena_->home_base());

  if (arena_->get_lose_status()) {
    paused_ = true;
    draw_status(ctx);
  }
  if (arena_->get_win_status()) {
    paused_ = true;
    draw_status(ctx);
  }
}

NAMESPACE_END(csci3081);
