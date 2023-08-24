NAME	=	minishell

CC		=	cc
FLAGS	=	-Wall -Werror -Wextra
LIBS	=	-L ./$(LIBFT) -lft -lreadline
RM		=	rm -rf

LIBFT	=	libft
GNL		=	get_next_line
SRC_DIR	=	src
INC_DIR	=	include
B_INS	=	builtins
TOKENS	=	tokens

SRC		=	minishell.c \
			$(SRC_DIR)/$(B_INS)/io_control.c \
			$(SRC_DIR)/$(B_INS)/navigation.c \
			$(SRC_DIR)/$(B_INS)/variable_env.c \
			$(SRC_DIR)/$(TOKENS)/tokenization.c \
			$(SRC_DIR)/$(TOKENS)/tokens_utils.c \
			$(SRC_DIR)/general.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/signals.c \
			get_next_line/get_next_line.c \

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			# norminette .
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