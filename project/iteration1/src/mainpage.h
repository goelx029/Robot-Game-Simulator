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
 * \section design_sec Project Design
 *
 * The project (iteration 1) has lots of classes interacting with each other in different manners to allow for the whole game to run. In my UML Diagram I have tried to map out as many
 relationships between classes as possible. These relationships include Inheritance, Association, Composition, Aggregation. The whole design can be subdivided into small parts which
 makes it easy to understand how everything is working.
  - Events - This consist of all the EventHandler classes:-
      1. EventBaseClass Class
      2. EventCollision Class
      3. EventRecharge Class
      4. EventCommand Class
      5. EventKeypress Class \n
    As seen in the upper left section of the UML diagram, these class (2-5) have inherited from the EventBaseClass Class which provides a genral framework for the Event Class.
    Also two of these class are associated with event_commands enumeration as it is used to handle the user input in form of arrow keypress.
    EventClasses are all responsible for handling different types of events that include (user keypress, recharge event of robot, collision events of mobile entities). They handle these by storing some information regarding the particular event and then sending these information to the arena/entity to update their state accordingly.
  - Helper Structs & Params Structs - This consist of all the Structs used in our project:-
      1. Position
      2. Color
      3. arena_entity_params
      4. arena_mobile_entity_params
      5. home_base_params
      6. robot_params
      7. arena_params \n
    As seen in the upper right section of the UML diagram, these structs have a Inheritance or an Association relationship between them.
    These structs working together helps create a foundation for the parameters used to initialize robot, home_base, recharge_station, obstacles, and Arena. They help to decluttter the parameters when passed to different constructors in the arena and its entities, also able to store more information in one object rather than have multiple basic data types.
  - Motion Helpers of Mobile Entities - This consist of all the classes that play a role in moving the mobile Entities in the arena:-
      1. Sensor
      2. SensorTouch
      3. RobotMotionBehavior
      4. RobotMotionHandler \n
    As seen in the middle right section of the UML diagram, these classes have relationships of Composition with Robot and HomeBase (Mobile Entities of the Arena). All these classes govern the movement, collision of these mobile entities in arena and thus are a crucial part of the whole project. They are just like a engine to the car.
    We can also observe that there are association relationships of these classes with EventClasses because, as these classes are responsible to govern the motion of the mobile entities they should be able to know about events as they alter the motion of the mobile entities.
  - Entities of the Arena - Classes that represent the entities present in the arena
      1. ArenaEntity - Interface for all the entities of the arena
      2. ArenaImmobileEntity - Interface for all the immobile entities of the arena, inherits from ArenaEntity
      3. ArenaMobileEntity - Interface for all the mobile entities of the arena, inherits from ArenaEntity
      4. Obstacle
      5. RechargeStation
      6. HomeBase
      7. Robot \n
    As seen in the middle section of the UML diagram, the classes have a very significant inheritance structure. Inheritance from the interface helps to ensure that we are implementing all the abstract functions. All the entities in this section are entities that are present in the Arena with different characterstics.
    Because Robot and HomeBase are mobile entities we make them inherit from ArenaMobileEntity while Obstacle inherits from ArenaImmobileEntity and RechargeStation from Obstacle. The inheritance structure helps add features to entities which are below in hierarchy. Other then Inheritance there are several relationships like Association,
    Aggregation and Composition from these classes with other helper (support) classes that play an integral part in making these classes work as they are supposed to.
  - Miscelleaneous - The miscelleaneous classes responsible for different aspects of the project.
      1. RobotBattery - The class responsible for handling the robot battery depletion and charging according to the events it accepts.
      2. Arena
      3. GraphicsArenaViewer \n
    As seen in the bootom section of the UML diagram, these classes (2-3) are one of the most essential classes for the whole project with their individual fields. Arena class is responsible for simulating the whole arena with all its entities. It is responsible for making all the entities interact in the right way such that we get the desired result from the game. GraphicsArenaViewer is responsible for providing the GUI for the whole arena and its contents.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */

#endif  // SRC_MAINPAGE_H_
