NAME	=	libft.a

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
RM		=	rm -f

SRC		=	ft_atoi.c ft_isprint.c ft_memset.c\
ft_strlcpy.c ft_strrchr.c ft_bzero.c ft_calloc.c\
ft_itoa.c ft_strlen.c ft_strtrim.c ft_isalnum.c\
ft_memchr.c ft_strchr.c ft_substr.c ft_isalpha.c\
ft_memcmp.c ft_strdup.c ft_striteri.c ft_tolower.c\
ft_isascii.c ft_memcpy.c ft_strjoin.c ft_strncmp.c\
ft_toupper.c ft_isdigit.c ft_memmove.c ft_strlcat.c\
ft_strnstr.c ft_split.c ft_strmapi.c ft_putchar_fd.c\
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS	=	ft_lstadd_front.c ft_lstsize.c\
ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstnew.c

OBJ		=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			@ar	-r $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)
