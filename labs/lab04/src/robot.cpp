#include<iostream>
#include"robot.h"

robot::robot()
{
  size = 0;
  r_col = 0;
  g_col = 0;
  b_col = 0;
  a_col = 255;
  x_pos = 0.0;
  y_pos = 0.0;
  x_vel = 0.0;
  y_vel = 0.0;
}

robot::robot(int in_size, double in_xpos, double in_ypos, double in_xvel, double in_yvel)
{
  size = in_size;
  r_col = 200;
  g_col = 100;
  b_col = 150;
  a_col = 255;
  x_pos = in_xpos;
  y_pos = in_ypos;
  x_vel = in_xvel;
  y_vel = in_yvel;
}


void robot::set_size(int in_size)
{
  size = in_size;
}
void robot::set_xpos(double in_xpos)
{
  x_pos = in_xpos;
}
void robot::set_ypos(double in_ypos)
{
  y_pos = in_ypos;
}
void robot::set_xvel(double in_xvel)
{
  x_vel = in_xvel;
}
void robot::set_yvel(double in_yvel)
{
  y_vel = in_yvel;
}
void robot::set_rcol(int in_rcol)
{
  r_col = in_rcol;
}
void robot::set_gcol(int in_gcol)
{
  g_col = in_gcol;
}
void robot::set_bcol(int in_bcol)
{
  b_col = in_bcol;
}
void robot::set_acol(int in_acol)
{
  a_col = in_acol;
}





int robot::get_size()
{
    return size;
}
double robot::get_xpos()
{
  return x_pos;
}
double robot::get_ypos()
{
  return y_pos;
}
double robot::get_xvel()
{
  return x_vel;
}
double robot::get_yvel()
{
  return y_vel;
}
int robot::get_rcol()
{
  return r_col;
}
int robot::get_gcol()
{
  return g_col;
}
int robot::get_bcol()
{
  return b_col;
}
int robot::get_acol()
{
  return a_col;
}
