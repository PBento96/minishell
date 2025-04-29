NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_abs.c ft_atoi.c ft_atol.c ft_bzero.c ft_calloc.c ft_dlstadd_back.c \
	  ft_dlstadd_front.c ft_dlstadd_mid.c ft_dlstclear.c ft_dlstdelone.c \
	  ft_dlstfirst.c ft_dlstiter.c ft_dlstlast.c ft_dlstmap.c ft_dlstnew.c \
	  ft_dlstsize.c ft_free.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_islower.c ft_isprint.c ft_isspace.c ft_isupper.c \
	  ft_itoa.c ft_labs.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	  ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
	  ft_lstsize.c ft_memset.c ft_islower.c ft_strncmp.c ft_toupper.c \
	  ft_isspace.c ft_striteri.c ft_dlstsize.c ft_strrchr.c ft_strmapi.c \
	  ft_itoa.c ft_lstsize.c ft_isdigit.c ft_labs.c ft_split.c ft_lstadd_back.c \
	  ft_isascii.c ft_dlstadd_front.c ft_dlstclear.c ft_putstr_fd.c ft_lstmap.c \
	  ft_lstnew.c ft_atol.c ft_free_array.c ft_strtrim.c ft_tolower.c ft_strlen.c \
	  ft_abs.c ft_substr.c ft_isupper.c ft_isalnum.c ft_dlstadd_mid.c ft_strchr.c \
	  ft_strdup.c ft_memcpy.c ft_calloc.c ft_dlstfirst.c ft_memchr.c ft_lstdelone.c \
	  ft_strnstr.c ft_isprint.c ft_lstiter.c ft_ansi.h ft_lstlast.c ft_dlstadd_back.c \
	  ft_memcmp.c ft_dlstiter.c ft_putendl_fd.c ft_dlstdelone.c ft_isalpha.c ft_memmove.c \
	  ft_dlstlast.c ft_putnbr_fd.c ft_strjoin.c ft_lstadd_front.c ft_putchar_fd.c \
	  ft_strlcpy.c ft_memcmp.c ft_dlstiter.c ft_putendl_fd.c ft_dlstdelone.c ft_isalpha.c \
	  ft_memmove.c ft_dlstlast.c ft_putnbr_fd.c ft_strjoin.c ft_lstadd_front.c ft_strlcat.c\
	  ft_printf/ft_render1.c ft_printf/ft_parser.c ft_printf/ft_utils2.c \
	  ft_printf/ft_render3.c ft_printf/ft_printf.c ft_printf/ft_utils1.c \
	  ft_printf/ft_render2.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ = ${SRC:.c=.o}

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f *.o ft_printf/*.o get_next_line/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
