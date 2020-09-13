Zephyr on Colorlight 5a-75e

Adapted from https://blog.pcbxprt.com/

1. Change base.py pins for uart settings
	I used F15(J1.8) for Tx and G3(J1.3) for Rx
2. Change pins on colorlight_5a_75e.py file of suported boards in litex settings that match with step 1

3. build gateware -> ./base.py --build 

4. load bitstream to FPGA.
	I used Omega 2+ Board to load svf file. The file is on	build/colorlight_5a_75e/gateware/colorlight_5a_75e.svf. To load this I used program.sh and ecp5-25f.cfg files on Omega 2+ board
5. load firmware


