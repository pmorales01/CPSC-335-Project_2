
CLANG_FLAGS = -std=c++17 -Wall -g

GTEST_FLAGS = -lpthread -lgtest_main -lgtest

# determine Python version, need at least 3.7
PYTHON=python3
ifneq (, $(shell which python3.7))
	PYTHON=python3.7
endif
ifneq (, $(shell which python3.8))
	PYTHON=python3.8
endif

build: poly_exp_test timing

test: poly_exp_test
	./poly_exp_test

grade: grade.py poly_exp_test
	${PYTHON} grade.py

poly_exp_test:  poly_exp.hpp poly_exp.cpp poly_exp_test.cpp
	clang++ ${CLANG_FLAGS} ${GTEST_FLAGS} poly_exp_test.cpp poly_exp.cpp -o poly_exp_test

timing: timer.hpp poly_exp.hpp poly_exp.cpp timing.cpp
	clang++ ${CLANG_FLAGS} timing.cpp poly_exp.cpp -o timing

clean:
	rm -f gtest.xml results.json poly_exp_test timing
