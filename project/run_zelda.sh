#!/bin/bash

cd /home/lucia/Desktop/42-cursus/zelda

make re

if [ $? -eq 0 ]; then
    # Ejecuta el archivo ejecutable
    ./zelda
else
    echo "La compilación falló. Verifica los errores del Makefile."
fi
