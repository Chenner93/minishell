NAME = minishell
CC = cc

FLAGS = -Wall -Werror -Wextra -g
READ_LINE_FLAG = -lreadline
LIBFT_FLAG = -Llibft -l:libft.a

SRCS_DIR = srcs/
PARSING = parsing/
EXECUTABLE = executable/
OBJS_DIR = objs/

GREEN=\033[0;32m
NC=\033[0m

# valgrind --suppressions=valgrind_suppressions_flags ./minishell
# valgrind --suppressions=valgrind_suppressions_flags --leak-check=full --show-leak-kinds=all ./minishell
# cl && make && valgrind --suppressions=valgrind_suppressions_flags --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

HEADER = headers/minishell.h

SRCS = $(SRCS_DIR)$(PARSING)parsing.c \
	$(SRCS_DIR)$(PARSING)parsing_utils_1.c \
	$(SRCS_DIR)$(PARSING)parsing_utils_2.c \
	$(SRCS_DIR)$(PARSING)parsing_utils_3.c \
	$(SRCS_DIR)$(PARSING)parsing_utils_4.c \
	$(SRCS_DIR)$(PARSING)parsing_utils_5.c \
	$(SRCS_DIR)$(PARSING)parsing_utils_6.c \
	$(SRCS_DIR)$(PARSING)split_minishell.c \
	$(SRCS_DIR)$(PARSING)syntax_utils_1.c \
	$(SRCS_DIR)$(PARSING)syntax_utils_2.c \
	\
	$(SRCS_DIR)$(EXECUTABLE)main_exec.c \
	$(SRCS_DIR)$(EXECUTABLE)init_cmd_pipe.c \
	$(SRCS_DIR)$(EXECUTABLE)pipex.c \
	$(SRCS_DIR)$(EXECUTABLE)builtin_check.c \
	$(SRCS_DIR)$(EXECUTABLE)echo_call.c \
	$(SRCS_DIR)$(EXECUTABLE)cd_call.c \
	$(SRCS_DIR)$(EXECUTABLE)env_call.c \
	$(SRCS_DIR)$(EXECUTABLE)export_call.c \
	$(SRCS_DIR)$(EXECUTABLE)unset_call.c \
	$(SRCS_DIR)$(EXECUTABLE)exit_call.c \
	$(SRCS_DIR)$(EXECUTABLE)unique_cmd.c \
	$(SRCS_DIR)$(EXECUTABLE)exit_child_perror.c \
	$(SRCS_DIR)$(EXECUTABLE)multiple_cmd.c \
	$(SRCS_DIR)$(EXECUTABLE)pwd_call.c \
	$(SRCS_DIR)$(EXECUTABLE)dup_std.c \
	\
	$(SRCS_DIR)main.c \
	$(SRCS_DIR)cmd_utils_1.c \
	$(SRCS_DIR)prompt_utils_1.c \
	$(SRCS_DIR)signals_utils_1.c \
	$(SRCS_DIR)utils_1.c \
	$(SRCS_DIR)env_utils_1.c \
	$(SRCS_DIR)env_utils_2.c \
	$(SRCS_DIR)env_utils_3.c \

OBJS = $(patsubst $(SRCS_DIR)%.c,$(OBJS_DIR)%.o,$(SRCS))

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(HEADER)
	make -C libft/
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBFT_FLAG) $(READ_LINE_FLAG)
	@echo "$(GREEN)C'est compilée chef!$(NC)"

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)$(PARSING)
	mkdir -p $(OBJS_DIR)$(EXECUTABLE)

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