TARGET = vernum
LIBNAME = vernum_lib
LIBFILE = lib$(LIBNAME).so

CPPFLAGS  += -g 
LDFLAGS += -L. 
LDLIBS += -l$(LIBNAME)

ifeq ($(shell uname -m),x86_64) 
 CPPFLAGS += -fPIC
endif

all: $(TARGET)

clean:
	rm -rf $(TARGET) $(LIBFILE) *.o

$(LIBFILE): vernum_lib.o
	gcc $(CFLAGS) $^ -shared -o $@

$(TARGET): ../vernum.cpp $(LIBFILE)
	gcc $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@