NAME	=	minishell

CC		=	cc
FLAGS	=	-Wall -Werror -Wextra
LIBS	=	-L ./$(LIBFT) -lft -lreadline
RM		=	rm -rf

LIBFT	=	libft
SRC_DIR	=	src
INC_DIR	=	include

SRC		=	minishell.c \
			$(SRC_DIR)/general.c \
			$(SRC_DIR)/io_control.c \
			$(SRC_DIR)/navigation.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/variable_env.c \

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			@norminette .
			@make -C $(LIBFT)
			@$(CC) $(CFLAGS) $(SRC) -o $@ $(LIBS)

clean:
			make clean -C $(LIBFT)
			@$(RM) $(OBJ)

fclean:		clean
			@make fclean -C $(LIBFT)
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re