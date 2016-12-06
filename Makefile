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
OBJECTSRPI=$(patsubst %.c, src/obj_rpi/%.o, $(SOURCES))
TESTOBJECTS=$(patsubst %.c, test/obj/%.o, $(TESTSOURCES))
TESTOBJECTSRPI=$(patsubst %.c, test/obj_rpi/%.o, $(TESTSOURCES))
CFLAGS=-Wall -g -Bstatic `sdl2-config --cflags --static-libs` -lSDL2_image -Bdynamic -Wno-write-strings -Iinclude
RPI=-lGLESv2 -Drpi
CYGWIN=-Wall -g -lm -lSDL2 -lSDL2_image -lglew32 -lopengl32 -DSDL_MAIN_HANDLED -Iinclude -Llibs
CXX=g++
CC=gcc
MINGCXX=i686-w64-mingw32-g++
MINGCC=i686-w64-mingw32-gcc

All:
	@echo please use the following for your platform:
	@echo make rpi
	@echo make cygwin

rpi: Furnace_rpi Test_rpi
cygwin: Furnace Test

#===========================================================================

Furnace_rpi: $(OBJECTSRPI) 
	$(CC) -o $@ $(OBJECTSRPI) $(RPI) $(CFLAGS) 

Test_rpi: $(TESTOBJECTSRPI)
	$(CC) -o $@ $(TESTOBJECTSRPI) $(RPI) $(CFLAGS)

Furnace: $(OBJECTS)
	$(MINGCC) -o $@ $(OBJECTS) $(CYGWIN)

Test: $(TESTOBJECTS)
	$(MINGCC) -o $@ $(TESTOBJECTS) $(CYGWIN) 
#===========================================================================

$(OBJECTSRPI): | src/obj_rpi
$(TESTOBJECTSRPI): | test/obj_rpi
$(OBJECTS): | src/obj
$(TESTOBJECTS): | test/obj

src/obj_rpi:
	@mkdir -p $@
test/obj_rpi:
	@mkdir -p $@
src/obj:
	@mkdir -p $@
test/obj:
	@mkdir -p $@

src/obj_rpi/%.o: %.c
	$(CC) $(RPI) $(CFLAGS) -c $< -o $@ 
test/obj_rpi/%.o: %.c
	$(CC) $(RPI) $(CFLAGS) -c $< -o $@
src/obj/%.o: %.c
	$(MINGCC) $(CYGWIN) -c $< -o $@ 
test/obj/%.o: %.c
	$(MINGCC) $(CYGWIN) -c $< -o $@


# cleanup ==================================================================
clean:
	@echo please use the following for your platform:
	@echo make clean_rpi
	@echo make clean_cygwin

clean_cygwin:
	
	rm -rf $(OBJECTS)
	rm -rf $(TESTOBJECTS)
	rm -rf Furnace.exe
	rm -rf Test.exe
	rmdir src/obj
	rmdir test/obj
	
clean_rpi:
	rm -rf $(OBJECTSRPI)
	rm -rf $(TESTOBJECTSRPI)
	rm -rf Furnace_rpi
	rm -rf Test_rpi
	rmdir src/obj_rpi
	rmdir test/obj_rpi
# EOF
