all: compile build

compile: malloc.asm
	nasm -f elf malloc.asm

build: compile
	ld -m elf_i386 -s -o malloc malloc.o

clean:
	rm -rf *.o malloc
