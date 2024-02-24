CC = -g -Wall -Wextra -Werror -std=c11
MYFLAGS = -lcheck -lpthread -lm  -I /usr/local/include -L/usr/local/lib
RUN = build/Calculator.app/Contents/MacOS/Calculator

all: install
	$(RUN)

dvi:
	open ../README.md

test: 
	gcc *.c $^ -o $@ $(CFLAGS) $(MYFLAGS) --coverage
	./test

install: uninstall
	mkdir build
	cd build && cmake build ../Calculator
	make -C ./build/

uninstall:
	rm -Rf build/
	rm -rf SmartCalc_v1.0.tar

gcov_report: test
	./test
	gcovr --html-details report.html
	open report.html

dist:
	tar -cf SmartCalc_v1.0.tar Calculator

check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n *.h
	clang-format -n Calculator/*.c
	clang-format -n Calculator/*.h
	clang-format -n Calculator/*.cpp 

clean:
	rm -rf a.out a.out.dSYM *.gcda *.gcno test report.* *.tar build .clang-format