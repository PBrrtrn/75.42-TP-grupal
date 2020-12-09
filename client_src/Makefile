# OBJS = GameLoop.cpp Surface.cpp Window.cpp 05_better.cpp *.h
OBJS = *.cpp *.h

CC = g++

COMPILER_FLAGS = -Werror -Wall

LINKER_FLAGS = -lSDL2 -lSDL2_image -pthread

OBJ_NAME = client

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)