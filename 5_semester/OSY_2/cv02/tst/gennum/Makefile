TARGET = gennum
LIBNAME = gennum_lib
LIBFILE = lib$(LIBNAME).a

CPPFLAGS += -g
LDFLAGS += -L. 
LDLIBS += -l$(LIBNAME)

all: $(TARGET)

# clean binary files
clean:
	rm -rf $(TARGET) $(LIBFILE) *.o

# creating static library 
$(LIBFILE): gennum_whole.o gennum_decimal.o gennum_bin.o
	@echo "\nCreating static library...\n"
	#rm -f $@
	ar r $@ $^
	@echo "\nStatic library created: '$(LIBFILE)'.\n"

# creating application
$(TARGET): $(TARGET).cpp $(LIBFILE)
	@echo "\nCreating application...\n"
	g++ $(CPPFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@
	@echo "\nApplication '$(TARGET)' is ready.\n"

# compile object files
gennum_whole.o: gennum_whole.cpp gennum_lib.h
	g++ $(CPPFLAGS) -c gennum_whole.cpp -o gennum_whole.o

gennum_decimal.o: gennum_decimal.cpp gennum_lib.h
	g++ $(CPPFLAGS) -c gennum_decimal.cpp -o gennum_decimal.o

gennum_binary.o: gennum_binary.cpp gennum_lib.h
	g++ $(CPPFLAGS) -c gennum_binary.cpp -o gennum_binary.o