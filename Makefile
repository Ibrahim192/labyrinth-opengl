CFLAGS=-g -O2
LIBS=-lGL -lGLU -lglut -lSOIL -lBox2D

all: src/main.cpp drawboard.o startscreen.o gamecontrol.o physics.o
	-@mkdir build
	g++ $(CFLAGS) src/main.cpp src/*.o $(LIBS) -o build/labyrinth.out

drawboard.o : src/drawboard.cpp
	g++ -c $(CFLAGS) src/drawboard.cpp $(LIBS) -o src/drawboard.o

startscreen.o : src/startscreen.cpp
	g++ -c $(CFLAGS) src/startscreen.cpp $(LIBS) -o src/startscreen.o

gamecontrol.o : src/gamecontrol.cpp
	g++ -c $(CFLAGS) src/gamecontrol.cpp $(LIBS) -o src/gamecontrol.o

physics.o : src/physics.cpp
	g++ -c $(CFLAGS) src/physics.cpp $(LIBS) -o src/physics.o

clean:
	-@rm -f src/*.o
	-@rm -rf build
