TARGET=blink
TOP=blink

OBJS+=blink.v rst_gen.v

# TRELLIS=/usr/local/share/trellis

# all: ${TARGET}.bit ${TARGET}.svf
all: ${TARGET}-flash.svf

$(TARGET).json: $(OBJS)
	yosys -p "synth_ecp5 -json $@" $(OBJS)

$(TARGET)_out.config: $(TARGET).json
	nextpnr-ecp5 --25k --package CABGA256 --speed 6 --json $< --textcfg $@ --lpf $(TARGET).lpf --freq 65

$(TARGET).bit: $(TARGET)_out.config
	ecppack --svf ${TARGET}.svf $< $@

${TARGET}.svf : ${TARGET}.bit

clean:
	rm -f *.svf *.bit *.config *.json *.ys

${TARGET}-flash.svf : ${TARGET}.bit
	./bit_to_flash.py $(TARGET).bit ${TARGET}-flash.svf

.PHONY: prog clean
