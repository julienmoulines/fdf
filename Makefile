NAME = fdf
CC = cc
LIBFT = libft/libft.a
MLX_PATH = mlx_linux

SRC = main.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -Imlx -I$(MLX_PATH)
LDFLAGS = -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

all: init $(NAME)

init:
	@cd libft && $(MAKE)
	@cd $(MLX_PATH) && ./configure

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make clean -C ./libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re

