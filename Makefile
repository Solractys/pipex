NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes/ft_printf -Iincludes/gnl -g3

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
		includes/gnl/get_next_line.c		\
		includes/gnl/get_next_line_utils.c	\
		src/main.c							\
		src/exec_routine.c					\
		src/free_utils.c					\

ARGS ?=

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

mem:
	valgrind --leak-check=full \
	--show-leak-kinds=all		\
	--track-fds=yes				\
	--track-origins=yes ./pipex $(ARGS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re mem
