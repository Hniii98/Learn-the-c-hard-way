CFLAGS=-g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local


SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))


TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))


TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))


# The Target Build
all: $(TARGET) $(SO_TARGET) tests


dev: CFLAGS=-g -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all


$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@


$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)


build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

# tests: $(TESTS)
#	$(CC) $(CFLAGS) $(LIBS) -o tests/list_tests $(TESTS) $(TARGET)
#	sh ./tests/runtests.sh

#tests/list_tests: tests/list_tests.c build/liblcthw.a
#	$(CC) $(CFLAGS) $(LIBS) -o tests/list_tests tests/list_tests.c build/liblcthw.a

tests/%: tests/%.c $(TARGET)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $< $(TARGET)


valgrind:
	VALGRIND="valgrind --log-file=/tmp/valgrind-%p.log" $(MAKE)


# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f test/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf 'find . -name "*.dsYM" -print'


# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true
