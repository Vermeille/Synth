CXXFLAGS=-Wall -Wextra -march=native -O3 -Isrc -std=c++14

run_tests: tests/tests

test: tests/tests
	./tests/tests

clean:
	rm -rf tests/tests
