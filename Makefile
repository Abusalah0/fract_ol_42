CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iinclude
NAME = fractol

LIBFT_DIR = libft
LDFLAGS = -L$(LIBFT_DIR) -lft -lmlx -lX11 -lXext -lm
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
OBJS_DIR = objs

SRC =  	color.c \
		error_handling.c \
		fractals.c \
		init_program.c \
		key_events.c \
		main.c \

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re