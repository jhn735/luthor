CC = g++
FLAGS = -std=c++11 -I./src/include -g -fpermissive

luthor: src/luthor.cpp src/main.cpp
	$(CC) $(FLAGS) -o $@ $^ 
