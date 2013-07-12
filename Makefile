MAKEFILE_IN = Makefile.in
include $(MAKEFILE_IN)

CFLAGS ?= -Wall
CURL ?= curl
UNTAR ?= tar -xvf
CD ?= cd
RM ?= rm -f
OS ?= MacOSX10.6.8

LIBS = -lhdf5 -L$(HDF_HOME)/lib -framework OpenGL -framework GLUT
LOCLIBS = cow/libcow.a
INCS = -I/usr/X11R6/include -I./cow/

default: bin/cowvis

bin/cowvis: src/cowvis.c $(LOCLIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(INCS) $(LIBS)
	
cow/libcow.a: .FORCE
	$(MAKE) -C cow libcow.a MAKEFILE_IN=$(MAKEFILE_IN)
	
clean:
	$(MAKE) -C cow clean MAKEFILE_IN=$(MAKEFILE_IN)
	$(RM) bin/cowvis
	
.FORCE:

