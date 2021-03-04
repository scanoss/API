
CWD=$(shell pwd)
CC=gcc
# Enable all compiler warnings. 
CCFLAGS=-g -Wall -std=gnu99
# Linker flags
LDFLAGS=-lpthread -lssl -lwayuu -lm -lcrypto -I. 
# Valgrind flags
VGFLAGS ?= \
	--quiet --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --error-exitcode=1 --keep-debuginfo=yes 

SOURCES=$(wildcard src/*.c) $(wildcard src/**/*.c)  
# TESTABLE_SOURCES are $SOURCES without main.c
TESTABLE_SOURCES=$(filter-out src/main.c, $(SOURCES))
TEST_SOURCES=$(wildcard test/*.c) $(wildcard test/**/*.c)
OBJ_TEST=$(patsubst %.c,%.o,$(TEST_SOURCES))
OBJECTS=$(SOURCES:.c=.o)
TESTABLE_OBJECTS=$(filter-out src/main.o,$(SOURCES:.c=.o))
TARGET=scanoss-api




all: clean $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -g -o $@ $^ $(LIB_BASE) $(LDFLAGS)
	rm -f src/*.o src/**/*.o 


%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

test/%.o: test/%.c 
	@mkdir -p $(dir $@)
	$(CC) -DSNOW_ENABLED -I. -Itest/. $(CCFLAGS) -c -o $@ $<

test-$(TARGET): $(OBJ_TEST) $(TESTABLE_OBJECTS)
	$(CC) -g -o $@ $(OBJ_TEST) $(TESTABLE_OBJECTS) $(LIB_BASE) $(LDFLAGS)
	

.PHONY: test
test: $(TARGET)
	valgrind $(VGFLAGS) ./test-$(TARGET) $(ARGS)

run-valgrind: $(TARGET)
	valgrind $(VGFLAGS) ./$(TARGET) -d $(ARGS)
	
clean:
	rm -f  src/*.o src/**/*.o test/*.o test/**/*.o $(TARGET) test-$(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/bin
	
install-wayuu:
	#installing Wayuu shared library
	wget https://github.com/scanoss/wayuu/releases/download/v1.4.2/wayuu-1.4.2-amd64.deb
	mv wayuu-1.4.2-amd64.deb /tmp
	sudo dpkg -i /tmp/wayuu-1.4.2-amd64.deb
	
update-docs:
	openapi-spec-gen . > scanoss-api.yaml
  	
	



  
