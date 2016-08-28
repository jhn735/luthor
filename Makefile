CC = g++
FLAGS = -std=c++11 -I./src/include -g -fpermissive -fmax-errors=5 -O0

luthor: src/luthor.cpp src/symbol.cpp src/main.cpp
	$(CC) $(FLAGS) -o $@ $^ 
