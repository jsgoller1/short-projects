CC:=clang++
CFLAGS :=-std=c++11 -lm -Wno-c++98-compat
WARNINGS :=-Weverything -Werror -Wno-padded

COMMON_INCLUDE := -I./include/common -I/usr/local/include

TESTS_SRC := ./src/tests/*
COMMON_SRC := ./src/common/*
MAIN_SRC := ./src/main/*

BUILD_DIR := ./execs
REDEMPTION_BIN := redemption
TESTS_BIN := tests

# ANALYZER:=scan-build --status-bugs
# VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

all: reset clean setup redemption run convert display
debug: reset clean setup debug-redemption debug-run convert display
tests: reset clean setup tests-compile tests-run

### Binary cleanup and generation
setup:
	-mkdir $(BUILD_DIR)

clean:
	-rm -r $(BUILD_DIR)/*

reset:
	reset

convert:
	convert $(BUILD_DIR)/photo.ppm $(BUILD_DIR)/photo.png

display:
	display $(BUILD_DIR)/photo.png

### Main build
redemption:
	$(ANALYZER) $(CC) $(CFLAGS) -O3 -DNDEBUG $(WARNINGS) -O3 $(COMMON_INCLUDE) $(COMMON_SRC) $(MAIN_SRC) -o $(BUILD_DIR)/$(REDEMPTION_BIN)

run:
	$(BUILD_DIR)/$(REDEMPTION_BIN)

### Debugging
debug-redemption:
	$(ANALYZER) $(CC) $(CFLAGS) $(WARNINGS) -g -fstandalone-debug  $(COMMON_INCLUDE) $(COMMON_SRC) $(MAIN_SRC) -o $(BUILD_DIR)/$(REDEMPTION_BIN)

debug-run:
	time $(VALGRIND) $(BUILD_DIR)/$(REDEMPTION_BIN)

### Tests
compile-googletest:
	-rm -rf googletest/ gtest/
	git clone git@github.com:google/googletest.git
	mkdir googletest/mybuild; \
	cd googletest/mybuild; \
	cmake -Dgtest_build_samples=ON ..; \
	make

install-googletest:
	cp -r googletest/googletest/include/gtest /usr/local/include
	cp -r googletest/mybuild/lib/libgtest*.a /usr/local/lib/

clean-googletest:
	rm -rf googletest

tests-compile:
	$(CC) $(CFLAGS) $(WARNINGS) -Wno-global-constructors $(COMMON_INCLUDE) $(TESTS_INCLUDE) $(COMMON_SRC) $(TESTS_SRC) -o $(BUILD_DIR)/$(TESTS_BIN) -lgtest -lpthread

tests-run:
	$(BUILD_DIR)/$(TESTS_BIN)



