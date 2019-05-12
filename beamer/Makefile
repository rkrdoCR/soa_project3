#This is a test for beamer builder
# all: create_build beamer
all: create_build main

create_build:
	mkdir -p build
	mkdir -p build/tmpfiles
	cp -R assets build
	cd build
	
main:
	gcc -o build/testBeamerBuilder testBeamerBuilder.c beamerBuilder.c -I.