#!/bin/bash

rm ../Resultados/BFS_0.1.dat

x=2

while [ $x -le 5000 ]
do
Tiempo=$(./Tiempos -BFS $x 0.1)
echo "$x   $Tiempo" >> ../Resultados/BFS_0.1.dat
x=$(( $x + 500 ))
done



rm ../Resultados/BFS_0.9.dat

x=2

while [ $x -le 2000 ]
do
Tiempo=$(./Tiempos -BFS $x 0.9)
echo "$x   $Tiempo" >> ../Resultados/BFS_0.9.dat
x=$(( $x + 200 ))
done



rm ../Resultados/DJK_0.1.dat

x=2

while [ $x -le 5000 ]
do
Tiempo=$(./Tiempos -DJK $x 0.1)
echo "$x   $Tiempo" >> ../Resultados/DJK_0.1.dat
x=$(( $x + 500 ))
done



rm ../Resultados/DJK_0.9.dat

x=2

while [ $x -le 2000 ]
do
Tiempo=$(./Tiempos -DJK $x 0.9)
echo "$x   $Tiempo" >> ../Resultados/DJK_0.9.dat
x=$(( $x + 200 ))
done



rm ../Resultados/BF.dat

x=2

while [ $x -le 1000 ]
do
Tiempo=$(./Tiempos -BF $x 0.1)
echo "$x   $Tiempo" >> ../Resultados/BF.dat
x=$(( $x + 100 ))
done



rm ../Resultados/MatS.dat

x=2

while [ $x -le 150 ]
do
Tiempo=$(./Tiempos -MatS $x 0.1)
echo "$x   $Tiempo" >> ../Resultados/MatS.dat
x=$(( $x + 15 ))
done



rm ../Resultados/MatF.dat

x=2

while [ $x -le 300 ]
do
Tiempo=$(./Tiempos -MatF $x 0.1)
echo "$x   $Tiempo" >> ../Resultados/MatF.dat
x=$(( $x + 30 ))
done



rm ../Resultados/FW.dat

x=2

while [ $x -le 500 ]
do
Tiempo=$(./Tiempos -FW $x 0.1)
echo "$x   $Tiempo" >> ../Resultados/FW.dat
x=$(( $x + 50 ))
done



rm ../Resultados/CT.dat

x=2

while [ $x -le 500 ]
do
Tiempo=$(./Tiempos -CT $x 0.9)
echo "$x   $Tiempo" >> ../Resultados/CT.dat
x=$(( $x + 50 ))
done