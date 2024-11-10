.PHONY: all debug release clean

RELEASE_FLAGS = -O2 -Wall -DNDEBUG
DEBUG_FLAGS   = -g -O0 -Wall
RELEASE_EXEC  = echo1
DEBUG_EXEC    = echo1-dbg
SOURCE        = echo1.cpp

all: debug release

debug: $(DEBUG_EXEC)

$(DEBUG_EXEC): echo1.cpp
	g++ $(DEBUG_FLAGS) echo1.cpp -o $(DEBUG_EXEC) 

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): echo1.cpp
	g++ $(RELEASE_FLAGS) echo1.cpp -o $(RELEASE_EXEC)

clean:
	rm -f $(RELEASE_EXEC) $(DEBUG_EXEC)
