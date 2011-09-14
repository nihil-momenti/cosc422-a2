# Hackery cause the cosc linux installs are missing the glut pkg-config file.
define MISSING_PKG_CONFIG

    WARNING::
        Your system is missing the pkg-config info for glut. This
        is the case on all the UC COSC department linux machines
        so I will now attempt to use default build flags for it.

endef
define GLUT_H_MISSING

        I couldn't find `GL/glut.h` in `$(GLUT_H_DIR)` so I'm giving up.
        Set `GLUT_H_DIR` to the correct location to continue.

endef
define LIBGLUT_MISSING

        I couldn't find `libglut.so` so I'm giving up.

endef
define FOUND

        I found $(GLUT_H_DIR)/GL/glut.h and libglut.so so Im attempting to use the default flags
            CPPFLAGS += -I$(GLUT_H_DIR)
            LDFLAGS += -lglut

endef

GLUT_H_DIR ?= /usr/include
ifeq "$(strip $(shell pkg-config --cflags glut))" ""
  $(warning $(MISSING_PKG_CONFIG))
  ifeq "$(strip $(shell ls '$(GLUT_H_DIR)/GL/glut.h'))" ""
  $(error $(GLUT_H_MISSING))
  else ifeq "$(strip $(shell locate '*/libglut.so'))" ""
    $(error $(LIBGLUT_MISSING))
  else
    $(warning $(FOUND))
    CPPFLAGS += -I$(GLUT_H_DIR)
    LDFLAGS += -lglut
  endif
else
  CPPFLAGS += $(shell pkg-config --cflags glut)
  LDFLAGS  += $(shell pkg-config --libs   glut)
endif
