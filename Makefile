CC=gcc -Wall -Wextra -Werror -std=c11
FUNC_FILES_C=s21_matrix.c
FUNC_FILES_O=s21_matrix.o
GCOVFLAGS=-fprofile-arcs -ftest-coverage
LIBNAME=s21_matrix.a
GLFLAGS=--coverage

all: s21_matrix.a

build_object_files:
	$(CC) $(GCOVFLAGS) $(GLFLAGS) -c $(FUNC_FILES_C)

build_library:
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

s21_matrix.a:
	$(CC) -c $(FUNC_FILES_C)
	make build_library
	rm -rf *.o

test: s21_matrix.a
	$(CC) $(GLFLAGS) $(GCOVFLAGS) tests.c -L. s21_matrix.a -o run_test -I/usr/include -L/usr/lib/x86_64-linux-gnu -lcheck -lsubunit -lm
	./run_test

gcov_report: clean build_object_files build_library test
	lcov -o tests.info -c -d .  
	genhtml -o report tests.info
	xdg-open report/index.html

clean:
	rm -rf *.o *.gcno *.gcov *.gcda *.a *.info *_test *.gch

rebuild:
	make clean
	make