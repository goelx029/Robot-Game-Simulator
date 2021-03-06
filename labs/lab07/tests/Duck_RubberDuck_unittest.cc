/* STUDENTS:  DO NOT EDIT THIS FILE.  INSTEAD, CREATE YOUR OWN UNIT TESTS ACCORDING
TO THE LAB DOCUMENT.
*/

// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/Duck.h"
//#include <iostream>
#include <string.h>
// Initial Test for Rubber Duck.  YayYay
TEST(RubberDuckTest, Constructor) {
  RubberDuck my_rubber_duck;
  string expect_str_1="Cannot fly.";
  string expect_str_2="Quack at 2 decibels.";
  string expect_str_3="Fly with wings at speed of 20 mph.";
  string expect_str_4="Cannot talk.";
  EXPECT_STREQ(expect_str_1.c_str(), my_rubber_duck.performFly().c_str())<<"FAIL: Display";
  EXPECT_STREQ(expect_str_2.c_str(), my_rubber_duck.performQuack().c_str())<<"FAIL: Display";
  my_rubber_duck.setFlyBehavior(new FlyWithRocket());
  my_rubber_duck.setQuackBehavior(new Mute());
  EXPECT_STREQ(expect_str_3.c_str(), my_rubber_duck.performFly().c_str())<<"FAIL: Display";
  EXPECT_STREQ(expect_str_4.c_str(), my_rubber_duck.performQuack().c_str())<<"FAIL: Display";
}

TEST(RubberDuckTest, display) {
  RubberDuck my_rubber_duck;
  string expect_str="I am a Rubber Duck.";
  EXPECT_STREQ(expect_str.c_str(), my_rubber_duck.display().c_str())<<"FAIL: Display";
}
