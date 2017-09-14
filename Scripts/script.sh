!/bin/bash
# Script file for setting up the experiment environment 
#  TK1 and TX1 environments

# Switch off the HDMI display on the board
echo -1 > /sys/kernel/debug/tegra_hdmi/hotplug
echo 4 > /sys/class/graphics/fb0/blank

#Turn off all the CPU cores other than cpu0 ; 0 core is only switched on 
# Need to change these parameters for multicore code 

echo 1 > /sys/devices/system/cpu/cpu0/online
echo 0 > /sys/devices/system/cpu/cpu1/online
echo 0 > /sys/devices/system/cpu/cpu2/online
echo 0 > /sys/devices/system/cpu/cpu3/online

# Setting the max Frequency of the CPU-core0
echo "userspace" > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
echo 564000 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq

# Setting GPU to low frequency 
echo 72000 > /sys/kernel/debug/clock/override.gbus/rate
echo 1 > /sys/kernel/debug/clock/override.gbus/state

