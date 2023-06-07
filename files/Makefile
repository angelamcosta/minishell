NAME	=	minishell

RM		=	rm -rf
CC		=	cc
FLAGS	=	-Wall -Werror -Wextra -lreadline

SRC		=	minishell.c \
			minishell.h \
			./utils/general_utils.c \
			./utils/string_utils.c \
			./utils/term_utils.c

all:		$(NAME)

$(NAME):
			$(CC) $(SRC) $(FLAGS) -o $(NAME)

clean:
			$(RM) $(NAME)

fclean:		clean

re:
			@$(MAKE) fclean
			@$(MAKE)