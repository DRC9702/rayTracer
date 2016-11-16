#!/bin/bash

#make -C .. -f ../Makefile || exit
make -C .. || exit

cp ../prog_out .

for file in ./*.scn; do
	echo ${file##*/}
	./prog_out ${file##*/} "test.exr"
	exrdisplay test.exr
done
