# The comparison between ROS and ROS2 based on the propulsion drive of autonomous vehicle

## Introduction 

You are reading README for the experiment conducted for the study *"The comparison between ROS and ROS2 based on the propulsion drive of autonomous vehicle"* for the project [PSG453](https://www.etis.ee/Portal/Projects/Display/72b66c74-e911-49c3-ac6a-6716f9e72ba5?lang=ENG).

This README will guide you through on how to recreate the experiment conducted in the research.

## Prerequisites

Make sure that you have the following components installed:
1. Linux OS (preferrably Ubuntu-based, no older than 20.04)
2. ROS2 Foxy Fitzroy
3. ROS Noetic Ninjemys
4. Created and configured (based on ROS tutorials) workspaces for ROS and ROS2
5. If you would like to process the data using our code, have *Jupyter Notebook* installed.

Please note, that in the folder **/results** we have included the logged data of the original experiment.

## Setting up the experiment

Follow these steps to correctly prepare everything for the latency test:

1. Copy contents of *ROS* folder into the */src* of your ROS workspace.
2. Copy contents of *ROS2* folder into the */src* of your ROS2 workspace.
3. In case you would like to change the output destination, go to */include* folder of both the */loading_motor_dt* and */tb_digital_twin* folders in their respective workspaces, and find the */data_logger* libraries. Once found, proceed to the files *data_logger.cpp* and scroll down. Modify the lines 92 and 106). Otherwise, keep as is.
4. For ROS2, clone the following repo to the */src* of your ROS2 workspace: 

```
git clone https://github.com/TalTech-PSG453/digital_twin_msgs.git
git checkout eval
 ```
5. Compile both workspaces.

## Running the experiment

In every ROS workspace, you can see the Python *run.py* script. The script will automatically run the necessary launch files for a duration 60 seconds and terminate all the nodes (by stopping the nodes and killing the ROS Launch process.)

Run the experiments one at a time by executing the script:

`python3 run.py`

After the experiment is done, you will observe the *logged_data* folders in the workspaces. These files contain the logged results.

## Recreating the iRobot's benchmark evaluation

We provide .json topology of the *loading_motor_dt* system for iRobot's benchmark framework.

For ROS2, clone the following repo to the */src* of your ROS2 workspace:
 ```
git clone https://github.com/irobot-ros/ros2-performance
git checkout foxy
 ```
 And copy the file *irobot_psg_topology.json* to topologies folder of *iRobot*'s benchmark.

**Make sure to read the documentation of *iRobot*'s benchmark framework!**

## Reading the results

The data is logged as .csv files. If you would like to generate same tables visually like found in the article, then do the following:
1. Open the *ROS1_ROS2_comparison.ipynb* notebook using Jupyter Notebook
2. Inside the notebook, change the **full paths** to folders containing the logged data, according to the example.
3. Run the Jupyter Notebook and observe the results.