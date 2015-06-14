vpath %.c src
SOURCES=main.c 

OBJECTS=$(patsubst %.c, src/obj/%.o, $(SOURCES))
CPPFLAGS=-Wall -g `sdl2-config --cflags --libs` -lSDL2 -Wno-write-strings
CXX=g++
CC=gcc

All: Furnace.bin

Furnace.bin: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(CPPFLAGS) 

$(OBJECTS): | src/obj

src/obj:
	@mkdir -p $@

src/obj/%.o: %.c
	$(CC) $(CPPFLAGS) -c $< -o $@ 


# cleanup
clean:
	rm -rf $(OBJECTS)
	rm -rf Furnace.bin
	rmdir src/obj

# EOF
