NAME	=	minishell

CC		=	cc
FLAGS	=	-Wall -Werror -Wextra -L ./$(LIBFT) -lft
LIBS	=	-lreadline
RM		=	rm -rf

LIBFT	=	libft
SRC_DIR	=	src
INC_DIR	=	include

SRCS	=	minishell.c \
			$(SRC_DIR)/general.c \
			$(SRC_DIR)/io_control.c \
			$(SRC_DIR)/navigation.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/variable_env.c \

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(SRCS)
			make -C $(LIBFT)
			$(CC) $(SRCS) $(FLAGS) -I $(INC_DIR) $(LIBS) -o $@

clean:
			make clean -C $(LIBFT)
			$(RM) $(NAME)

fclean:		clean
			make fclean -C $(LIBFT)

re:			fclean all