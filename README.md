# Relink
## Quick Start
The project has been tested on 18.04(ROS Melodic). Take Ubuntu 18.04 as an example, run the following commands to setup:
```
  sudo apt-get install libarmadillo-dev ros-melodic-nlopt
  cd ${YOUR_WORKSPACE_PATH}/src
  git clone https://github.com/Galaxy1stShooter/relink.git
  cd ../ 
  catkin_make -DCATKIN_WHITELIST_PACKAGES="message_files"
  catkin_make -DCATKIN_WHITELIST_PACKAGES=""
```

After compilation you can start the visualization by:
```
  source devel/setup.bash && roslaunch visualization visualization.launch
```

, then you can start the robot simulator (we use [Fast-Planner](https://github.com/HKUST-Aerial-Robotics/Fast-Planner) here) by:
```
  source devel/setup.bash && roslaunch plan_manage swarm.launch
```

and start the algorithm by:
```
  source devel/setup.bash && roslaunch optimizer algorithm.launch
```
. You can use `2D Nav Goal` in Rviz to start RELINK.

## Related Paper
[RELINK: Real-Time Line-of-Sight-Based Deployment Framework of Multi-Robot for Maintaining a Communication Network](https://ieeexplore.ieee.org/abstract/document/10290936/), Lijia Xia, Beiming Deng, Jie Pan, Xiaoxun Zhang, Peiming Duan, Boyu Zhou, Hui Cheng, IEEE Robotics and Automation Letters (RA-L), 2023.

Please cite this paper if you find this project useful.

## Acknowledgements
- The robot simulator of this project is based on [Fast-Planner](https://github.com/HKUST-Aerial-Robotics/Fast-Planner) by Zhou Boyu.
- The L-BFGS solver we use is from [LBFGS-Lite](https://github.com/ZJU-FAST-Lab/LBFGS-Lite).
