NAME = libft.a
CC = clang
FLAGS = -Wall -Werror -Wextra

OBJS_DIR = objs/

LIBFT_SRCS = libft_srcs/ft_isalpha.c \
			libft_srcs/ft_isdigit.c \
			libft_srcs/ft_isalnum.c \
			libft_srcs/ft_isascii.c \
			libft_srcs/ft_isprint.c \
			libft_srcs/ft_strlen.c \
			libft_srcs/ft_memset.c \
			libft_srcs/ft_bzero.c \
			libft_srcs/ft_memcpy.c \
			libft_srcs/ft_memmove.c \
			libft_srcs/ft_strlcpy.c \
			libft_srcs/ft_strlcat.c \
			libft_srcs/ft_toupper.c \
			libft_srcs/ft_tolower.c \
			libft_srcs/ft_strchr.c \
			libft_srcs/ft_strrchr.c \
			libft_srcs/ft_strncmp.c \
			libft_srcs/ft_memchr.c \
			libft_srcs/ft_memcmp.c \
			libft_srcs/ft_strnstr.c \
			libft_srcs/ft_atoi.c \
			libft_srcs/ft_calloc.c \
			libft_srcs/ft_strdup.c \
			libft_srcs/ft_substr.c \
			libft_srcs/ft_strjoin.c \
			libft_srcs/ft_strtrim.c \
			libft_srcs/ft_split.c \
			libft_srcs/ft_itoa.c \
			libft_srcs/ft_strmapi.c \
			libft_srcs/ft_striteri.c \
			libft_srcs/ft_putchar_fd.c \
			libft_srcs/ft_putstr_fd.c \
			libft_srcs/ft_putendl_fd.c \
			libft_srcs/ft_putnbr_fd.c \
			libft_srcs/ft_realloc.c \
			libft_srcs/ft_memcpy_opti_af.c \
			libft_srcs/ft_realloc_array.c \
			libft_srcs/ft_free_array.c \
			libft_srcs/ft_free_array_of_array.c \
			libft_srcs/ft_get_array_length.c \

GNL_SRCS = gnl_srcs/get_next_line.c \

PRINTF_SRCS = ft_printf_srcs/ft_printf.c \
			ft_printf_srcs/base_utils.c \
			ft_printf_srcs/print_functions.c \
			ft_printf_srcs/print_functions2.c

LIBFT_OBJS = $(patsubst libft_srcs/%.c,$(OBJS_DIR)%.o,$(LIBFT_SRCS))
GNL_OBJS = $(patsubst gnl_srcs/%.c,$(OBJS_DIR)%.o,$(GNL_SRCS))
PRINTF_OBJS = $(patsubst ft_printf_srcs/%.c,$(OBJS_DIR)%.o,$(PRINTF_SRCS))

OBJS = $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

$(OBJS_DIR)%.o : libft_srcs/%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(OBJS_DIR)%.o : gnl_srcs/%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(OBJS_DIR)%.o : ft_printf_srcs/%.c | $(OBJS_DIR)
	$(CC) $(FLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)

all : $(NAME)

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re