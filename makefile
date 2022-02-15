CC=g++
CFLAGS=-c -Wall -O3
LDFLAGS= -pthread
SOURCES=jordan.cpp vivod.cpp norma.cpp solve.cpp nashb.cpp jordanf.cpp
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURSES:.cpp=.d)
EXECUTABLE=prog

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

