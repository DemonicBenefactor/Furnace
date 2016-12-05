vpath %.c src test
SOURCES=main.c\
	characters.c\
	player.c\
	game.c\
	input.c\
	textureManager.c\
	gameObject.c\
	vectors.c



TESTSOURCES=test.c


OBJECTS=$(patsubst %.c, src/obj/%.o, $(SOURCES))
TESTOBJECTS=$(patsubst %.c, test/obj/%.o, $(TESTSOURCES))
CFLAGS=-Wall -g -Bstatic `sdl2-config --cflags --static-libs` -lSDL2_image -Bdynamic -Wno-write-strings -Iinclude
RPI=-lGLESv2
CXX=g++
CC=gcc

All:
	@echo please type:
	@echo make rpi
	@echo make cygwin

rpi: Furnace_rpi Test_rpi
cygwin: Furnace Test

Furnace_rpi: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(RPI) $(CFLAGS) 

Test_rpi: $(TESTOBJECTS)
	$(CC) -o $@ $(TESTOBJECTS) $(RPI) $(CFLAGS)

$(OBJECTS): | src/obj

$(TESTOBJECTS): | test/obj

src/obj:
	@mkdir -p $@

test/obj:
	@mkdir -p $@

src/obj/%.o: %.c
	$(CC) $(RPI) $(CFLAGS) -c $< -o $@ 

test/obj/%.o: %.c
	$(CC) $(RPI) $(CFLAGS) -c $< -o $@

# cleanup
clean:
	rm -rf $(OBJECTS)
	rm -rf $(TESTOBJECTS)
	rm -rf Furnace.bin
	rm -rf Test.bin
	rmdir src/obj
	rmdir test/obj

# EOF
