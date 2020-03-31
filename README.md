# P2-Go Chase It

## Tasks

Create two ROS packages

- `drive_bot`
	
Design a differential drive robot with two sensors: a lidar and a camera. Place the robot in the world designed in the earlier [project](https://github.com/jsaurabh/P1-Build-My-World). Add a white colored ball to the world.

- `ball_chaser`
Write a `drive_bot` node that will provide a service to drive the above mentioned robot by controlling its linear and angular velocities. Write a `process_image` that analyzes the robot's camera view and makes decisions to follow the ball.



