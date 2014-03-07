#! /bin/bash

for (( i = 0; i < 10; i++ )); do
  port=`expr 2929 + $i`
  cd $i
  ./weierstrass --plotStats 0 --nbGen 50 --serverPort $port &
  cd ..
done
