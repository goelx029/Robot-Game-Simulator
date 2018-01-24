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
TEST(MallardTest, Constructor) {
  Duck* my_duck = new Mallard();
  string expect_str_1="Fly with wings at speed of 5 mph.";
  string expect_str_2="Quack at 10 decibels.";
  string expect_str_3="Fly with wings at speed of 20 mph.";
  string expect_str_4="Cannot talk.";
  EXPECT_STREQ(expect_str_1.c_str(), my_duck->performFly().c_str())<<"FAIL: Display";
  EXPECT_STREQ(expect_str_2.c_str(), my_duck->performQuack().c_str())<<"FAIL: Display";
  my_duck->setFlyBehavior(new FlyWithRocket());
  my_duck->setQuackBehavior(new Mute());
  EXPECT_STREQ(expect_str_3.c_str(), my_duck->performFly().c_str())<<"FAIL: Display";
  EXPECT_STREQ(expect_str_4.c_str(), my_duck->performQuack().c_str())<<"FAIL: Display";
}

TEST(MallardTest, display) {
  Duck* my_duck = new Mallard();
  string expect_str="I am a Mallard.";
  EXPECT_STREQ(expect_str.c_str(), my_duck->display().c_str())<<"FAIL: Display";
}