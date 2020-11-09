CC := clang
CFLAGS := -c -Wall -Wno-deprecated-declarations

.PHONY: all target run clean submodule

FILENAME := main
BUILDPATH := build
SUBMODULEPATH := MLKG

ifeq ($(OS), Windows_NT)
FILENAME := $(BUILDPATH)\$(FILENAME).exe
RUNFILE := $(FILENAME)
else
FILENAME := $(BUILDPATH)/$(FILENAME)
RUNFILE := ./$(FILENAME)
CLIBS := -lm
endif

SOURCES := $(wildcard *.c)
OBJECTS := $(SOURCES:.c=.o)

# Submodule translation units
SUBMODULE_SOURCES := $(wildcard $(SUBMODULEPATH)/*.c)
SUBMODULE_SOURCES := $(filter-out $(SUBMODULEPATH)/main.c, $(SUBMODULE_SOURCES))
SUBMODULE_OBJECTS := $(SUBMODULE_SOURCES:.c=.o) 

all:  $(BUILDPATH) submodule target

target: $(OBJECTS) $(SUBMODULE_OBJECTS)
	$(CC) $^ -o  $(FILENAME) $(CLIBS)

$(BUILDPATH):
	mkdir $(BUILDPATH)

run: $(RUNFILE)
	$(RUNFILE)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

submodule: $(SUBMODULEPATH)/Makefile
	cd $(SUBMODULEPATH) && make

ifeq ($(OS), Windows_NT)
clean:
	del /q /s *.o
	rmdir /q /s $(BUILDPATH)
	cd $(SUBMODULEPATH) && make clean

else
clean:
	rm -f *.o
	rm -rf $(BUILDPATH)
	cd $(SUBMODULEPATH) && make clean
endif