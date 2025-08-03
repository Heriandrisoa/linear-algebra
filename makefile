matrice:Matrice.o main.o EqLin.o
	g++ Matrice.o main.o  EqLin.o -o matrice
Matrice.o:Matrice.cpp Matrice.h
	g++ -c Matrice.cpp
EqLin.o:EqLin.cpp EqLin.h
	g++ -c EqLin.cpp
main.o:main.cpp
	g++ -c main.cpp
clean:
	rm Matrice.o main.o matrice
run:
	./matrice