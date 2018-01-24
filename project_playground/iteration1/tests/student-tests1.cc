/* STUDENTS: Write your own unit tests in this file.  Or, better yet,
   rename this file to something more meaningful and/or add additional
   files of tests to this directory to test your project code in
   whatever ways you see fit!
 */

// The Google Test framework
#include <gtest/gtest.h>


// Includes for project code in the ../src directory
#include "../src/arena.h"
#include "../src/arena_params.h"
#include "../src/event_collision.h"
#include "../src/robot.h"
#include "../src/color.h"
/************************************************************************
* SETUP
*************************************************************************/
// class StudentTest : public ::testing::Test {
//  protected:
//    virtual void SetUp() {
//      // Initialize default start values for various arena entities
//
//      rparams.battery_max_charge = 100.0;
//      rparams.angle_delta = 10;
//      rparams.collision_delta = 1;
//      rparams.radius = 20.0;
//      rparams.pos = Position(500, 500);
//      rparams.color = csci3081::Color(0, 0, 255, 255); /* blue */
//      aparams.robot = rparams;
//
//      aparams.recharge_station.radius = 20.0;
//      aparams.recharge_station.pos = {500, 300};
//      aparams.recharge_station.color = csci3081::Color(0, 128, 128, 255); /* green */
//
//      aparams.home_base.radius = 20.0;
//      aparams.home_base.pos = {400, 400};
//      aparams.home_base.color = csci3081::Color(255, 0, 0, 255); /* red */
//
//      aparams.obstacles[0].radius = 30.0;
//      aparams.obstacles[0].pos = {200, 200};
//      aparams.obstacles[0].color = csci3081::Color(255, 255, 255, 255); /* white */
//
//      aparams.n_obstacles = 1;
//      aparams.x_dim = 1024;
//      aparams.y_dim = 768;
//    }
//    csci3081::robot_params rparams;
//    csci3081::arena_params aparams;
//  };

TEST(StudentTests, SanityCheck) {
  EXPECT_EQ(1, 1);
}

// make sure the simtime is initialized to 0.0 whenever a new RobotLand is created
TEST(StudentTests, SimTimeInitialized) {
  // rparams.pos = Position(240, 200);
  // aparams.robot = rparams;
  // csci3081::Arena rl(&aparams);
  // csci3081::Robot * robot = rl.robot();
  // EXPECT_EQ(rl.get_current_time(), 0.0);
}
