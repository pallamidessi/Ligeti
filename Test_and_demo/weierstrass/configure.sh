#! /bin/bash

make clean;
rm Makefile *.cpp *.hpp *.dat *.csv *.r *.plot ;
easea weierstrass.ez;
make;
