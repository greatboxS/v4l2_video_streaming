CC=gcc
CPP=g++
APP_BINARY=uvccapture
VERSION = 0.4
PREFIX=/usr/local/bin

WARNINGS = -Wall


CFLAGS = -std=gnu99 -O2 -DLINUX -DVERSION=\"$(VERSION)\" $(WARNINGS)
CPPFLAGS = $(CFLAGS) 
# CPPFLAGS = $(CFLAGS) `pkg-config --cflags --libs opencv`

OBJECTS= uvccapture.o v4l2uvc.o v4l2debug.o 


all:    uvccapture

clean:
	@echo "Cleaning up directory."
	rm -f *.a *.o $(APP_BINARY) core *~ log errlog

install:
	install $(APP_BINARY) $(PREFIX)

# Applications:
uvccapture: $(OBJECTS)
	$(CC)   $(OBJECTS) $(XPM_LIB) $(MATH_LIB) -ljpeg -o $(APP_BINARY) 
