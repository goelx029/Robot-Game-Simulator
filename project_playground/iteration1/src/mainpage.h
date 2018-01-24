/**
 * @file mainpage.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * Project Iteration 1 Base Code:- The software revolves around two main classes - Arena and the Robot Class. Another important class is the GraphicsArenaViewer class that is responsible for graphically representing the whole simulation of the arena as time advances. The purpose of the software is to produce a game in which the aim of the robot is to reach the home_base before it runs out of battery. There are several factors like (collision from another entity, collision from walls, collision with recharge station). The software handles most of these events through the eventhandler classes.
 Arena Class is the most important class as it brings together all the pieces and actually runs the game. It is responsible for instantiating all the objects(entities) in the arena (i.e. Robot, Obstacles, HomeBase, RechargeStation) and also responsible for Advancing time, Updating each and every object(entity) in the arena and also checking how they interact with each other and the environment(collision and entity out of bounds).
 GraphicsArenaViewer Class is the class that provides the interface(graphical) interface. It first collects all the information from the arena (about arena and its entities), and then using their individual properties it then creates them individually. As time progress, the work of the GraphicsArenaViewer class is to again draw all the entities with their new state. The class accomplishes this task through the help of DrawUsingNanoVG which is called in every iteration of nanogui::mainloop().
 Robot Class is also really important because it is the center piece of the game much like a car in a car racing game. Robot class handles all the member variables which maintain and help determine the state of the robot at a particular time. It also contains methods that mutate the state of its motion handler, sensors and motion behaviors so that we can always get information about the current position and velocity to calculate the future position and velocity.
 In my UML diagram I have tried to map out the relationship between all the classes using the principles of Inheritance, Association, Composition, Aggregation. Inheritance was easy to depict from the Base Code because of how Inheritance is implemented in the code. My idea of association was related to how the classes would be interacting with each other and whether logically would they need to interact. For aggregation and composition I thought about how an object of class was part of another class and how would the destruction of object of the main class would effect the object (in the main class) of other class.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */

#endif  // SRC_MAINPAGE_H_
