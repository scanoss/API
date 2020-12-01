
CWD=$(shell pwd)
CC=gcc
# Enable all compiler warnings. 
CCFLAGS=-g -Wall -std=gnu99
# Linker flags
LDFLAGS=-lpthread -lssl -lm -lcrypto -I. 
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


# The API depends on these libraries.
LIB_WAYUU=wayuu/libwayuu.a

all: clean libwayuu $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -g -o $@ $^ $(LIB_WAYUU) $(LIB_BASE) $(LDFLAGS)
	rm -f src/*.o src/**/*.o 


.PHONY: libwayuu
libwayuu: 
	make lib -C wayuu

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

test/%.o: test/%.c 
	@mkdir -p $(dir $@)
	$(CC) -DSNOW_ENABLED -I. -Itest/. $(CCFLAGS) -c -o $@ $<

test-$(TARGET): $(OBJ_TEST) $(TESTABLE_OBJECTS)
	$(CC) -g -o $@ $(OBJ_TEST) $(TESTABLE_OBJECTS) $(LIB_WAYUU)  $(LIB_BASE) $(LDFLAGS)
	

.PHONY: test
test: clean libwayuu test-$(TARGET)
	valgrind $(VGFLAGS) ./test-$(TARGET) $(ARGS)

run-valgrind: $(TARGET)
	valgrind $(VGFLAGS) ./$(TARGET) -d $(ARGS)
	
clean:
	rm -f wayuu/*.o src/*.o src/**/*.o test/*.o test/**/*.o $(TARGET) test-$(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/bin

update-docs:
	openapi-spec-gen . > scanoss-api.yaml
  
	



  
