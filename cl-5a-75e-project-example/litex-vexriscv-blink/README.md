# Litex 

En éste ejemplo se encenderá un led
a través de tokens dados desde el promt

Los tokens son:

* **ledon**: Encender el LED de usuario
* **ledoff**: Apagar el LED de usuario

## Pasos

Si hace uso de conda recuerde tener activo el entorno, ejemplo:

```bash
conda activate fpga
```

Contruir el gateware y el bios

```
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


