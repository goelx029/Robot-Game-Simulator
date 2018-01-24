BugFixes.md File

General Overview:-

1. The Project Design Overview is present in my DesignDocument file present in the docs folder. The file Mainpage.h
contains the same information which can be accessed through the doxygen documentation.
2. I use a file to provide the input parameter for the entities, the file name is params-file.txt. Please
use that file to change the initialization of entities.

Overview of Bugs and Implementation of All Priority Levels
- There are really no known bugs. Most of the bugs that were removed as part of the iteration3 were - strange behavior of the robots and superbots because of the sensor proximity updating itself because of one entity and then not setting itself to the correct state when some other entity comes in proximity as well. Most of these interactions include - "Robot in proximity of Superbot and then the Player comes in the proximity which would make the Superbot chase player with slower speed because of the change in state earlier because of the present of robot in the proximity of superbot."

- Not exactly a bug but when there are many entities present near each other involving the robot as super bot, they might get stuck because of the way I make them avoid collisions. This happens because of sensor proximity activating again and again and instructing the entity to change the direction such that in that direction the sensor proximity activates itself and instructs the entity to go the opposite direction which makes like an infinite loop there until some external entity comes and changes the state of the sensor proximity for robot and superbot.