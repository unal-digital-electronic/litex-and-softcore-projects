# Programación de ColorLight 5A-75E desde Omega2

### Archivos a usar

* **program.sh** guión que contiene el procedimiento para habilitar los gpio de la omega2 para el jtag y ejecuta openocd con la configuración de la fpga
* **ecp5-25f.cfg** configuración que usará openocd para programar la flash o la fpga directamente
* **sysfsgpio-onion.cfg** configuración de los gpio usados para el jtag, éste archivo es llamado por ecp5-25f.cfg como una fuente

## Requerimientos

* **OpenOCD** instalado en omega2 (En éste repositorio en el directorio **../omega-packs/** encontrará los precompilados de openocd para instalar en omega2)
* **ssh server** en omega2 (Generalmente viene preinstalado en la omega2)

## Pasos 

### 1. Subir archivos desde el PC a la omega2

Debe conocer la dirección ip de la omega2 y ésta ser accesible desde su PC
```bash
scp program.sh ecp5-25f.cfg sysfsgpio-onion.cfg root@ip_de_omega2:/root/
```

### 2. Programar FPGA desde Omega2


Teniendo el **archivo.svf** sintetizado y listo para subir a la fpga se procede de la siguiente manera

```bash
scp archivo.svf root@ip_de_omega2:/root/
```


Hacer loggin por ssh a la omega2

```bash
ssh root@ip_de_omega2
```

Programar fpga

```bash
sh program.sh archivo.svf
```

## Ejemplo

Puede testear el funcionamiento de las herramientas instaladas haciendo uso del archivo **blink.svf** en éste
directorio el cual fue sintetizado para hacer el hola mundo en la tarjeta ColorLight 5A-75E.

### Pasos para ejecutar el ejemplo

Subiendo blink.svf a la omega2

```bash
scp blink.svf root@192.168.3.1:/root/
```

Hacer loggin por ssh a la omega2

```bash
ssh root@192.168.3.1
```

Programar FPGA

```bash
root@Omega-49E1:~# sh program.sh blink.svf 
set gpiomux pwm0 -> gpio
set gpiomux pwm1 -> gpio
Open On-Chip Debugger 0.10.0-05040-gf98f83eada-dirty (2017-10-12-15:09)
Licensed under GNU GPL v2
For bug reports, read
        http://openocd.org/doc/doxygen/bugs.html
SysfsGPIO nums: tck = 17, tms = 2, tdi = 16, tdo = 15
SysfsGPIO num: trst = 1
SysfsGPIO num: srst = 19
Info : SysfsGPIO JTAG/SWD bitbang driver
Info : JTAG only mode enabled (specify swclk and swdio gpio to add SWD mode)
Warn : gpio 19 is already exported
Info : This adapter doesn't support configurable speed'
Info : JTAG tap: lfe5u25.tap tap/device found: 0x41111043 (mfg: 0x021 (Lattice Semi.), part: 0x1111, ver: 0x4)
Warn : gdb services need one or more targets defined
   TapName             Enabled  IdCode     Expected   IrLen IrCap IrMask
-- ------------------- -------- ---------- ---------- ----- ----- ------
 0 lfe5u25.tap            Y     0x41111043 0x41111043     8 0x05  0xff
svf processing file: "blink.svf"
95%    
Time used: 0m33s638ms 
'svf file programmed successfully for 618 commands with 0 errors'
shutdown command invoked
sh: write error: Invalid argument
root@Omega-49E1:~#
```

## Referencias

[Configuración openocd para ecp5-x](https://github.com/f32c/f32c/tree/master/rtl/proj/lattice/programmer/openocd/ulx3s)

[Fuentes verilog para el blink.svf usado](https://github.com/Martoni/MartoniColorlight/tree/master/simpleBlink)

[Configuración de interfaz jtag openocd para omega2](https://github.com/johnnycubides/onion-medialab/tree/master/sw/omega-packs/stm32f100)
