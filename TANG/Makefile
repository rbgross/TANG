CC ?= g++
CFLAGS := -Wall -std=c++11 $(shell pkg-config --cflags glm glew libglfw)
LDFLAGS := $(shell pkg-config --libs glew libglfw) -lstdc++ -lXrandr
HEADERS := $(wildcard TANG/*.h) $(wildcard TANG/*.hpp)
SOURCES := $(wildcard TANG/*.cpp)
OBJECTS := $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE := build/TANG

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

build/%.o: TANG/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
