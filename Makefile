##
## EPITECH PROJECT, 2023
## mysh
## File description:
## Makefile mysh
##

NAME	=	42sh

SRCS	=	$(shell find src -name '*.c')

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-W -Werror -Wall -Wextra

CPPFLAGS	=	-I ./

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -I ./

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(OBJS) $(NAME)

re:	fclean all

debug: fclean
	@$(CC) $(SRCS) -g3 -o $(NAME) -I ./ $(CFLAGS)
