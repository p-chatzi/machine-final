#Variables
FLAGS := -Wall -Werror -O0

default: run

setup:
	mkdir -p out

clean:
	rm -rf out
	rm -rf build

build: setup
	gcc $(FLAGS) src/*.c -o out/chess

debug: 
	mkdir -p build/Debug
	gcc $(FLAGS) src/*.c -o build/Debug/outDebug

run: debug build 
	./out/chess