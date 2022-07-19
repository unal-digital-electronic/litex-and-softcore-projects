# Configuración de FPGA a través de esp8266

## Compilación de openocd con remote_bigbang

```bash
# Clonar
git clone https://git.code.sf.net/p/openocd/code openocd-code
cd openocd-code
# Compilar
./bootstrap
./configure --enable-remote-bitbang
make
sudo make install
```

## How to use

```bash
sh program.sh file.svf
```

## Referencias

[Archivos fuente de openocd](https://sourceforge.net/p/openocd/code/ci/master/tree/)
