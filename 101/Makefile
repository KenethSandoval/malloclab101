# --------- FLAGS AND VARIABLES --------------------

CFLAGS=-O2 -nostdlib -nodefaultlibs -fno-builtin -fPIC -Wall 
HEADERPATH=-I./
CC = gcc



# ---------  GENERIC MAKE RULES --------------------

all: 
	@echo "Output should be: liballoc.a "
	@echo "                  liballoc.so"
	@echo 
	@echo "Usage: make [ compile | clean | <platform> ] "
	@echo 
	@echo "Currently supported platforms:"
	@echo 
	@echo "      linux"
	@echo
	@echo


clean:
	rm -f ./*.o
	rm -f ./*.a
	rm -f ./*.so

compile:
	$(CC) $(HEADERPATH) $(CFLAGS) -static -c  memalloc.c
	ar -rcv memalloc.a  *.o
	$(CC) $(HEADERPATH) $(CFLAGS) -shared memalloc.c -o memalloc.so

linux_debug:
	$(CC) -DDEBUG $(HEADERPATH) $(CFLAGS) -static -c memalloc.c linux.c
	ar -rcv memalloc.a  *.o
	$(CC) -DDEBUG $(HEADERPATH) $(CFLAGS) -shared memalloc.c linux.c -o memalloc.so
