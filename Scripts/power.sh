#!/bin/bash
while true; do
    cat /sys/devices/platform/7000c400.i2c/i2c-1/1-0040/iio_device/in_power0_input
	#cat /sys/devices/3160000.i2c/i2c-0/0-0041/iio_device/in_power0_input
    sleep 0.01
done
