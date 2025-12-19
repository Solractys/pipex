NAME = "pipex"

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes/ft_printf -g3

SRCS = $(shell find src -name "*.c")
SRCS += $(shell find includes/ft_printf -name "*.c")

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
