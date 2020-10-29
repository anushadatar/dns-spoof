# Makefile for building and testing DNS spoofing daemeon
cc = gcc
flags := -Wall

# Uses wildcard to compile all files in each directory. 
# Referenced from https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
target := dnsspoof
target-debug := dnsspoof-debug
src := $(wildcard src/*.c)
test-target := dnsspoof-test
test-target-debug := dnsspoof-test-debug
test := $(wildcard test/*.c)
cunit := -lcunit

$(target): 
	$(cc) $(src) $(flags) -o $(target)

.PHONY: clean
clean:
	rm -rf $(target) obj/ 

.PHONY: test
test:
	$(cc) $(test) $(src) $(flags) $(cunit) -D UNIT_TEST -o $(test-target)

.PHONY: debug
debug:
	$(cc) $(src) $(flags) -D DEBUG -o $(target-debug)

.PHONY: test-debug
test-debug:
	$(cc) $(src) $(flags) -D TEST_DEBUG -o $(target-debug)
