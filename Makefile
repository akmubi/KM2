CC := clang
CFLAGS := -c -Wall -Wno-deprecated-declarations

.PHONY: all target run clean

FILENAME := main
BUILDPATH := build

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

all:  $(BUILDPATH) target

target: $(OBJECTS)
	$(CC) $^ -o  $(FILENAME) $(CLIBS)

$(BUILDPATH):
	mkdir $(BUILDPATH)

run: $(RUNFILE)
	$(RUNFILE)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

ifeq ($(OS), Windows_NT)
clean:
	del /q /s *.o
	rmdir /q /s $(BUILDPATH)

else
clean:
	rm -f *.o
	rm -rf $(BUILDPATH)
endif