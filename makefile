testing:Matrice.o main.o
	g++ main.o Matrice.o -o testing

main.o:main.cpp Matrice.o
	g++ -c main.cpp

Matrice.o:Matrice.cpp
	g++ -c Matrice.cpp

library:
	g++ -fPIC -c Matrice.cpp
	g++ -shared -o libMatrice.so Matrice.o
run:
	./testing
clean:
	rm *.o