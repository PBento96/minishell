NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = $(wildcard *.c) $(wildcard ft_printf/*.c) $(wildcard get_next_line/*.c)

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