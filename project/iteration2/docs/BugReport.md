BugFixes.md File

General Overview:-

1. The Project Design Overview is present in my DesignDocument file present in the docs folder. The file Mainpage.h
contains the same information which can be accessed through the doxygen documentation.
2. I use a file to provide the input parameter for the entities, the file name is params-file.txt. Please
use that file to change the initialization of entities.

Overview of Bugs and Implementation of All Priority Levels
- Because of the way I make the entities avoid other entities they sometimes, get stuck somewhere, until their
heading is drastically changed because of some collision/proximity of another entity.
- The entities robot and superbot may sometime approach the player entity slowly as compared to their max_speed
because the proximity sensor has been activated because of some other entity, and then the player comes in
proximity of the event.
