NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes/ft_printf -g3
CFLAGS_BONUS = -Wall -Wextra -Werror -I_bonus/includes/gnl -I_bonus/includes/ft_printf -g3

SRCS = includes/ft_printf/ft_strlen.c \
		includes/ft_printf/ft_putendl_fd.c	\
		includes/ft_printf/ft_isdigit.c		\
		includes/ft_printf/ft_memmove.c		\
		includes/ft_printf/ft_strtrim.c		\
		includes/ft_printf/ft_strjoin.c		\
		includes/ft_printf/ft_striteri.c	\
		includes/ft_printf/ft_memset.c		\
		includes/ft_printf/ft_calloc.c		\
		includes/ft_printf/ft_split.c		\
		includes/ft_printf/ft_itoa.c		\
		includes/ft_printf/ft_hex.c			\
		includes/ft_printf/ft_memchr.c		\
		includes/ft_printf/ft_isalpha.c		\
		includes/ft_printf/ft_substr.c		\
		includes/ft_printf/ft_putnbr_u.c		\
		includes/ft_printf/ft_memcpy.c		\
		includes/ft_printf/ft_strnstr.c		\
		includes/ft_printf/ft_atoi.c		\
		includes/ft_printf/ft_toupper.c		\
		includes/ft_printf/ft_tolower.c		\
		includes/ft_printf/ft_strrchr.c		\
		includes/ft_printf/ft_bzero.c		\
		includes/ft_printf/ft_strlcat.c		\
		includes/ft_printf/ft_pointer.c		\
		includes/ft_printf/ft_isprint.c		\
		includes/ft_printf/ft_putnbr_fd.c		\
		includes/ft_printf/ft_putstr_fd.c		\
		includes/ft_printf/ft_strdup.c		\
		includes/ft_printf/ft_memcmp.c		\
		includes/ft_printf/ft_strmapi.c		\
		includes/ft_printf/ft_strchr.c		\
		includes/ft_printf/ft_putchar_fd.c		\
		includes/ft_printf/ft_unsigned.c		\
		includes/ft_printf/ft_isascii.c		\
		includes/ft_printf/ft_strncmp.c		\
		includes/ft_printf/ft_strlcpy.c		\
		includes/ft_printf/ft_printf.c		\
		includes/ft_printf/ft_isalnum.c		\
		src/main.c							\
		src/exec_routine.c					\
		src/free_utils.c					\

SRCS_BONUS = _bonus/includes/ft_printf/ft_strlen.c \
			_bonus/includes/ft_printf/ft_putendl_fd.c	\
			_bonus/includes/ft_printf/ft_isdigit.c		\
			_bonus/includes/ft_printf/ft_memmove.c		\
			_bonus/includes/ft_printf/ft_strtrim.c		\
			_bonus/includes/ft_printf/ft_strjoin.c		\
			_bonus/includes/ft_printf/ft_striteri.c	\
			_bonus/includes/ft_printf/ft_memset.c		\
			_bonus/includes/ft_printf/ft_calloc.c		\
			_bonus/includes/ft_printf/ft_split.c		\
			_bonus/includes/ft_printf/ft_itoa.c		\
			_bonus/includes/ft_printf/ft_hex.c			\
			_bonus/includes/ft_printf/ft_memchr.c		\
			_bonus/includes/ft_printf/ft_isalpha.c		\
			_bonus/includes/ft_printf/ft_substr.c		\
			_bonus/includes/ft_printf/ft_putnbr_u.c		\
			_bonus/includes/ft_printf/ft_memcpy.c		\
			_bonus/includes/ft_printf/ft_strnstr.c		\
			_bonus/includes/ft_printf/ft_atoi.c		\
			_bonus/includes/ft_printf/ft_toupper.c		\
			_bonus/includes/ft_printf/ft_tolower.c		\
			_bonus/includes/ft_printf/ft_strrchr.c		\
			_bonus/includes/ft_printf/ft_bzero.c		\
			_bonus/includes/ft_printf/ft_strlcat.c		\
			_bonus/includes/ft_printf/ft_pointer.c		\
			_bonus/includes/ft_printf/ft_isprint.c		\
			_bonus/includes/ft_printf/ft_putnbr_fd.c		\
			_bonus/includes/ft_printf/ft_putstr_fd.c		\
			_bonus/includes/ft_printf/ft_strdup.c		\
			_bonus/includes/ft_printf/ft_memcmp.c		\
			_bonus/includes/ft_printf/ft_strmapi.c		\
			_bonus/includes/ft_printf/ft_strchr.c		\
			_bonus/includes/ft_printf/ft_putchar_fd.c		\
			_bonus/includes/ft_printf/ft_unsigned.c		\
			_bonus/includes/ft_printf/ft_isascii.c		\
			_bonus/includes/ft_printf/ft_strncmp.c		\
			_bonus/includes/ft_printf/ft_strlcpy.c		\
			_bonus/includes/ft_printf/ft_printf.c		\
			_bonus/includes/ft_printf/ft_isalnum.c		\
			_bonus/includes/gnl/get_next_line.c				\
			_bonus/includes/gnl/get_next_line_utils.c				\
			_bonus/src/main_bonus.c							\
			_bonus/src/exec_routine_bonus.c					\
			_bonus/src/free_utils_bonus.c					\

ARGS ?=

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS) : $(OBJS_BONUS)
	$(CC) $(CFLAGS_BONUS) $(OBJS_BONUS) -o $(NAME_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

mem:
	valgrind --leak-check=full \
	--show-leak-kinds=all		\
	--track-fds=yes				\
	--track-origins=yes ./pipex $(ARGS)

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean:	clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re:	fclean all

.PHONY: all clean fclean re mem bonus
