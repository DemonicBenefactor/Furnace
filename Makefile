vpath %.c src test
SOURCES=main.c\
	game.c\
	handleEvents.c\
	textureManager.c\
	gameObject.c\
	vectors.c


TESTSOURCES=test.c


OBJECTS=$(patsubst %.c, src/obj/%.o, $(SOURCES))
TESTOBJECTS=$(patsubst %.c, test/obj/%.o, $(TESTSOURCES))
CFLAGS=-Wall -g -Bstatic `sdl2-config --cflags --static-libs` -lSDL2 -lSDL2_image -lm -Bdynamic -Wno-write-strings -Iinclude
CXX=g++
CC=gcc

All: Furnace.bin Test.bin

Furnace.bin: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) 

Test.bin: $(TESTOBJECTS)
	$(CC) -o $@ $(TESTOBJECTS) $(CFLAGS)

$(OBJECTS): | src/obj

$(TESTOBJECTS): | test/obj

src/obj:
	@mkdir -p $@

test/obj:
	@mkdir -p $@

src/obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

test/obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleanup
clean:
	rm -rf $(OBJECTS)
	rm -rf $(TESTOBJECTS)
	rm -rf Furnace.bin
	rm -rf Test.bin
	rmdir src/obj
	rmdir test/obj

# EOF
