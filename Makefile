NAME = minishell
CC = cc

FLAGS = -Wall -Werror -Wextra -g
# FLAGS = -g

READ_LINE_FLAG = -lreadline
LIBFT_FLAG = -Llibft -l:libft.a

SRCS_DIR = srcs/
PARSING = parsing/
SYNTAX = syntax/
AST = ast/
EXECUTABLE = executable/
ENV = env/
OBJS_DIR = objs/

GREEN=\033[0;32m
NC=\033[0m

# valgrind --suppressions=valgrind_suppressions_flags ./minishell
# valgrind --suppressions=valgrind_suppressions_flags --leak-check=full --show-leak-kinds=all ./minishell
# cl && make && valgrind --suppressions=valgrind_suppressions_flags --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

HEADER = headers/minishell.h

SRCS = $(SRCS_DIR)main.c \
		$(SRCS_DIR)prompt_utils_1.c \
		$(SRCS_DIR)signals_utils_1.c \
		$(SRCS_DIR)write_err.c \
		\
		$(SRCS_DIR)$(ENV)env_utils_1.c \
		$(SRCS_DIR)$(ENV)env_utils_2.c \
		$(SRCS_DIR)$(ENV)env_utils_3.c \
		\
		$(SRCS_DIR)$(SYNTAX)syntax.c \
		$(SRCS_DIR)$(SYNTAX)syntax_utils_1.c \
		$(SRCS_DIR)$(SYNTAX)syntax_parenthesis.c \
		$(SRCS_DIR)$(SYNTAX)char_utils_1.c \
		$(SRCS_DIR)$(SYNTAX)white_space_utils_1.c \
		\
		$(SRCS_DIR)$(AST)ast_node_utils_1.c \
		$(SRCS_DIR)$(AST)node_construct.c \
		$(SRCS_DIR)$(AST)ast_construct.c \
		$(SRCS_DIR)$(AST)ast_priorities.c \
		\
		$(SRCS_DIR)$(PARSING)the_axe.c \
		$(SRCS_DIR)$(PARSING)remove_useless_parenthesis.c \
		$(SRCS_DIR)$(PARSING)split_minishell.c \
		$(SRCS_DIR)$(PARSING)cmd_path.c \
		$(SRCS_DIR)$(PARSING)interpret_arguments.c \
		$(SRCS_DIR)$(PARSING)interpret_arguments_utils.c \
		$(SRCS_DIR)$(PARSING)cmd_args.c \

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(HEADER)
	make -C libft/
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG) $(READ_LINE_FLAG)
	@echo "$(GREEN)C'est compilée chef!$(NC)"

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)$(PARSING)
	mkdir -p $(OBJS_DIR)$(SYNTAX)
	mkdir -p $(OBJS_DIR)$(AST)
	mkdir -p $(OBJS_DIR)$(EXECUTABLE)
	mkdir -p $(OBJS_DIR)$(ENV)

all : $(NAME)

clean :
	make -C libft/ clean
	rm -rf $(OBJS_DIR)

fclean : clean
	make -C libft/ fclean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)

re : fclean all

.PHONY: all clean fclean re