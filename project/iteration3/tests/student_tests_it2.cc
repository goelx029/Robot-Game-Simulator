/* STUDENTS: Write your own unit tests in this file.  Or, better yet,
   rename this file to something more meaningful and/or add additional
   files of tests to this directory to test your project code in
   whatever ways you see fit!
 */

// The Google Test framework
#include <gtest/gtest.h>


// Includes for project code in the ../src directory
#include "../src/sensor_touch.h"
#include "../src/entity_type.h"
#include "../src/sensor_proximity.h"
#include "../src/sensor_distress.h"
#include "../src/sensor_entity_type.h"
#include "../src/position.h"
#include "../src/common.h"
#include "../src/obstacle.h"
#include "../src/player.h"
#include "../src/player_params.h"
#include "../src/robot_params.h"
#include "../src/robot.h"
#include "../src/event_base_class.h"
#include "../src/event_proximity.h"
#include "../src/event_collision.h"
#include "../src/event_distress_call.h"
#include "../src/event_type_emit.h"


TEST(StudentTestsIT2, STSanity) {
  csci3081::SensorTouch st;

  EXPECT_EQ(st.get_activated(), false);
  EXPECT_EQ(st.get_point_of_contact().x, 0.0);
  EXPECT_EQ(st.get_point_of_contact().y, 0.0);
  EXPECT_EQ(st.get_angle_of_contact(), 0.0);
  EXPECT_EQ(st.get_st_activated(), false);
  EXPECT_EQ(st.get_output(), 0);

  st.set_activated(true);
  st.set_point_of_contact(csci3081::Position(1.0, 1.0));
  st.set_angle_of_contact(180.0);
  st.set_st_activated(true);
  st.set_output(1);
  EXPECT_EQ(st.get_activated(), true);
  EXPECT_EQ(st.get_point_of_contact().x, 1.0);
  EXPECT_EQ(st.get_point_of_contact().y, 1.0);
  EXPECT_EQ(st.get_angle_of_contact(), 180.0);
  EXPECT_EQ(st.get_st_activated(), true);
  EXPECT_EQ(st.get_output(), 1);
}

// make sure the simtime is initialized to 0.0 whenever a new RobotLand is created
TEST(StudentTestsIT2, STReset) {
  csci3081::SensorTouch st;

  st.set_activated(true);
  st.set_point_of_contact(csci3081::Position(1.0, 1.0));
  st.set_angle_of_contact(180.0);
  st.set_st_activated(true);
  st.set_output(1);
  EXPECT_EQ(st.get_activated(), true);
  EXPECT_EQ(st.get_point_of_contact().x, 1.0);
  EXPECT_EQ(st.get_point_of_contact().y, 1.0);
  EXPECT_EQ(st.get_angle_of_contact(), 180.0);
  EXPECT_EQ(st.get_st_activated(), true);
  EXPECT_EQ(st.get_output(), 1);

  st.Reset();
  EXPECT_EQ(st.get_activated(), false);
  EXPECT_EQ(st.get_point_of_contact().x, 0.0);
  EXPECT_EQ(st.get_point_of_contact().y, 0.0);
  EXPECT_EQ(st.get_angle_of_contact(), 0.0);
  EXPECT_EQ(st.get_st_activated(), false);
  EXPECT_EQ(st.get_output(), 0);
}

TEST(StudentTestsIT2, STOutput) {
  csci3081::SensorTouch st;
  csci3081::EventCollision e;
  csci3081::player_params pparams;
  pparams.battery_max_charge = 100.0;
  pparams.radius = 20.0;
  pparams.color = csci3081::Color(0, 0, 0, 0);
  pparams.max_speed = 5;
  pparams.speed_delta = 1;
  pparams.angle_delta = 30;
  pparams.collision_delta = 1;
  csci3081::Obstacle ob = csci3081::Obstacle(20, csci3081::Position(200.0, 200.0), csci3081::Color(0, 0, 0, 0));
  e.set_sensed(&ob);

  pparams.pos = csci3081::Position(240.0, 200.0);
  csci3081::Player pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), true);
  EXPECT_EQ(st.get_output(), 1);
  st.Reset();

  pparams.pos = csci3081::Position(200.0, 240.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), true);
  EXPECT_EQ(st.get_output(), 1);
  st.Reset();

  pparams.pos = csci3081::Position(160.0, 200.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), true);
  EXPECT_EQ(st.get_output(), 1);
  st.Reset();

  pparams.pos = csci3081::Position(200.0, 160.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), true);
  EXPECT_EQ(st.get_output(), 1);
  st.Reset();

  pparams.pos = csci3081::Position(250.0, 200.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), false);
  EXPECT_EQ(st.get_output(), 0);
  st.Reset();

  pparams.pos = csci3081::Position(240.0, 220.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), false);
  EXPECT_EQ(st.get_output(), 0);
  st.Reset();

  pparams.pos = csci3081::Position(240.0, 240.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), false);
  EXPECT_EQ(st.get_output(), 0);
  st.Reset();

  pparams.pos = csci3081::Position(242.0, 200.0);
  pl = csci3081::Player(&pparams);
  e.set_sensing(&pl);
  st.Accept(&e);
  EXPECT_EQ(st.get_st_activated(), false);
  EXPECT_EQ(st.get_output(), 0);
  st.Reset();
}

TEST(StudentTestsIT2, SPSanity) {
  csci3081::SensorProximity sp;

  EXPECT_EQ(sp.get_activated(), false);
  EXPECT_EQ(sp.get_range(), 0.0);
  EXPECT_EQ(sp.get_field_of_view(), 0.0);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);

  sp.set_activated(true);
  sp.set_range(30.0);
  sp.set_field_of_view(180.0);
  sp.set_sp_activated(true);
  sp.set_output(1);
  EXPECT_EQ(sp.get_activated(), true);
  EXPECT_EQ(sp.get_range(), 30.0);
  EXPECT_EQ(sp.get_field_of_view(), 180.0);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 1);
}

TEST(StudentTestsIT2, SPReset) {
  csci3081::SensorProximity sp;

  sp.set_activated(true);
  sp.set_range(30.0);
  sp.set_field_of_view(180.0);
  sp.set_sp_activated(true);
  sp.set_output(1);
  EXPECT_EQ(sp.get_activated(), true);
  EXPECT_EQ(sp.get_range(), 30.0);
  EXPECT_EQ(sp.get_field_of_view(), 180.0);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 1);

  sp.Reset();
  EXPECT_EQ(sp.get_activated(), false);
  EXPECT_EQ(sp.get_range(), 30.0);
  EXPECT_EQ(sp.get_field_of_view(), 180.0);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
}

TEST(StudentTestsIT2, SPOutput) {
  csci3081::SensorProximity sp;
  csci3081::EventProximity e;
  csci3081::player_params pparams;
  pparams.battery_max_charge = 100.0;
  pparams.radius = 20.0;
  pparams.color = csci3081::Color(0, 0, 0, 0);
  pparams.max_speed = 5;
  pparams.speed_delta = 1;
  pparams.angle_delta = 30;
  pparams.collision_delta = 1;
  csci3081::Obstacle ob = csci3081::Obstacle(20, csci3081::Position(200.0, 200.0), csci3081::Color(0, 0, 0, 0));
  e.set_sensed(&ob);

  sp.set_range(30.0);
  sp.set_field_of_view(45.0);

  pparams.pos = csci3081::Position(100.0, 500.0);
  csci3081::Player pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

//*************************************************************************
  pparams.pos = csci3081::Position(150.0, 200.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(180.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(150.0, 200.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(200.0, 150.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(200.0, 150.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(90.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(250.0, 200.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(250.0, 200.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(180.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(200.0, 250.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(200.0, 250.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(270.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(150.0, 150.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(160.0, 170.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(250.0, 150.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(240.0, 170.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(180.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(250.0, 250.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(240.0, 230.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(180.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(150.0, 250.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), false);
  EXPECT_EQ(sp.get_output(), -1);
  sp.Reset();

  pparams.pos = csci3081::Position(160.0, 230.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();
//*************************************************************************

  pparams.pos = csci3081::Position(150.0, 200.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 50);
  sp.Reset();

  pparams.pos = csci3081::Position(150.0, 220.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 53);
  sp.Reset();

  pparams.pos = csci3081::Position(150.0, 180.0);
  pl = csci3081::Player(&pparams);
  pl.set_heading_angle(0.0);
  e.set_sensing(&pl);
  sp.Accept(&e);
  EXPECT_EQ(sp.get_sp_activated(), true);
  EXPECT_EQ(sp.get_output(), 53);
  sp.Reset();
}

TEST(StudentTestsIT2, SDSanity) {
  csci3081::SensorDistress sd;

  EXPECT_EQ(sd.get_activated(), false);
  EXPECT_EQ(sd.get_range(), 0.0);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);

  sd.set_activated(true);
  sd.set_range(30.0);
  sd.set_sd_activated(true);
  sd.set_output(1);
  EXPECT_EQ(sd.get_activated(), true);
  EXPECT_EQ(sd.get_range(), 30.0);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 1);
}

TEST(StudentTestsIT2, SDReset) {
  csci3081::SensorDistress sd;

  sd.set_activated(true);
  sd.set_range(30.0);
  sd.set_sd_activated(true);
  sd.set_output(1);
  EXPECT_EQ(sd.get_activated(), true);
  EXPECT_EQ(sd.get_range(), 30.0);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 1);

  sd.Reset();
  EXPECT_EQ(sd.get_activated(), false);
  EXPECT_EQ(sd.get_range(), 30.0);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
}

TEST(StudentTestsIT2, SDOutput) {
  csci3081::SensorDistress sd;
  csci3081::EventDistressCall e;

  csci3081::robot_params rparams;
  rparams.radius = 20.0;
  rparams.color = csci3081::Color(0, 0, 0, 0);
  rparams.max_speed = 5;
  rparams.collision_delta = 1;
  rparams.pos = csci3081::Position(200.0, 200.0);
  csci3081::Robot st = csci3081::Robot(&rparams);
  e.set_sensed(&st);

  sd.set_range(30.0);

  rparams.pos = csci3081::Position(250.0, 200.0);
  csci3081::Robot sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(270.0, 200.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(200.0, 250.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(200.0, 270.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(160.0, 170.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(240.0, 170.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(240.0, 230.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

  rparams.pos = csci3081::Position(160.0, 230.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), false);
  EXPECT_EQ(sd.get_output(), 0);
  sd.Reset();

//*************************************************************************

  st.set_distress(true);

  rparams.pos = csci3081::Position(250.0, 200.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 50);
  sd.Reset();

  rparams.pos = csci3081::Position(270.0, 200.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 70);
  sd.Reset();

  rparams.pos = csci3081::Position(200.0, 250.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 50);
  sd.Reset();

  rparams.pos = csci3081::Position(200.0, 270.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 70);
  sd.Reset();

  rparams.pos = csci3081::Position(160.0, 170.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 50);
  sd.Reset();

  rparams.pos = csci3081::Position(240.0, 170.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 50);
  sd.Reset();

  rparams.pos = csci3081::Position(240.0, 230.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 50);
  sd.Reset();

  rparams.pos = csci3081::Position(160.0, 230.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  sd.Accept(&e);
  EXPECT_EQ(sd.get_sd_activated(), true);
  EXPECT_EQ(sd.get_output(), 50);
  sd.Reset();

}

TEST(StudentTestsIT2, SENTTYPSanity) {
  csci3081::SensorEntityType senttyp;

  EXPECT_EQ(senttyp.get_senttyp_activated(), false);
  EXPECT_EQ(senttyp.get_range(), 30.0);

  senttyp.set_senttyp_activated(true);
  senttyp.set_range(30.0);
  EXPECT_EQ(senttyp.get_senttyp_activated(), true);
  EXPECT_EQ(senttyp.get_range(), 30.0);
}

TEST(StudentTestsIT2, SENTTYPReset) {
  csci3081::SensorEntityType senttyp;

  senttyp.set_senttyp_activated(true);
  senttyp.set_range(30.0);
  EXPECT_EQ(senttyp.get_senttyp_activated(), true);
  EXPECT_EQ(senttyp.get_range(), 30.0);

  senttyp.Reset();
  EXPECT_EQ(senttyp.get_senttyp_activated(), false);
  EXPECT_EQ(senttyp.get_range(), 30.0);
}

TEST(StudentTestsIT2, SENTTYPOutput) {
  csci3081::entity_type typ;
  csci3081::SensorEntityType senttyp;
  csci3081::EventTypeEmit e;

  csci3081::robot_params rparams;
  rparams.radius = 20.0;
  rparams.color = csci3081::Color(0, 0, 0, 0);
  rparams.max_speed = 5;
  rparams.collision_delta = 1;
  rparams.pos = csci3081::Position(200.0, 200.0);
  csci3081::Robot st = csci3081::Robot(&rparams);
  e.set_sensed(&st);

  rparams.pos = csci3081::Position(300.0, 200.0);
  csci3081::Robot sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), false);
  senttyp.Reset();

  rparams.pos = csci3081::Position(200.0, 300.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), false);
  senttyp.Reset();

  rparams.pos = csci3081::Position(100.0, 200.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), false);
  senttyp.Reset();

  rparams.pos = csci3081::Position(200.0, 100.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), false);
  senttyp.Reset();

  rparams.pos = csci3081::Position(250.0, 200.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), true);
  senttyp.Reset();

  rparams.pos = csci3081::Position(200.0, 250.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), true);
  senttyp.Reset();

  rparams.pos = csci3081::Position(150.0, 200.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), true);
  senttyp.Reset();

  rparams.pos = csci3081::Position(200.0, 150.0);
  sensing = csci3081::Robot(&rparams);
  e.set_sensing(&sensing);
  senttyp.Accept(&e);
  EXPECT_EQ(senttyp.get_senttyp_activated(), true);
  senttyp.Reset();

}
