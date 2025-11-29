CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I ft_printf/includes/ -I get_next_line/ -I .
NAME = libft.a
HEADER = libft.h ft_printf/includes/ft_printf.h get_next_line/get_next_line.h

SRCS_CHARACTER = character/ft_isalnum.c \
		character/ft_isalpha.c \
		character/ft_isascii.c \
		character/ft_isdigit.c \
		character/ft_isprint.c \
		character/ft_isspace.c \
		character/ft_issign.c \
		character/ft_tolower.c \
		character/ft_toupper.c

SRCS_STRING = string/ft_atoi.c \
		string/ft_itoa.c \
		string/ft_split.c \
		string/ft_strchr.c \
		string/ft_strrchr.c \
		string/ft_strdup.c \
		string/ft_strndup.c \
		string/ft_striteri.c \
		string/ft_strjoin.c \
		string/ft_strlcat.c \
		string/ft_strlcpy.c \
		string/ft_strlen.c \
		string/ft_strmapi.c \
		string/ft_strncmp.c \
		string/ft_strnstr.c \
		string/ft_strtrim.c \
		string/ft_substr.c \
		string/ft_startwith.c \
		string/ft_endwith.c \
		string/ft_replace.c \
		string/ft_strnjoin.c

SRCS_MEMORY = memory/ft_bzero.c \
		memory/ft_calloc.c \
		memory/ft_memchr.c \
		memory/ft_memcmp.c \
		memory/ft_memcpy.c \
		memory/ft_memmove.c \
		memory/ft_memset.c

SRCS_PUT = put/ft_putchar_fd.c \
		put/ft_putendl_fd.c \
		put/ft_putnbr_fd.c \
		put/ft_putstr_fd.c

SRCS_LIST = list/ft_lstadd_back.c \
		list/ft_lstadd_front.c \
		list/ft_lstclear.c \
		list/ft_lstdelone.c \
		list/ft_lstiter.c \
		list/ft_lstlast.c \
		list/ft_lstmap.c \
		list/ft_lstnew.c \
		list/ft_lstsize.c

SRCS_DICT = dict/ft_dict_new.c \
		dict/ft_dict_set.c \
		dict/ft_dict_unset.c \
		dict/ft_dict_get.c \
		dict/ft_dict_get_node.c \
		dict/ft_dict_clear.c

SRCS_PRINTF = ft_printf/srcs/ft_printf.c \
		ft_printf/srcs/ft_putaddr.c \
		ft_printf/srcs/ft_putchar.c \
		ft_printf/srcs/ft_putnbr.c \
		ft_printf/srcs/ft_putnbrhexa.c \
		ft_printf/srcs/ft_putstr.c \
		ft_printf/srcs/ft_putunbr.c \
		ft_printf/srcs/ft_startwith.c \
		ft_printf/srcs/ft_strcmp.c \
		ft_printf/srcs/ft_strlen.c

SRCS_GET_NEXT_LINE = get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

SRCS = $(SRCS_CHARACTER) \
	$(SRCS_STRING) \
	$(SRCS_MEMORY) \
	$(SRCS_PUT) \
	$(SRCS_LIST) \
	$(SRCS_DICT) \
	$(SRCS_PRINTF) \
	$(SRCS_GET_NEXT_LINE)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
