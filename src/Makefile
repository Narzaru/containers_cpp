CC := g++
STD := -std=c++17
CFLAG := -Wall -Wextra -Wshadow

FSANITIZE_DEBUG := True
ifeq ($(shell uname), Linux)
	ifeq ($(FSANITIZE_DEBUG), True)
	CFLAG += -fno-omit-frame-pointer -fsanitize=address
	endif
endif

GTEST_LIBS := -lgtest
INCLUDE_PATHS := . s21_vector tests
INCLUDE := $(addprefix -I,$(INCLUDE_PATHS))


all: test

# main build
test: clean
	$(CC) $(STD) $(CFLAG) -o test ./tests/test.cc $(INCLUDE) $(GTEST_LIBS)
	./test

.PHONY: linter clean

linter:
	@clear
	@cp ../materials/linters/CPPLINT.cfg .
	@find . -name "*.cpp" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

clean:
	@rm -f test
