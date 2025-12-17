CXX = g++
BASE_FLAGS = -std=c++20 -Wall -Wextra -Wpedantic
DEBUG_FLAGS = -g -O0 -DDEBUG
TARGET = main
SRC = main.cpp

.PHONY: all run debug clean

all: run

$(TARGET):
	$(CXX) $(BASE_FLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

debug:
	$(CXX) $(BASE_FLAGS) $(DEBUG_FLAGS) -o $(TARGET) $(SRC)
	lldb ./$(TARGET)

clean:
	rm -f $(TARGET)