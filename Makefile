CC=cc
NAME = minishell
SRC_DIR = src/

SRC_ENV = $(SRC_DIR)env/load_env.c \
	$(SRC_DIR)env/destroy_env.c

SRC_UTILS = $(SRC_DIR)utils/path.c \
	$(SRC_DIR)utils/get_input.c \
	$(SRC_DIR)utils/safe_exit.c \
	$(SRC_DIR)utils/is_blank.c \
	$(SRC_DIR)utils/is_in_scope.c \
	$(SRC_DIR)utils/bounded_join.c \
	$(SRC_DIR)utils/signal.c \
	$(SRC_DIR)utils/free_2d.c

SRC_PARSING = $(SRC_DIR)parsing/parser.c \
	$(SRC_DIR)parsing/checker/check_scope.c \
	$(SRC_DIR)parsing/checker/check_syntax.c \
	$(SRC_DIR)parsing/pre_tokenizer/clear_pre_token.c \
	$(SRC_DIR)parsing/pre_tokenizer/pre_token_chain.c \
	$(SRC_DIR)parsing/pre_tokenizer/pre_token_chain_utils.c \
	$(SRC_DIR)parsing/tokenizer/clear_token.c \
	$(SRC_DIR)parsing/tokenizer/token_chain.c \
	$(SRC_DIR)parsing/tokenizer/token_chain_utils.c \
	$(SRC_DIR)parsing/expander/n_expand.c \
	$(SRC_DIR)parsing/expander/expander_utils.c \
	$(SRC_DIR)parsing/expander/expander.c \
	$(SRC_DIR)parsing/expander/handle_tilde.c \
	$(SRC_DIR)parsing/expander/expand_tokens.c \
	$(SRC_DIR)parsing/joiner/join_args_cmd.c \
	$(SRC_DIR)parsing/pre_exec/init_exec_utils.c \
	$(SRC_DIR)parsing/pre_exec/init_exec.c \
	$(SRC_DIR)parsing/pre_exec/process_clear.c \
	$(SRC_DIR)parsing/pre_exec/process_finder.c \
	$(SRC_DIR)parsing/pre_exec/process_generator.c 

SRC_EXEC = $(SRC_DIR)exec/execute.c \
	$(SRC_DIR)exec/free_exec.c \
	$(SRC_DIR)exec/file/open_file.c \
	$(SRC_DIR)exec/file/here_doc.c \
	$(SRC_DIR)exec/file/close_file.c

SRCS = $(SRC_DIR)minishell.c \
	$(SRC_DIR)ctx.c \
	$(SRC_UTILS) \
	$(SRC_ENV) \
	$(SRC_INPUT) \
	$(SRC_PARSING) \
	$(SRC_EXEC)

OBJ_DIR = .build/
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a

FSANITIZE = -fsanitize=address,undefined,leak -fno-omit-frame-pointer \
            -fsanitize-recover=address

CFLAGS = -Wall -Werror -Wextra -g \
		-I include \
		-I libft \
		-I libft/ft_printf/includes \
		-I libft/get_next_line/

LDFLAGS = $(LIBFT) -lreadline

ifdef SANITIZE
	CFLAGS += $(FSANITIZE)
	LDFLAGS += $(FSANITIZE)
endif

all: $(NAME)

sanitize:
	@echo ""
	@echo "================================"
	@echo "Recompiling with fsanitize flags..."
	@echo "================================"
	@echo ""
	$(MAKE) re SANITIZE=1
	@$(MAKE) run_sanitize
run_sanitize:
	@echo ""
	@echo "================================"
	@echo "Running with AddressSanitizer..."
	@echo "================================"
	@echo ""
	@ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 LSAN_OPTIONS=report_objects=1 ./$(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo ""
	@echo "================================"
	@echo "Creating minishell..."
	@echo "================================"
	@echo ""
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)env
	@mkdir -p $(OBJ_DIR)utils
	@mkdir -p $(OBJ_DIR)parsing
	@mkdir -p $(OBJ_DIR)parsing/pre_tokenizer
	@mkdir -p $(OBJ_DIR)parsing/tokenizer
	@mkdir -p $(OBJ_DIR)parsing/checker
	@mkdir -p $(OBJ_DIR)parsing/expander
	@mkdir -p $(OBJ_DIR)parsing/joiner
	@mkdir -p $(OBJ_DIR)parsing/pre_exec
	@mkdir -p $(OBJ_DIR)exec
	@mkdir -p $(OBJ_DIR)exec/file

	$(CC) $(CFLAGS) $< -c -o $@

$(LIBFT):
	@echo ""
	@echo "================================"
	@echo "Compiling libft objects..."
	@echo "================================"
	@echo ""
	$(MAKE) -C libft

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C libft fclean

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

re: fclean all

.PHONY: all fclean clean re
