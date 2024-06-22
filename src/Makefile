CC=g++
FLAGS_TEST_LIBS =-lcheck -lm -lpthread
CXXFLAGS=-Wall -Wextra -Werror -Wno-unused -pedantic -std=c++17
GTESTFLAGS=-lgtest_main -lgtest
CLANG_FLAGS=--assume-filename=./.clang-format -i
#
#
#
SRC=singleton/singleton.cc
SRC_GTEST=tests/gtests.cc
#
HEADER=singleton/singleton.h
NAME=singleton/libsingleton.a
#
OBJ=$(patsubst %.cc, %.o, $(SRC))
#
OS = $(shell uname)
#
.PHONY: all build lib tests gcov_report dist dvi install uninstall rebuild clean m
#
all: build
#
build: $(NAME)
	$(CC) $(CXXFLAGS) -L./singleton/ $(SRC_GTEST) -lgtest -lsingleton -o ./tests/gtest
#
$(NAME) : $(OBJ) $(HEADER)
	ar rcs $(NAME) $?
%.o : %.cc $(HEADER)
	$(CC) $(CXXFLAGS) -c $< -o $@
#
tests: build
	./tests/gtest
#
gcov_report: clean build
	$(CC) $(CXXFLAGS) $(SRC_GTEST) -c -o tests/gtests.o
	$(CC) $(CXXFLAGS) --coverage $(SRC) tests/gtests.o $(FLAGS_TEST_LIBS) -lgtest -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open ./report/index.html
#
check: build
	cp ../materials/linters/.clang-format .
	clang-format $(CLANG_FLAGS) singleton/*.h
	clang-format $(CLANG_FLAGS) singleton/*.cc
	clang-format $(CLANG_FLAGS) controller/*.h
	clang-format $(CLANG_FLAGS) controller/*.cc
	clang-format $(CLANG_FLAGS) view/*.h
	clang-format $(CLANG_FLAGS) view/*.cc
	# rm -rf .clang-format

ifeq ($(OS), Darwin)
	leaks -atExit -- tests/gtest
else
	CK_FORK=no valgrind --vgdb=no \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--verbose \
	--log-file=RESULT_VALGRIND.txt \
	./tests/gtest
endif
#
install: uninstall
	mkdir build
	cd view && qmake && make && make clean && rm Makefile && cd ../ && cp -R view/view.app build
#
uninstall:
	rm -rf build
#
dist: install
	rm -rf Archive_Viewer/
	mkdir Archive_Viewer/
	mkdir Archive_Viewer/build
	cp -r ./build/view.app Archive_Viewer/build/

	cp -R ./OBJ Archive_Viewer/build/
	tar cvzf Archive_Viewer.tgz Archive_Viewer/
	rm -rf Archive_Viewer/
#
dvi:
	open README.md
#
clean:
	rm -rf RESULT_VALGRIND.txt *.gcda *.gcno
	rm -rf singleton/*.a singleton/*.o
	rm -rf tests/*.a tests/*.o tests/gtest
	rm -rf gcov* report
	rm -rf build* Archive*
#
rebuild: clean build
