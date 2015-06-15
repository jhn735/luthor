CC = g++
FLAGS = -std=c++11 -I./src/include -g

luthor: src/main.cpp src/luthor.cpp 
	$(CC) $(FLAGS) -o $@ $^ 
