BugFixes.md File

General Overview:-

1. The Project Design Overview is present in my Mainpage.h file and can be accessed through the doxygen documentation.
2. I changed a bunch of things in main.cc so that I can have higher speeds and different angles. Please change these values as you wish to ensure that the game behaves as you wish.

Overview of Bugs and Implementation of All Priority Levels
- Priority Level 1
  - Implement the arrow keypress handlers.
    - Completed
    - Bug :- If the speed of the robot is really small then when I turn the robot it does not turn visually. The robot at really small speed just seem to move in angles which are a multiple of 90 degrees (0, 90, 180, 270). I am not sure why this happens as the robot is changing direction perfectly when the speed is greater than or equal to 1.
  - Bounce robot off of other entities (at angle of incidence).
    - Completed
    - Bug :- N/A
    - Note - I used a technique to ensure that the mobile entity comes out of the collision_delta circumference around the obstacle by using the formula for external division of a line in two ratios.
  - Deplete battery as robot moves.
    - Completed
    - Bug :- N/A
  - Recharge battery if robot collides with recharge station.
    - Completed
    - Bug :- N/A
  - Home base is mobile.
    - Completed
    - Bug :- N/A
    - Note - I made the HomeBase class inherit from the ArenaMobileEntity class to make the HomeBase mobile and as discussed in the lecture on one day I commented out the Accept(EventRecharge * e) function from the ArenaMobileEntity class for a better design. I also made the home_base_params inherit from arena_mobile_entity_params, however as stated in the class on October 31, I undo'ed this change so that the interface as given to us by the faculty remains same. I did the same with the Accept(EventRecharge * e) function and thus have a Accept(EventRecharge * e) function in HomeBase class that does nothing.

- Priority Level 2
  - Implement functionality for pause and restart buttons.
    - Completed
    - Bug :- N/A
  - Implement functionality for win and lose. This can be text or windows.
    - Completed
    - Bug :- N/A
    - Note - I am using std::cin to get a value from the user through the terminal to ensure that I restart the game if the user wants to play again.
  - Fix bounce behavior off of left and right walls (it should reflect at angle of incidence.)
    - Completed
    - Bug :- N/A
  - Visualize battery level (can be through GUI or something on the robot)
    - Completed
    - Bug :- N/A
  - Replace all nanogui::Color types in Arena to separate graphics from robots.
    - Completed
    - Bug :- N/A

- Priority Level 3
  - ~~Limit the working dimensions inside which the robots can move (so GUI is not in arena).~~  Do not do for iteration 1.
  - Create a Sensor base class and make SensorTouch a subclass.
    - Completed
    - Bug :- N/A
    - Note - I made an abstract class named Sensor.h that provides a interface to the SensorTouch class.
  - Deplete battery when robot bumps into obstacles.
    - Completed
    - Bug :- N/A
    - Note - I am Using a function that just decreases the battery level by some delta of my choosing.
  - Slow the robot down when it bumps into obstacles.
    - Completed
    - Bug :- N/A
    - Note - Sam suggested me to change the velocity to be some percentage of the original velocity and thus I am using 70% of original velocity as my final velocity after collision.
  - Home base randomly changes direction at random times.
    - Completed
    - Bug :- N/A
    - Note - I used rand_r for the random motion of my home_base and that is why I had to declare a
            * thread_local unsigned int seed = time(NULL);
            so that I can pass it to the rand_r as a parameter.
  - Create a total of 5 obstacles in the environment.
    - Completed
    - Bug :- N/A
