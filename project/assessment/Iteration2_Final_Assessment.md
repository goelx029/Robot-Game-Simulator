# Iteration 2 Feedback

*Grader: Sam - marqu317@umn.edu*

This file contains the feedback for your iteration 2. If you have questions or concerns, please reach out to me (Sam) and we can resolve them.

Note: This file entails 2 separate components of the iteration 2 grading: Code Submission and refactoring/unit tests. Code submission is the grade on your final code turn in for interfaces, function, etc. Refactoring/Unit tests refers to the initialization refactor you did and the unit tests your wrote for the sensors.

## Refactoring and Unit Tests

This is the grade for the initialization refactor you were asked to do and the sensor unit tests you turned in early in interation 2.



| **Category**                                  | **Score** | **Comments** |
|-----------------------------------------------|-----------|--------------|
| Refactor Initialization | 15 / 15 |  |
| Unit Tests for Sensors (needs 5) | 15 / 15 |  |
| **Total** | 30 / 30 |   |

## Code

This section details the functional components of your iteration 2. See the requirement write-up for iteration 2 for more detail about each listed category.



| **Category**                                  | **Score** | **Comments** |
|-----------------------------------------------|-----------|--------------|
| P1 - Define `enum entity_type` | 4 / 4 |  |
| P1 - Interface for abstract class Sensor | 4 / 4 | get_dist and get_angle could be useful functions to place in the position struct! |
| P1 - Interface & members for SensorProximity class | 4 / 4 |  |
| P1 - Interface & members for SensorDistress class | 4 / 4 |  |
| P1 - Interface & members for SensorEntityType class | 4 / 4 |  |
| P1 - Revise interface & members for SensorTouch | 4 / 4 |  |
| P1 - Interface & members for Events | 4 / 4 |  |
| P1 - Define abstract MotionHandler class | 4 / 4 |  |
| P1 - Define various motion handler classes | 4 / 4 |  |
| P1 - Rename Robot class to Player | 4 / 4 |  |
| P1 - Interface & members for a Robot class | 5 / 5 |  |
| P1 - Interface & members for a SuperBot class | 5 / 5 |  |
| P2 - Interface for Arena Methods modeled after Observer pattern | 10 / 10 | So your implementation works. To make it more generic, rather than have specific members of each sensor type, have a std::vector of sensors, which you can just iterate over when doing the event checking. This way you don't have to have your player class with a bunch of extra, unused sensors that are being updated.  |
| P2 - Implement functionality in Arena for checking events | 10 / 10 | I'm not a huge fan of having the sensor calculate their own event status (like the TouchSensor claculating whether it should activiate from two entities) (I may have suggested this in office hours without thinking too much about it). A cleaner design would have some sort of "EventSystem" responsible for generating event every update, and sending them to the correct sensors. Sensors then just act as components through which the Robot interacts with the event system (this is kinda how a lot of game engines work). Woah this comment got long. |
| P3 - Implement Accept methods for each sensor | 2 / 2 |  |
| P3 - Implement functionality for Player, including sensors and events | 8 / 8 |  |
| P3 - Implement functionality for Robot | 8 / 8 |  |
| P3 - Implement functionality for SuperBot | 8 / 8 |  |
| P3 - Implement functionality for HomeBase and RechargeStation | 2 / 2 |  |
| P3 - Implement win / loss conditions | 2 / 2 |  |
| Additional Marks | 0 / 0 | Good iteration 2. My way too long comments could turn into good ideas for iteration 3. |
| **Total** | 100 / 100 |   |

