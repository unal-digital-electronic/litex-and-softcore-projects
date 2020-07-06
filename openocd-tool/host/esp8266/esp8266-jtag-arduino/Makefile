# Johnny Cubides <jgcubidesc@gmail.com>
# b=9600
b=115200
s=/dev/ttyUSB0
# s=/dev/ttyACM0
l=
SRC=jtag_wifi_serial.ino
BAUDRATE=$(b)
DEVICE=$(s)
LIB=$(l)
# TARGET[uno, nano, esp8266]
TARGET=esp8266
TERM=picocom# minicom

ifeq ($(TARGET),uno)
ARDUINO-TARGET=arduino:avr:uno
else ifeq ($(TARGET),nano)
ARDUINO-TARGET=arduino:avr:nano
else
ARDUINO-TARGET=esp8266:esp8266:generic
endif

build:
	arduino-cli compile --fqbn $(ARDUINO-TARGET) $(SRC)

flash:
ifeq ($(TARGET), uno)
	arduino-cli upload -p $(DEVICE) --fqbn $(ARDUINO-TARGET) $(SRC)
else ifeq ($(TARGET), nano)
	arduino-cli upload -p $(DEVICE) --fqbn $(ARDUINO-TARGET) $(SRC)
else ifeq ($(TARGET), esp8266)
	esptool.py --port $(DEVICE) write_flash 0x00000 $(SRC)*bin
else
	@echo "El programador no está en la lista"
endif

clear:
ifeq ($(SRC), )
	rm -rf *.bin *.elf *.hex
else
	rm -rf $(SRC)/*.bin $(SRC)/*.elf $(SRC)/*.hex
endif

serial:
	@ls ${SERIAL} || (echo "\n\nNo se encuentra ${SERIAL} conectado, verifique conexión o cambie el valor de SERIAL=${SERIAL} por un puerto serial existente\n\n"; exit 123;)
ifeq ($(TERM), picocom)
	picocom ${DEVICE} -b $(BAUDRATE)
else ifeq ($(TERM), minicom)
	minicom -o -b ${DEVIC} -D ${DEVICE}
endif

lib2search:
ifeq ($(LIB),)
	@echo "please add l=<lib to search>"
	@echo "example: make lib2search l=TSL2591"
else
	arduino-cli lib search $(LIB)
endif

lib2install:
ifeq ($(LIB),)
	@echo "please add l=<lib to search>"
	@echo "example: make lib2install l=\"Adafruit\\ TSL2591\\ Library\""
else
	arduino-cli lib install $(LIB)
endif

b:build

f:flash

s:serial

c:clear

.PHONY: build flash clear serial b f c s
