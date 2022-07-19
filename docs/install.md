# Instalación de herramientas

Para las herramientas que hemos usado para los ejercicios propuesto
pondremos unos ejemplos de instalación para que el usuario pueda tenerlas presente


## Simulador ngspice

[Documentación oficial de ngspice](http://ngspice.sourceforge.net/docs/ngspice-manual.pdf)

### Instalación desde gestor de paquetes

```bash
sudo apt install ngspice
```

### Compilación desde archivos fuentes

Descarga desde sourceforge los archivos fuente del proyecto [ngspice](https://sourceforge.net/projects/ngspice/files/)

```bash
tar xvf ngspice-xx.tar.gz
cd ngspice-xx/
mkdir release && cd release
../configure  --with-x --with-readline=yes --disable-debug --enable-xspice
make
sudo make install
```
**Nota**: puedes borrar los archivos que ya no necesitas como el *ngspice-xx.tar.gz*

## Visualizadores ondas analogas

* gwave
* gaw
* gnuplot

### Gwave

![gwave-overview](http://gwave.sourceforge.net/gwave.png)


[Link oficial del proyecto](http://gwave.sourceforge.net/)

#### Instalación

```bash
sudo apt install gwave
```

### gaw

![gaw](http://gaw.tuxfamily.org/linux/gaw1.png)

#### Instalación

```bash
cd /tmp/
wget http://download.tuxfamily.org/gaw/download/gaw3-20200922.tar.gz
tar xvf gaw3-20200922.tar.gz
cd gaw3-20200922.tar.gz
./configure
make
sudo make install
```

### gnuplot

![gnuplot](http://www.gnuplot.info/figs/gaussians.png)

#### Instalación

```bash
sudo apt install gnuplot
```
