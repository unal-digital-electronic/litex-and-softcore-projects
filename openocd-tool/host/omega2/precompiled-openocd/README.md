# OpenOCD para omega2


Los siguientes paquetes fueron cross-compilados para que openocd
pueda ser ejecutado desde la omega2 u omega2+

## Instalación

### Subir los paquetes a la omega2

Debe conocer la dirección ip de la omega2 y ésta ser accesible desde su PC
```bash
scp hidapi_0.8.0-rc1-2_mipsel_24kc.ipk openocd_v0.10.0-1_mipsel_24kc.ipk root@ip_de_omega2:/root/
```

### Instalar openocd en omega2

Hacer loggin por ssh a la omega2

```bash
ssh root@ip_de_omega2
```

Instalar los siguientes paquetes

```bash
root@Omega-49E1:~# opkg install hidapi_0.8.0-rc1-2_mipsel_24kc.ipk
root@Omega-49E1:~# opkg install openocd_v0.10.0-1_mipsel_24kc.ipk
```


