#!/bin/bash

rm ../resultados/BMB.txt

for i in $(ls ../datos_MDD/ -C1)
do

disp=$(./P3 ../datos_MDD/$i 0 -BMB -Disp)
tiempo=$(./P3 ../datos_MDD/$i 0 -BMB -Tiempo)

echo "$i; $disp; $tiempo " >> ../resultados/BMB.txt
done
