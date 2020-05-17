# Brief:	Makefile para crear proyectos con litex, riscv32 en placas ecp5
# Author: Johnny Cubides
# e-mail: jgcubidesc@gmail.com
# date: Friday 15 May 2020

TARGET=top
TOP=top
BUILD_DIR=build/gateware

# Poner la dirección del puerto serial que está usando
# o agregarlo en la línea de comandos ejemplo: make SERIAL=/dev/ttyUSB0x
SERIAL?=/dev/ttyUSB0

# Poner la dirección ip de la omega2 para poder conectarse a ella desde ssh
# o agregarlo en la línea de comandos ejemplo: make IP=x.x.x.x
IP_OMEGA?=192.168.3.1

# Poner el directorio destino de la omega2 para subir el bitstream, el lugar ideal es aquel donde tenga el script program.sh
# o agregarlo en la línea de comandos ejemplo: make IP=/root/
PATH_DEST?=/root/

NEXTPNR=nextpnr-ecp5
CC=riscv32-unknown-elf-gcc

all: firmware ${BUILD_DIR}/${TARGET}-flash.svf

${BUILD_DIR}/${TARGET}.bit:
	@yosys -V || (echo "\nNo se puede encontrar yosys, si está usando conda active en ésta terminal el entorno donde se instaló las herramientas, ejemplo:\n\n\
	conda activate fpga \n\n\
	para más información visite la siguiente url:"; exit 123;)
	@${NEXTPNR} -V || (echo "\nNo se puede encontrar ${NEXTPNR}, si está usando conda active en ésta terminal el entorno donde se instaló las herramientas, ejemplo:\n\n\
	conda activate fpga \n\n\
	para más información visite la siguiente url:"; exit 123;)
	./base.py

firmware:
	@${CC} -v || (echo "\nNo se puede encontrar el compilador de ${CC}, si está usando conda active en ésta terminal el entorno donde se instaló las herramientas, ejemplo:\n\n\
	conda activate fpga \n\n\
	para más información visite la siguiente url:"; exit 123;)
	$(MAKE) -C firmware/ -f Makefile all


${BUILD_DIR}/${TARGET}-flash.svf : ${BUILD_DIR}/${TARGET}.bit
	./bit_to_flash.py ${BUILD_DIR}/$(TARGET).bit ${BUILD_DIR}/${TARGET}-flash.svf

litex_term: firmware
	@ls ${SERIAL} || (echo "\n\nNo se encuentra ${SERIAL} conectado, verifique conexión o cambie el valor de SERIAL=${SERIAL} por un puerto serial existente\n\n"; exit 123;)
	litex_term ${SERIAL} --kernel firmware/firmware.bin

# prog FPGA FLASH from omega2
prog-f-o2: ${BUILD_DIR}/${TARGET}-flash.svf
	@echo "Programar la FLASH de la FPGA desde la omega2"
	@echo "scp ${BUILD_DIR}/${TARGET}-flash.svf root@${IP_OMEGA}:${PATH_DEST}"
	@scp ${BUILD_DIR}/${TARGET}-flash.svf root@${IP_OMEGA}:${PATH_DEST} || (echo "No fue posible enviar ${TARGET}-flash.svf a la omega2"; exit 123;)
	@echo "Para programar la fpga puede abrir otra consola y en ella acceder por ssh a la omega2, ejemplo:\n\n\
	ssh root@${IP_OMEGA}\n\n\
	Cuando esté en la terminal de la omega2 puede ubicarse en el lugar donde se subió el archivo ${TARGET}-flash.svf el cual fue el directorio ${PATH_DEST} y desde allí programar \
	la fpga con el script de programación, ejemplo:\n\n\
	cd ${PATH_DEST}\n\
	sh program.sh ${TARGET}-flash.svf\n\n"

# prog FPGA ram from omega2
prog-r-o2: ${BUILD_DIR}/${TARGET}.svf
	@echo "Programar la RAM de la FPGA desde la omega2"
	@echo "scp ${BUILD_DIR}/${TARGET}.svf root@${IP_OMEGA}:${PATH_DEST}"
	@scp ${BUILD_DIR}/${TARGET}.svf root@${IP_OMEGA}:${PATH_DEST} || (echo "No fue posible enviar ${TARGET}.svf a la omega2"; exit 123;)
	@echo "Para programar la fpga puede abrir otra consola y en ella acceder por ssh a la omega2, ejemplo:\n\n\
	ssh root@${IP_OMEGA}\n\n\
	Cuando esté en la terminal de la omega2 puede ubicarse en el lugar donde se subió el archivo ${TARGET}.svf el cual fue el directorio ${PATH_DEST} y desde allí programar \
	la fpga con el script de programación, ejemplo:\n\n\
	cd ${PATH_DEST}\n\
	sh program.sh ${TARGET}.svf\n\n"

clean:
	rm -f ${BUILD_DIR}/*.svf ${BUILD_DIR}/*.bit ${BUILD_DIR}/*.config ${BUILD_DIR}/*.json ${BUILD_DIR}/*.ys
	make -C firmware -f Makefile clean

.PHONY: clean firmware
