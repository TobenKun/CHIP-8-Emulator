SHELL = /bin/bash
idx = 0
sp = /-\|/
CC = c++
CFLAGS = -I/Users/sangshin/.brew/opt/sdl2/include/SDL2 -L/Users/sangshin/.brew/opt/sdl2/lib -lSDL2 -lSDL2main -std=c++11
NAME = chip8

SOURCES = main.cpp Chip8.cpp Platform.cpp operation.cpp
		

OBJECTS = $(SOURCES:.cpp=.o)

all : .make_mandatory

$(NAME) : .make_mandatory

.make_mandatory : $(OBJECTS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)
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
