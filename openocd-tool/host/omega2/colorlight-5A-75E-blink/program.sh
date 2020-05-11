#!/bin/sh
# BOOT GPIO0
# TRST GPIO1
# BOOT0 = 0 Main flash
# BOOT0 = 1 Embedded SRAM
omega2-ctrl gpiomux set pwm0 gpio
omega2-ctrl gpiomux set pwm1 gpio
# Boot0 = 1
echo "0" >  "/sys/class/gpio/unexport"
echo "0" >  "/sys/class/gpio/export"
echo "out" > "/sys/class/gpio/gpio0/direction"
echo "1" >   "/sys/class/gpio/gpio0/value"
# Reset
echo "19" >  "/sys/class/gpio/unexport"
echo "19" >  "/sys/class/gpio/export"
echo "out" > "/sys/class/gpio/gpio19/direction"
echo "1" >   "/sys/class/gpio/gpio19/value"
sleep 1 
echo "0" >  "/sys/class/gpio/gpio19/value"
sleep 1  
echo "1" >   "/sys/class/gpio/gpio19/value"
openocd -f ecp5-25f.cfg
# Boot0 = 1
echo "0" >  "/sys/class/gpio/unexport"
echo "0" >  "/sys/class/gpio/export"
echo "out" > "/sys/class/gpio/gpio0/direction"
echo "0" >   "/sys/class/gpio/gpio0/value"
# Reset
echo "19" >  "/sys/class/gpio/unexport"
echo "19" >  "/sys/class/gpio/export"
echo "out" > "/sys/class/gpio/gpio19/direction"
echo "1" >   "/sys/class/gpio/gpio19/value"
sleep 1 
echo "0" >  "/sys/class/gpio/gpio19/value"
sleep 1  
echo "1" >   "/sys/class/gpio/gpio19/value"


