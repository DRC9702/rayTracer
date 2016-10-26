#!/bin/bash

#make -C .. -f ../Makefile || exit
make -C .. || exit

for file in ./*.scn; do
	echo ${file##*/}
	../prog_out ${file##*/} "test.exr"
	exrdisplay test.exr
done
