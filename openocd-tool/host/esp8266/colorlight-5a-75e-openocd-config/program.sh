#!/bin/sh
# sh program.sh file.svf host
# Author: Johnny Cubides <jgcubidesc@gmail.com>

# openocd -f openocd.cfg -c "init; scan_chain; svf -tap lfe5u25.tap -quiet -progress $1; shutdown; quit"

if [ "$1" = "" ];
then
  echo "¿Cómo usar éste script? Ejemplo:"
  echo "sh program.sh file.svf 192.168.4.1"
fi

if [ `echo $1 | grep -c ".svf"` -gt 0 ];
then
  echo "Extensión del archivo de configuración válida $1"
else
  echo "El archivo a enviar debe tener la extensión .svf"
  return 1;
fi

programming() {
  openocd -d4 \
    -c "interface remote_bitbang; remote_bitbang_port 3335; remote_bitbang_host $2;"\
    -c "jtag newtap lfe5u25 tap -expected-id 0x41111043 -irlen 8 -irmask 0xFF -ircapture 0x5;"\
    -c "init; scan_chain; svf -tap lfe5u25.tap -quiet -progress $1; shutdown; quit"
}

if [ "$2" = "" ];
then
  echo "Como no asignó un host, el indicado por defecto es el 192.168.4.1. desea continuar?"
  read -p "¿Dese acontinuar? y/n: " -r variable
  if [ "$variable" = "y" ];
  then
    programming $1 192.168.4.1
  else
    echo "Salida voluntaria de usuario"
    return 1;
  fi
else
  programming $1 $2
fi
