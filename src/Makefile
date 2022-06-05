CC := g++
STD := -std=c++17
CFLAG := -Wall -Wextra -Wshadow -pedantic
S = --suppress=unmatchedSuppression: *cc

FSANITIZE_DEBUG := True
ifeq ($(shell uname), Linux)
	ifeq ($(FSANITIZE_DEBUG), True)
	CFLAG += -g -fsanitize=address
	endif
endif

GTEST_LIBS := -lgtest -pthread
INCLUDE_PATHS := . s21_list s21_queue s21_vector tests
INCLUDE := $(addprefix -I,$(INCLUDE_PATHS))

TEST_FILES := $(addprefix ./tests/,\
	test.cc\
	array.cc\
	vector.cc\
	list.cc\
	queue.cc\
	stack.cc)

all: test

# main build
test: clean
	$(CC) $(STD) $(CFLAG) -o test $(TEST_FILES) $(INCLUDE) $(GTEST_LIBS)
	./test

.PHONY: linter clean

linter:
	@clear
	@cp ../materials/linters/CPPLINT.cfg .
	@find . -name "*.cc" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.cpp" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.inc" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../materials/linters/cpplint.py {} \;
	@find . -name "*.hpp" -exec python3 ../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

gcov_report: test
	@./test
	lcov -t "test" -o testcoverage.info -c -d .
	genhtml -o report test.info
	open report/index.html

cpplint:
	cppcheck --enable=all  --check-config $(S)constParameter $(S)useStlAlgorithm $(S)missingIncludeSystem $(S)noCopyConstructor $(S)noOperatorEq $(S)noExplicitConstructor $(S)negativeIndex $(S)missingReturn ../src/

clean:
	@rm -f test
