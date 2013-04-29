CC=g++
CFLAGS=-c -W
LDFLAGS=
SOURCES=main.cpp game.cpp agent.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=blackjack

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	mv $(EXECUTABLE) ../

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

