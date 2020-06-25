#!/bin/sh
# sh program.sh file.svf

openocd -f openocd.cfg -c "init; scan_chain; svf -tap lfe5u25.tap -quiet -progress $1; shutdown; quit"
