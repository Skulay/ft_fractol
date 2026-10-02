NAME		= fractol

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O2 -g

HEADER		= ft_fractol.h
SRC_DIR		= src
LIBFT_DIR	= libft
MLX_DIR		= minilibx-linux

LIBFT_REPO	= https://github.com/Skulay/libft.git
MLX_REPO	= https://github.com/42Paris/minilibx-linux.git

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

$(OBJ): | $(LIBFT_DIR) $(MLX_DIR)

$(LIBFT_DIR):
	git clone --depth 1 $(LIBFT_REPO) $(LIBFT_DIR)

$(MLX_DIR):
	git clone --depth 1 $(MLX_REPO) $(MLX_DIR)

$(LIBFT): | $(LIBFT_DIR)
	make -C $(LIBFT_DIR)

$(MLX): | $(MLX_DIR)
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJ)
	if [ -d $(LIBFT_DIR) ]; then make -C $(LIBFT_DIR) clean; fi
	if [ -d $(MLX_DIR) ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	if [ -d $(LIBFT_DIR) ]; then make -C $(LIBFT_DIR) fclean; fi

distclean: fclean
	rm -rf $(LIBFT_DIR) $(MLX_DIR)

re: fclean
	make all

.PHONY: all clean fclean distclean re
