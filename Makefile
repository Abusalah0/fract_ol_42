CC = cc
CFLAGS = -Wall -Werror -Wextra
MLX_FLAGS = -lmlx -lXext -lX11 -lm
MAKEFLAGS += --no-print-directory
SRC = main.c fractals.c key_events.c init_program.c error_handling.c color.c
OBJ_DIR = ./obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
NAME = mandelbrot

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

all: $(NAME) libft

$(NAME): $(OBJ) #$(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX_FLAGS) $(LIBFT_FLAGS)

libft:
	@$(MAKE) -C $(LIBFT_DIR)
#$(LIBFT):
#	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c fract_ol.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean: clean_libft
	rm -rf $(OBJ_DIR)

fclean: clean fclean_libft
	rm -rf $(NAME)

clean_libft:
	$(MAKE) -C $(LIBFT_DIR) clean

fclean_libft:
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all re clean fclean clean_libft fclean_libft libft
