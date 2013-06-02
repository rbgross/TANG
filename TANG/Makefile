CC := gcc-4.8
CFLAGS := -std=c++11 $(shell pkg-config glm --cflags) $(shell pkg-config glew --cflags) $(shell pkg-config libglfw --cflags)
LDFLAGS := -lstdc++ $(shell pkg-config glew --libs) $(shell pkg-config libglfw --libs)
SOURCES := $(wildcard TANG/*.cpp)
OBJECTS := $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE := build/TANG

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $^ -o $@

build/%.o: TANG/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@