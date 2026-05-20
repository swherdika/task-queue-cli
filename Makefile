CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++17

SRC = $(wildcard src/*.cpp)
OUT = build/task-queue-cli

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)