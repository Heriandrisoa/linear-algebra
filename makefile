TARGET = testing
LIB = libMatrice.so

CXX = g++

CXXFLAGS = -Wall -Wextra -fPIC

OBJS = main.o Algebra.o Operator.o Constructor.o

all: $(TARGET) $(LIB)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

$(LIB): Algebra.o Operator.o Constructor.o
	$(CXX) -shared $^ -o $(LIB)

main.o: main.cpp header/Matrice.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Algebra.o: source/Algebra.cpp header/Matrice.h
	$(CXX) $(CXXFLAGS) -c source/Algebra.cpp

Operator.o: source/Operator.cpp header/Matrice.h
	$(CXX) $(CXXFLAGS) -c source/Operator.cpp

Constructor.o: source/Constructor.cpp header/Matrice.h
	$(CXX) $(CXXFLAGS) -c source/Constructor.cpp


run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET) $(LIB)
