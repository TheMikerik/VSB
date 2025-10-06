LIBNAME = vernum_lib
LIBFILE = lib$(LIBNAME).so

CPPFLAGS += -g -I../inc

ifeq ($(shell uname -m),x86_64) 
 CPPFLAGS += -fPIC
endif

all: $(LIBFILE)

clean:
	rm -rf $(LIBFILE) *.o

$(LIBFILE): vernum_lib.o
	g++ $(CPPFLAGS) $^ -shared -o $@

vernum_lib.o: vernum_lib.cpp ../inc/vernum_lib.h
	g++ $(CPPFLAGS) -c vernum_lib.cpp -o vernum_lib.o