CC := g++
STD := -std=c++17
CFLAG := -Wall -Wextra -Wshadow

FSANITIZE_DEBUG := True
ifeq ($(shell uname), Linux)
	ifeq ($(FSANITIZE_DEBUG), True)
	CFLAG += -g -fsanitize=address
	endif
endif

GTEST_LIBS := -lgtest
INCLUDE_PATHS := . s21_vector tests
INCLUDE := $(addprefix -I,$(INCLUDE_PATHS))

TEST_FILES := $(addprefix ./tests/,\
	test.cc\
	vector.cc)

all: test

# main build
test: clean
	$(CC) $(STD) $(CFLAG) -o test $(TEST_FILES) $(INCLUDE) $(GTEST_LIBS)
	./test

.PHONY: linter clean

linter:
	@clear
	@find . -name "*.cc" -exec python3 cpplint.py {} \;
	@find . -name "*.h" -exec python3 cpplint.py {} \;

clean:
	@rm -f test
