all: main.cpp Duck.o MallardDuck.o DecoyDuck.o RubberDuck.o MuteQuack.o Quack.o QuackBehavior.o Squeak.o
	g++ -o lab03.out main.cpp Duck.o MallardDuck.o RubberDuck.o DecoyDuck.o MuteQuack.o Quack.o Squeak.o QuackBehavior.o

Duck.o: Duck.h Duck.cpp
	g++ -c Duck.cpp

DecoyDuck.o: DecoyDuck.h DecoyDuck.cpp
	g++ -c DecoyDuck.cpp

MallardDuck.o: MallardDuck.h MallardDuck.cpp
	g++ -c MallardDuck.cpp

RubberDuck.o: RubberDuck.h RubberDuck.cpp
	g++ -c RubberDuck.cpp

MuteQuack.o: MuteQuack.h MuteQuack.cpp
	g++ -c MuteQuack.cpp

Quack.o: Quack.h Quack.cpp
	g++ -c Quack.cpp

QuackBehavior.o: QuackBehavior.h QuackBehavior.cpp
	g++ -c QuackBehavior.cpp

Squeak.o: Squeak.h Squeak.cpp
	g++ -c Squeak.cpp

clean:
	rm *.o *.out

CXX = g++
CXXFLAGS = -Wall -c -std=c++11
