EXEFILE   = Pacman
CPUCC     = /usr/bin/g++
CPPFLAGS  = -O3 -std=gnu++11 -Wall #-w -g #-O3 #-DTARDINESS # -g  -w # -fpermissive
DEFS      = #-D_DEBUG
INCLUDES  = -I. 
LIBDIR   = 
LIBS     =  -lm  -lGL -lGLU  -lglut -lGLEW 
LINK     =  $(LIBDIR) $(LIBS) 

C_COMPILE = $(CPUCC) $(DEFS) $(INCLUDES) $(CPPFLAGS) 



all:  Scene ImageTGA Hero Enemy AStar Agent main #uniform #seed
	$(C_COMPILE) Scene.o ImageTGA.o Hero.o Enemy.o AStar.o Agent.o main.o   $(LINK) -o $(EXEFILE)


main:
	$(C_COMPILE) -c main.cpp


Agent:
	$(C_COMPILE) -c Agent.cpp

AStar:
	$(C_COMPILE) -c AStar.cpp

Enemy:
	$(C_COMPILE) -c Enemy.cpp

Hero:
	$(C_COMPILE) -c Hero.cpp

ImageTGA:
	$(C_COMPILE) -c ImageTGA.cpp

Scene:
	$(C_COMPILE) -c Scene.cpp
	

clean:
	rm *.o; rm $(EXEFILE); 

