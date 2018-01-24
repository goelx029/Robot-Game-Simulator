/**
 * @file read_params.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <fstream>
#include <string>
#include "src/common.h"
#include "src/read_params.h"
#include "src/robot_params.h"
#include "src/player_params.h"
#include "src/arena_params.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
csci3081::arena_params ReadParams::params_read() {
  std::ifstream config;
  config.open("./src/params_file.txt");
  assert(config.is_open());
  std::string line;
  char command[1000];
  csci3081::arena_params aparams;

  while (getline(config, line)) {
    if (line[0] == '#') {
      continue;
    } else {
      sscanf(line.c_str(), "%s ", command);
      std::string cmd = command;
      if (cmd == "Player") {
        float battery_max_charge, radius, pos_x, pos_y;
        int col_r, col_g, col_b, col_a;
        int max_speed, speed_delta, angle_delta, collision_delta;
        sscanf(line.c_str(), "Player %f %f %f %f %d %d %d %d %d %d %d %d",
        &battery_max_charge,
        &radius,
        &pos_x,
        &pos_y,
        &col_r,
        &col_g,
        &col_b,
        &col_a,
        &max_speed,
        &speed_delta,
        &angle_delta,
        &collision_delta);
        csci3081::player_params pparams;
        pparams.battery_max_charge = battery_max_charge;
        pparams.radius = radius;
        pparams.pos = csci3081::Position(pos_x, pos_y);
        pparams.color = csci3081::Color(col_r, col_g, col_b, col_a);
        pparams.max_speed = max_speed;
        pparams.speed_delta = speed_delta;
        pparams.angle_delta = angle_delta;
        pparams.collision_delta = collision_delta;
        aparams.player = pparams;
      } else if (cmd == "RechargeStation") {
        float radius, pos_x, pos_y;
        int col_r, col_g, col_b, col_a;
        sscanf(line.c_str(), "RechargeStation %f %f %f %d %d %d %d",
        &radius,
        &pos_x,
        &pos_y,
        &col_r,
        &col_g,
        &col_b,
        &col_a);
        aparams.recharge_station.radius = radius;
        aparams.recharge_station.pos = csci3081::Position(pos_x, pos_y);
        aparams.recharge_station.color = csci3081::Color(col_r,
                                          col_g, col_b, col_a);
      } else if (cmd == "HomeBase") {
        float radius, pos_x, pos_y;
        int col_r, col_g, col_b, col_a;
        sscanf(line.c_str(), "HomeBase %f %f %f %d %d %d %d",
        &radius,
        &pos_x,
        &pos_y,
        &col_r,
        &col_g,
        &col_b,
        &col_a);
        aparams.home_base.radius = radius;
        aparams.home_base.pos = csci3081::Position(pos_x, pos_y);
        aparams.home_base.color = csci3081::Color(col_r,
                                  col_g, col_b, col_a);
      } else if (cmd == "RobotNo.") {
        int no_of_robots_;
        sscanf(line.c_str(), "RobotNo. %d",
        &no_of_robots_);
        aparams.n_robots = no_of_robots_;
      } else if (cmd == "Robot") {
        int id;
        float radius, pos_x, pos_y, max_speed;
        int col_r, col_g, col_b, col_a;
        float sensor_range, sensor_angle;
        sscanf(line.c_str(), "Robot %d %f %f %f %d %d %d %d %f %f %f",
        &id,
        &radius,
        &pos_x,
        &pos_y,
        &col_r,
        &col_g,
        &col_b,
        &col_a,
        &max_speed,
        &sensor_range,
        &sensor_angle);
        aparams.robots[id].radius = radius;
        aparams.robots[id].pos = csci3081::Position(pos_x, pos_y);
        aparams.robots[id].color = csci3081::Color(col_r,
                                  col_g, col_b, col_a);
        aparams.robots[id].max_speed = max_speed;
        aparams.robots[id].sp_range = sensor_range;
        aparams.robots[id].sp_field_of_view = sensor_angle;
        aparams.robots[id].collision_delta = 1;
      } else if (cmd == "SuperBot") {
        float radius, pos_x, pos_y, max_speed;
        int col_r, col_g, col_b, col_a;
        float sensor_range, sensor_angle;
        sscanf(line.c_str(), "SuperBot %f %f %f %d %d %d %d %f %f %f",
        &radius,
        &pos_x,
        &pos_y,
        &col_r,
        &col_g,
        &col_b,
        &col_a,
        &max_speed,
        &sensor_range,
        &sensor_angle);
        aparams.superbot.radius = radius;
        aparams.superbot.pos = csci3081::Position(pos_x, pos_y);
        aparams.superbot.color = csci3081::Color(col_r,
                                  col_g, col_b, col_a);
        aparams.superbot.max_speed = max_speed;
        aparams.superbot.sp_range = sensor_range;
        aparams.superbot.sp_field_of_view = sensor_angle;
        aparams.superbot.collision_delta = 1;
        for (int i = 0; i < 5; i++) {
          aparams.robots[i].superbot_max_speed = max_speed;
          aparams.robots[i].superbot_color = csci3081::Color(col_r,
                                              col_g, col_b, col_a);
          aparams.robots[i].superbot_sp_range = sensor_range;
          aparams.robots[i].superbot_sp_field_of_view = sensor_angle;
        }
      } else if (cmd == "ObstacleNo.") {
        int no_of_obstacles_;
        sscanf(line.c_str(), "ObstacleNo. %d",
        &no_of_obstacles_);
        aparams.n_obstacles = no_of_obstacles_;
      } else if (cmd == "Obstacle") {
        int id;
        float radius, pos_x, pos_y;
        int col_r, col_g, col_b, col_a;
        sscanf(line.c_str(), "Obstacle %d %f %f %f %d %d %d %d",
        &id,
        &radius,
        &pos_x,
        &pos_y,
        &col_r,
        &col_g,
        &col_b,
        &col_a);
        aparams.obstacles[id].radius = radius;
        aparams.obstacles[id].pos = csci3081::Position(pos_x, pos_y);
        aparams.obstacles[id].color = csci3081::Color(col_r,
                                    col_g, col_b, col_a);
      } else {
        printf("%s Command not found \n", command);
      }
    }
  }  // while
  aparams.x_dim = 1024;
  aparams.y_dim = 768;
  return aparams;
}
