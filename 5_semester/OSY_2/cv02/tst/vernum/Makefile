TARGET = vernum
LIBNAME = vernum_lib
LIBFILE = lib$(LIBNAME).so

CPPFLAGS += -g -I../inc
LDFLAGS += -L../lib_d -L../lib_o -L../lib_w
LDLIBS += -l$(LIBNAME)

all: $(TARGET)

# clean binary files
clean:
	rm -rf $(TARGET) *.o

# creating application
$(TARGET): $(TARGET).cpp
	@echo "\nCreating application...\n"
	g++ $(CPPFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@
	@echo "\nApplication '$(TARGET)' is ready.\n"