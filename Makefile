# Makefile for building and testing DNS spoofing daemeon
cc = gcc
flags := -Wall

# Uses wildcard to compile all files in each directory. 
# Referenced from https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
target := dnsspoof
src := $(wildcard src/*.c)
test-target := dnsspoof-test
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
