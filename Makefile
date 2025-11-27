CC=cc
NAME = minishell
SRC_DIR = src/

SRC_ENV = $(SRC_DIR)env/load_env.c \
	$(SRC_DIR)env/destroy_env.c

SRC_UTILS = $(SRC_DIR)utils/path.c \
	$(SRC_DIR)utils/get_input.c \
	$(SRC_DIR)utils/safe_exit.c

SRCS = $(SRC_DIR)minishell.c \
	$(SRC_DIR)ctx.c \
	$(SRC_UTILS) \
	$(SRC_ENV) \
	$(SRC_INPUT)

OBJ_DIR = .build/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g \
		-I include \
		-I libft \
		-I libft/ft_printf/includes \
		-I libft/get_next_line/

LDFLAGS = $(LIBFT) -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)env
	@mkdir -p $(OBJ_DIR)utils
	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	$(MAKE) -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C libft fclean

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

re: fclean all

.PHONY: all fclean clean run run2 re
