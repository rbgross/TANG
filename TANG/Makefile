CC := g++
CFLAGS := -std=c++11 -Wall $(shell pkg-config glm --cflags) $(shell pkg-config glew --cflags) $(shell pkg-config libglfw --cflags)
LDFLAGS := $(shell pkg-config glew --libs) $(shell pkg-config libglfw --libs)
SOURCES := $(wildcard TANG/*.cpp)
OBJECTS := $(addprefix build/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE := build/TANG

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $^

build/%.o: TANG/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<