CC = gcc
CCFLAGS = -std=c11 -Wall -Wextra -Werror
LDFLAGS = -lcheck -lc -lsubunit -lrt -lm -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage
LIBSFLAGS = -lcheck -lsubunit -lrt -lpthread -lm -lgcov
VALGRIND_FLAGS = --tool=memcheck --leak-check=yes
SRC = ./Additional_functions/*.c ./Arithmetic_operators/*.c ./Comparison_operators/*.c ./Converters/*.c ./Other_functions/*.c
TESTS_SRC = ./tests/*.c
CPPFLAGS = --enable=all --suppress=missingIncludeSystem --std=c11
RM = rm -rf

GCOVR = ~/.local/bin/gcovr

LIB_NAME = s21_decimal.a
TESTS_NAME = s21_decimal_test
TESTS_GCOV_NAME = s21_decimal_tests_gcov

HEADER_NAME = s21_decimal.h
SOURCES = $(filter-out tests/%,$(wildcard */*.c))

OBJECTS = $(SOURCES:.c=.o)
HEADER = $(HEADER_NAME)

TEST_DIR = tests/
TEST_HEADER_NAME := s21_decimal_test.h
TEST_SRC = $(wildcard $(addprefix $(TEST_DIR),*.c))
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_HEADER = $(addprefix $(TEST_DIR),$(TEST_HEADER_NAME))


all:$(LIB_NAME)

$(LIB_NAME):$(OBJECTS)
	ar rc $@ $^
	ranlib $@

%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@

$(SOURCES):$(HEADER)
$(TEST_SRC): $(TEST_HEADER)

test: $(TESTS_NAME)
	./$(TESTS_NAME)

$(TESTS_NAME):$(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CCFLAGS) $^ -L. -L/usr/local/lib -L/usr/include -l:s21_decimal.a -o $@ $(LDFLAGS)

gcov_report:clean_gcov clean_report $(TESTS_GCOV_NAME)
	./$(TESTS_GCOV_NAME)
	mkdir report
	$(GCOVR) -r . --html --html-details -o report/coverage.html --exclude=$(TEST_DIR) --exclude=Additional_functions/
	make clean_gcov
	firefox report/coverage.html

$(TESTS_GCOV_NAME):$(TEST_SRC) $(SOURCES)
	$(CC) $(CCFLAGS) -g -fprofile-arcs -ftest-coverage $^ -o $@ $(LDFLAGS)

clang-check:
	clang-format --style=Google -n *.h
	clang-format --style=Google -n */*.c
	clang-format --style=Google -n */*.h
	clang-format --style=Google -n $(TEST_DIR)*.c
	clang-format --style=Google -n $(TEST_DIR)*.h

clang-fix:
	clang-format --style=Google -i *.h
	clang-format --style=Google -i */*.c
	clang-format --style=Google -i */*.h
	clang-format --style=Google -i $(TEST_DIR)*.c
	clang-format --style=Google -i $(TEST_DIR)*.h

clean:clean_gcov clean_report
	$(RM) $(TESTS_NAME)
	$(RM) $(LIB_NAME)
	$(RM) $(OBJECTS)
	$(RM) $(TEST_OBJ)

clean_report:
	$(RM) report

clean_gcov:
	$(RM) $(TESTS_GCOV_NAME)
	$(RM) *.gcda
	$(RM) *.gcno

valgrind: $(LIB_NAME)
	$(CC) $(CCFLAGS) -g $(GCOV_FLAGS) $(SRC) ${TESTS_SRC} -o s21_decimal_test $(LIBSFLAGS)
	valgrind $(VALGRIND_FLAGS) ./s21_decimal_test
	make clean


