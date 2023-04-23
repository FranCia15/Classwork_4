# Classwork_4

Create a new ROS package containing robot configuration files and two nodes. With the configuration files you must add a new robot model in the ROS system visualizing it on RVIz. 
The two nodes of the package will perform the following operation:
-	Node 1: Implement a service server that accepts as input two strings: frame_a and frame_b. This service will return the position and orientation  of the frame_b in the frame_a reference frame.
-	Node 2: Use the service advertised by the Node 1, to get the transformation between two frames. This transformation is then shown on RVIz with a dynamic tf.

Video of the working model:

https://user-images.githubusercontent.com/124872841/233840511-d3057c1f-6d77-4ec9-ae14-923bc423fb38.mp4
