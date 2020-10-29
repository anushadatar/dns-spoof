# Makefile for building and testing DNS spoofing daemeon
cc = gcc
flags := -Wall

# Uses wildcard to compile all files in each directory. 
# Referenced from https://www.gnu.org/software/make/manual/html_node/Wildcard-Function.html
target := dnsspoof
src := $(wildcard src/*.c)
test-target := dnsspoof-check
test := $(wildcard test/*.c)
cunit := -lcunit

$(target): 
	$(cc) $(src) $(flags) -o $(target)

.PHONY: check
check:
	$(cc) $(test) $(src) $(flags) $(cunit) -D UNIT_TEST -o $(test-target)
	./dnsspoof-check

.PHONY: clean
clean:
	rm -rf $(target) $(test-target) obj/ 

