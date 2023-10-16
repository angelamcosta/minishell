NAME	=	minishell

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g
LIBS	=	-L ./$(LIBFT) -lft -lreadline
RM		=	rm -rf

LIBFT	=	libft
SRC_DIR	=	src
INC_DIR	=	include
B_INS	=	builtins
PARSER	=	parser
SUBS	=	shell_subsystems
XCTOR	=	executor
VAL		=	--leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind_log.txt \
			--suppressions=readline.supp \
			--track-fds=yes

SRC		=	minishell.c \
			$(SRC_DIR)/$(B_INS)/builtin_utils.c \
			$(SRC_DIR)/$(B_INS)/heredoc.c \
			$(SRC_DIR)/$(B_INS)/io_control.c \
			$(SRC_DIR)/$(B_INS)/navigation.c \
			$(SRC_DIR)/$(B_INS)/variable_env.c \
			$(SRC_DIR)/$(XCTOR)/builtin_executor.c \
			$(SRC_DIR)/$(XCTOR)/command_executor.c \
			$(SRC_DIR)/$(XCTOR)/command_parser.c \
			$(SRC_DIR)/$(XCTOR)/file_executor.c \
			$(SRC_DIR)/$(XCTOR)/process_management.c \
			$(SRC_DIR)/$(PARSER)/command_parsing.c \
			$(SRC_DIR)/$(PARSER)/parser.c \
			$(SRC_DIR)/$(PARSER)/string_handling.c \
			$(SRC_DIR)/$(PARSER)/syntax_parsing.c \
			$(SRC_DIR)/$(PARSER)/tokenization.c \
			$(SRC_DIR)/free_memory.c \
			$(SRC_DIR)/general.c \
			$(SRC_DIR)/signals.c \

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
			valgrind $(VAL) ./$(NAME)

.PHONY:		all clean fclean re