#!/bin/sh
git clone https://github.com/ivmai/bdwgc/
cd bdwgc
./autogen.sh
make clean
./configure --prefix=`pwd`/../bdwgc-install --disable-shared --enable-large-config --enable-threads=win32
make
rm -rf `pwd`/../bdwgc-install
make install
cd ..
gcc -O2 -march=native -c alloc.c -I`pwd`/bdwgc-install/include/
gcc -O2 -o main.exe main.c -I`pwd`/bdwgc-install/include/ alloc.o `pwd`/bdwgc-install/lib/libgc.a
