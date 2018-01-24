## Exercise to Engage the Code

These are questions that ask you to explore the code in a specific way. They highlight important functionality and flow-of-control. You might want to jot down the answers for your own use as you spend time learning the code. It will probably take you a minimum of 2 hours just to understand how all the pieces fit together. We highly recommend you spend time understanding the framework before adding a single line of code.

# Answer the Following Questions Based on Iteration1 Code

1. What does GraphicsArenaViewer::DrawUsingNanoVG() do?
	
	This function creates all the obstacles (obstacle, recharge station), home base and the robot. It also sets up the font size and font face for the text that appears on
	the robot, home base and the obstacles

2. When does this get called?
	
	This function gets called in each iteration of the nanogui::mainloop(), which runs because of the Run() command in the file main.cc

3. How is it that the Recharge Station is being drawn - there is no command to draw it?
	
	Reacharge Station is a obstacle 9inherits from it), so when we are calling the GraphicsArenaViewer::DrawUinsgNanoVG(), it is drawing all the obstacles in the vector of <obstacles> which contains Recharge Station and thus it gets drawn. Main principles that help this are - Dynamic Instantiation, Inheritance, Function Overidding(name(void))

4. What entities exist in the Arena?
    - For each entity, what is it's base (parent) class?
	
	robot_ - ArenaMobileEntity

	recharge_station_ - Obstacle

	home_base_ - ArenaImmobileEntity

5. Where does the system check for collisions (look in Arena.cc)?
	
	In the function UpdateEntitiesTimestep in Arena class. This function calls the two function CheckForEntityCollision and CheckforEnityOutOfBounds. CheckForEntityCollision checks whether the robot has collided with any other aren entity present in the arena, and if it has then set the EventCollision object to have true for collision. CheckForEntityOutOfBounds check whether there is a collision with one of the walls of the arena

6. When does this happen (i.e. where is it in flow-of-control)?
	
	UpdateEntitiesTimestep is called in the function AdvanceTime, which is called through GraphicsArenaViewer through the UpdateSimulation function (which is called again and again while the windows is open)
	
7. What is the logic for checking for colliding with walls?
	
	We find the point that could be the closest to the walls by finding the center and adding/subtracting the radius of the entity. Then we check whether the result is less than 0 or greater than the max value for x and y to check whether they have collided or not. This could work because we are dealing with circle. if any other shape then this logic would have failed because we cannot find the point closest to the wall just by using the radius and the center.

8. What is the logic for checking for colliding with other entities?
	
	We first find the distance between the centers of the two identities using the distance formula of cartesian plane. Then check whether the difference of distance and the (sum of radius of the two entities) is greater than some small distance(delta). If it is then the entities have not collided. Otherwise they have.

9. Trace the EventCollision from the point at which it is created in Arena to
the robot sensor. What does the sensor record when a collision happens?
	
	First the EventCollision object is created inside Arena::UpdateEntitiesTimestep, and is passed as a parameter to functions like CheckForEntityCollision, CheckForEntityOutOfBounds. If anywhere the robot is colliding with something the EventCollision object's collison is set to true, and at last the method robot_->Accept is called which in truns call the function sensor_touch_->Accept with the parameter EventCollison Object which in turn update the point_of_contact and the angle_of_contact.
	
10. The RobotMotionHandler reads the touch sensor. What does it do with this information?
	
	It changes the heading_angle_ of the robot motion to the negative of the angle_of_contact that we recieve from the SensorTouch (which is updated whenever there is a collision)

11. Identify the method (function) that updates the robot position. Trace flow-of-control
from the call UpdateSimulation in GraphicsArenaViewer.
	
	GraphicsArenaViewer::UpdateSimulation --> Arena::AdvanceTime --> Arena::UpdateEntitiesTimestep --> entities::TimestepUpdates(which can be of robot or other entities) --> Arena::CheckForEntityCollision (yet to be coded for the right result) || Arena::CheckForEntityOutOfBounds (which changes the position and the velocity of the robot ) --> if (there is a collision) then send collision events to each entity for changing their respective position and velocity else do nothing.
		

12. What is the equation used to calculate the deltaX and deltaY for the robot
and update the position?

	deltaX = cos(ent->heading_angle()*M_PI/180.0)*ent->speed()*dt;

  	deltaY = sin(ent->heading_angle()*M_PI/180.0)*ent->speed()*dt;
	  
	These equations take in to consideration the heading angle and use that to calculate the amount of movement in x and y axis using the cosine and sine of the angle and multiplying with speed times time. As soon as the heading angle changes the way of updating the position also changes because of how the heading_angle is used to calculate deltaX and deltaY
  
