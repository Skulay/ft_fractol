NAME		= fractol

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O2 -g

HEADER		= ft_fractol.h
SRC_DIR		= src
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx_Linux.a

INCLUDES 	= -I . -I $(LIBFT_DIR) -I $(MLX_DIR)

MLX_LNK		= -L $(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

SRC = main.c \
		parsing.c \
		render.c \
		init.c \
		utils.c \
		hook.c \
		color.c \
		mandelbrot.c \
		julia.c \
		burningship.c \

SRC := $(addprefix $(SRC_DIR)/,$(SRC))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LNK) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean
	make all

.PHONY: all clean fclean re
