#!/bin/bash

echo -e "\e[38;5;3m\e[1mCleaning Build Directory\e[m"
rm -rf build/
mkdir build
cd build
cmake ../
cp -r ../textures/ ./textures/
make -j 4
echo -e "\e[38;5;10m\e[1mDONE!\e[m Your executable is '\e[38;5;14m\e[1mOpenGLTest\e[m' inside the build directory. You can run it by entering 'build/\e[38;5;14m\e[1mOpenGLTest\e[m'"
