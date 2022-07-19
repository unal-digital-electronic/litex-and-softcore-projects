# Blink

Este es el hola mundo para la placa colorlight 5A-75E: Consiste en el encendido y apagado de un LED de manera periódica.

Para sintetizar el ejemplo ejecute `make all`

Obtendrá a la salida tres archivos:

* **blink.bit** bitstream para configurar fpga (programable desde openFPGALoader).
* **blink.svf** formato de vector serialiazado que permite la configuración de la fpga de manera volátil.
* **blink-flash.svf** formato de vector serialiazado que permite la configuración de la fpga de manera permanente.

Para poder programar la FPGA deberás contar con un hardware que sirva de interfaz y además un software que
cumplirá esa tarea; te presentamos a continuación algunas opciones:

* [openOCD](https://github.com/unal-digital-electronic/litex-and-softcore-projects/tree/master/openocd-tool)
* [openFPGALoader](https://github.com/unal-digital-electronic/litex-and-softcore-projects/tree/master/synthesis-compilation-and-programming-tools/openFPGALoader)

Si aún no comprendes cómo desarrollar este ejemplo visita la
[wiki](https://github.com/unal-digital-electronic/litex-and-softcore-projects/wiki) en la sección
*Hola mundo (blink)*

## Referencias

[Qué es un archivo .svf](https://www.intel.com/content/www/us/en/programmable/quartushelp/13.0/mergedProjects/reference/glossary/def_svf.htm)
