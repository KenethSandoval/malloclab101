NAME = bayou
CC = gcc
FLAGS = -std=c99 -pedantic -g
FLAGS += -Wall -Wno-unused-parameter -Wextra -Werror=vla -Werror
VALGRIND = --show-leak-kinds=all --track-origins=yes --leak-check=full

BIND = bin
OBJD = obj
SRCD = src
SUBD = sub

INCL = -I$(SRCD) -I$(SUBD)/termbox_next/src 
SRCS = $(SRCD)/main.c

SRCS_OBJS := $(patsubst %.c,$(OBJD)/%.o,$(SRCS))
SRCS_OBJS += $(SUBD)/termbox_next/bin/termbox.a

.PHONY: __all
__all: $(BIND)/$(NAME)

$(OBJD)/%.o: %.c
	@echo "building object $@"
	@mkdir -p $(@D)
	@$(CC) $(INCL) $(FLAGS) -c -o $@ $<

$(SUBD)/termbox_next/bin/termbox.a:
	@echo "building static object $@"
	@(cd $(SUBD)/termbox_next && $(MAKE))

$(BIND)/$(NAME): $(SRCS_OBJS)
	@echo "compiling executable $@"
	@mkdir -p $(@D)
	@$(CC) -o $@ $^ $(LINK)

run:
	@cd $(BIND) && ./$(NAME)

leakgrind: $(BIND)/$(NAME)
	@rm -f valgrind.log
	@cd $(BIND) && valgrind $(VALGRIND) 2> ../valgrind.log ./$(NAME)

clean:
	@echo "cleaning"
	@rm -rf $(BIND) $(OBJD) valgrind.log
