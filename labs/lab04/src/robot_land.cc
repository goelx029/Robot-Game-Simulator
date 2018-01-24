/**
 * @file robot_land.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_land.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/


RobotLand::RobotLand(void)
{
  sim_time_ = 0.0;
  initialize();
}

void RobotLand::initialize(void)
{
  robot1 = new robot(50,400.0,300.0,10.0,12.0);
  robot2 = new robot(50,400.0,300.0,-15.0,-9.0);
}





int RobotLand::get_rcol(int id)
{
  if(id == 0)
  {
    return robot1->get_rcol();
  }
  else
  {
    return robot2->get_rcol();
  }
}


int RobotLand::get_gcol(int id)
{
  if(id == 0)
  {
    return robot1->get_gcol();
  }
  else
  {
    return robot2->get_gcol();
  }
}


int RobotLand::get_bcol(int id)
{
  if(id == 0)
  {
    return robot1->get_bcol();
  }
  else
  {
    return robot2->get_bcol();
  }
}



void RobotLand::set_color(int in_rcol, int in_gcol, int in_bcol)
{
  robot1->set_rcol((robot1->get_rcol()+in_rcol)%256);
  robot2->set_rcol((robot2->get_rcol()+in_rcol)%256);
  robot1->set_gcol((robot1->get_gcol()+in_gcol)%256);
  robot2->set_gcol((robot2->get_gcol()+in_gcol)%256);
  robot1->set_bcol((robot1->get_bcol()+in_bcol)%256);
  robot2->set_bcol((robot2->get_bcol()+in_bcol)%256);
}

void RobotLand::advance_time(double dt) {
   robot1->set_xpos(robot1->get_xpos()+(robot1->get_xvel()*dt));
   robot1->set_ypos(robot1->get_ypos()+(robot1->get_yvel()*dt));

   robot2->set_xpos(robot2->get_xpos()+(robot2->get_xvel()*dt));
   robot2->set_ypos(robot2->get_ypos()+(robot2->get_yvel()*dt));

   sim_time_ += dt;
   std::cout << "Advancing simulation time to " << sim_time_ << std::endl;
 }








// Hard coded for 2 robots moving in circular patterns
int RobotLand::get_num_robots(void) { return 2; }

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
bool RobotLand::get_robot_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0)
  {
    *x_pos = robot1->get_xpos();
    *y_pos = robot1->get_ypos();
    return true;
  } else if (id == 1)
  {
    // make this robot slower
    //double t = 0.75 * sim_time_;
    *x_pos = robot2->get_xpos();
    *y_pos = robot2->get_ypos();
    return true;
  }
  else
  {
    return false;
  }
}

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
// Notice the use of "id" -- how will you handle this in your robot class??
bool RobotLand::get_robot_vel(int id, double *x_vel, double *y_vel) {
  //double xnow, ynow, xprev, yprev;
  //double delta = 0.1;
  if (id == 0)
  {
    //xnow = circle_x(sim_time_);
    //ynow = circle_y(sim_time_);
    //xprev = circle_x(sim_time_ - delta);
    //yprev = circle_y(sim_time_ - delta);
    *x_vel = robot1->get_xvel();
    *y_vel = robot1->get_yvel();
    return true;
  }
  else if (id == 1)
  {
    // make this robot slower
    //double t = 0.75 * sim_time_;
    //xnow = circle_x(t);
    //ynow = circle_y(t);
    //xprev = circle_x(t - delta);
    //yprev = circle_y(t - delta);
    *x_vel = robot2->get_xvel();
    *y_vel = robot2->get_yvel();
    return true;
  }
  else
  {
    return false;
  }
}

// Hard coded for now...
double RobotLand::get_robot_radius(int id)
{
  if (id == 0)
  {
    return robot1->get_size();
  }
  else if (id == 1)
  {
    return robot2->get_size();
  }
  else
  {
    return 0;
  }
}

// Hard coded for now...  in radians
double RobotLand::get_robot_sensor_angle(int id) { return 2.0; }

// Hard coded for now...
double RobotLand::get_robot_sensor_distance(int id) {
  return 3.0 * get_robot_radius(id);
}

// Hard coded for now...
int RobotLand::get_num_obstacles() { return 1; }

// Hard coded for now...
bool RobotLand::get_obstacle_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    *x_pos = 200;
    *y_pos = 300;
    return true;
  }
  return false;
}

// Hard coded for now...
double RobotLand::get_obstacle_radius(int id) { return 75; }
