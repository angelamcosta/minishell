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
PARSER	=	parser
SUBS	=	shell_subsystems
XCTOR	=	executor

SRC		=	minishell.c \
			$(SRC_DIR)/$(B_INS)/io_control.c \
			$(SRC_DIR)/$(B_INS)/navigation.c \
			$(SRC_DIR)/$(XCTOR)/executor.c \
			$(SRC_DIR)/$(PARSER)/lexer_utils.c \
			$(SRC_DIR)/$(PARSER)/lexer.c \
			$(SRC_DIR)/$(PARSER)/parser_utils.c \
			$(SRC_DIR)/$(PARSER)/parser.c \
			$(SRC_DIR)/$(SUBS)/variable_env.c \
			$(SRC_DIR)/free_memory.c \
			$(SRC_DIR)/general.c \
			$(SRC_DIR)/signals.c \
			get_next_line/get_next_line.c \

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
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