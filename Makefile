SHELL = /bin/bash
idx = 0
sp = /-\|/
CC = c++
SDL2_PREFIX ?= $(shell brew --prefix sdl2)
CFLAGS = -I$(SDL2_PREFIX)/include/SDL2 -std=c++11
LDFLAGS = -L$(SDL2_PREFIX)/lib -lSDL2 -lSDL2main
NAME = chip8

SOURCES = main.cpp Chip8.cpp Platform.cpp operation.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all : .make_mandatory

$(NAME) : .make_mandatory

.make_mandatory : $(OBJECTS)
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME)
	@touch $@
	@printf "\b\b\b\b\b\b\b\b\b\b\b\b\bDone!               \n"

%.o : %.cpp
	$(eval idx = $(shell expr $(idx) + 1))
	$(eval t_idx = $(shell expr $(idx) % 4 + 1))
	$(eval chr = $(shell echo $(sp) | cut -c $(t_idx)))
	@if [ $(idx) = 1 ]; then\
		echo -n "Loading ... ";\
	fi
	@printf "\b$(chr)"
	@$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	@rm -f $(OBJECTS)
	@rm -f .make_mandatory
	@rm -f .make_bonus
	@printf "Done!\n"

fclean : clean
	@rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
