#OBJS specifies which files to compile as part of the project
 OBJS = main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = coelho

CC = g++
WALL = -Wall

FLAGS = -g -lSDL -lGL -lGLU -lglut -o
#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) $(OBJ_NAME)
