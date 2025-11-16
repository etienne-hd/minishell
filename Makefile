CC=cc
NAME = minishell
SRC_DIR = src/
SRCS = $(SRC_DIR)minishell.c

OBJ_DIR = objs/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a

CFLAGS = -g \
		-I include \
		-I libft \
		-I libft/ft_printf/includes \
		-I libft/get_next_line/

LDFLAGS = -Wall -Werror -Wextra -g $(LIBFT)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p objs/
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