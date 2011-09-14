CC = g++

ORIGINAL_FLAGS := $(CPPFLAGS)
CPPFLAGS = -Wall -pedantic
CPPFLAGS += -g
#CPPFLAGS += -O3
CPPFLAGS += -MD -MP -MF .dep/$(subst /,-,$@).d
CPPFLAGS += $(shell pkg-config --cflags gl glu)
CPPFLAGS += $(ORIGINAL_FLAGS)

LDFLAGS += $(shell pkg-config --libs gl glu)



GLUT_H_DIR ?= /usr/include/GL
CANT_FIND_GLUT_H = I couldnt find GL/glut.h so Im giving up

CANT_FIND_GLUT_SO = I couldnt find libglut.so so Im giving up

FOUND_GLUT = I found GL/glut.h and libglut.so so Im attempting to use the default flags \
  (CPPFLAGS += -I/usr/include) \
  (LDFLAGS += -lglut)

# Hackery cause the cosc linux installs are missing the glut pkg-config file.
ifeq "$(strip $(shell pkg-config --cflags glut))" ""
  $(warning WARNING:: )
	$(warning Your system is missing the pkg-config info for glut. This )
	$(warning is the case on all the UC COSC department linux machines  )
	$(warning so I will now attempt to use default build flags for it.  )
  ifeq "$(strip $(shell ls '$(GLUT_H_DIR)/glut.h'))" ""
		$(warning I couldn\'t find `glut.h` in `$(GLUT_H_DIR)` so I\'m giving up. )
		$(warning Set `GLUT_H_DIR` to the correct location to continue.           )
  else ifeq "$(strip $(shell locate '*/libglut.so'))" ""
		$(error I couldn\'t find `libglut.so` so I\'m giving up. )
  else
		$(warning FOUND_GLUT = I found GL/glut.h and libglut.so so Im attempting to use the default flags )
		$(warning \t\(CPPFLAGS += -I$(GLUT_H_DIR)\) )
		$(warning \t\(LDFLAGS += -lglut\) )
    CPPFLAGS += -I$(GLUT_H_DIR)
    LDFLAGS += -lglut
  endif
else
  CPPFLAGS += $(shell pkg-config --cflags glut)
  LDFLAGS  += $(shell pkg-config --libs   glut)
endif

###############################################################################

C_FILES = $(wildcard src/*.cpp)
OBJECTS = $(C_FILES:.cpp=.o)

###############################################################################

all: build .dep basic
rebuild: clean all


basic: $(OBJECTS:src/%=build/%)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)


build/%.o: src/%.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -rf build/*
	rm -rf .dep/*


build:
	mkdir $@


.PRECIOUS: build/%.o
.PHONY: all rebuild clean

# Include the dependency files, should be the last of the makefile
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
