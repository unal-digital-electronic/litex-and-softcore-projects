# Litex 

En éste ejemplo se encenderá un led
a través de tokens dados desde el prompt

Los tokens son:

* **ledon**: Encender el LED de usuario
* **ledoff**: Apagar el LED de usuario

<video src="./video/vexriscv-cl-5a-75e.mp4" autoplay loop></video>

## Pasos

Si hace uso de conda recuerde tener activo el entorno, ejemplo:

```bash
conda activate fpga
```

Contruir el gateware y el bios

```bash
make build
```

Contruir el programa del blink

```bash
make firmware
```

Lanzar el servidor litex con el programa blink a correr

```bash
make litex
```

Cargar el firmware desde el bios

```bash
serialboot
```

Ejecutar los tokens

```bash
ledon
ledoff
```

Puede ver los demás toquen a usar

Salir

La tecla control se simboliza con ^
```bash
^c ^d ^c
```

## Referencias

[Qué es LiteX](https://github.com/timvideos/litex-buildenv/wiki/LiteX-for-Hardware-Engineers#litescope-sampler)

[Documentación vexriscV](https://github.com/SpinalHDL/VexRiscv)

[vexriscV cpu](https://tomverbeure.github.io/rtl/2018/12/06/The-VexRiscV-CPU-A-New-Way-To-Design.html#designing-a-cpu-the-traditional-way)

