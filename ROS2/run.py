# Make sure that you run in the terminal source devel/setup.bash before running this file!

import subprocess
import time
import signal
import os

print("Launch ROS2 loading_motor_dt system...")
child = subprocess.Popen(["ros2", "launch", "loading_motor_dt", "loading_motor_launch.py"])
pgid = os.getpgid(child.pid)
time.sleep(60)
print("Create keyboardInterrupt...")
os.killpg(pgid, signal.SIGINT)
time.sleep(3)
print("Finally terminate...")
child.terminate()
