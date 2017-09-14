# Stress Detection Readme 

This repository contains CPU code of SVM and KNN implementation of Stress Detection 
We compared the performance of SVM and KNN of the stress application on NVIDIA Jetson TX1 and TX2 
Running "Scripts/script.sh" file sets the Jetson TX1 environment for experimental conditions i.e., switching
off the HDMI; turing one core and switching off all the cores; turing GPU to it's lowest frequency; and 
setting core 0 frequency to 564MHz

Change the core 0 CPU frequency to the desired frequency by changeing 564000 to the required frequency.

The Scripts/power.sh contains two commands for TX1 and TX2;
For TX1 (v300 and above) use the cammand including "7000c400.i2c" device

For TX2 use the command including "3160000.i2c" device and comment the other statement

To compile and execute SVM and KNN Cpu codes, 

Compile: gcc -o svm svm.c
Run: ./svm

