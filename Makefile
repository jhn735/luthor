CC = g++
FLAGS = -g -Wall

luthor: main.cpp  
	$(CC) $(FLAGS) -o $@ $^ 
