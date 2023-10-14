NAME = fdf
CC = cc
LIBFT = libft/libft.a \

SRC = main.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

all: init $(NAME)

init: 
	@cd libft && $(MAKE)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
