# Make sure that you run in the terminal source devel/setup.bash before running this file!

import subprocess
import time
nodes = ["/tb/lm_1/angular_converter",
"/tb/lm_1/current_input",
"/tb/lm_1/efficiency_map",
"/tb/lm_1/power_calculator",
"/tb/lm_1/torque_calculator"]

child = subprocess.Popen(["roslaunch", "tb_digital_twin", "launch_full.launch"])
time.sleep(60)
print("Shutting down ROS nodes...")
for n in nodes:
    subprocess.Popen(["rosnode","kill", n])
time.sleep(3)
print("Terminating the process...")
child.terminate()
time.sleep(3)
print("Killing rosmaster...")
subprocess.Popen(["killall", "-9", "rosmaster"])
exit(1)
