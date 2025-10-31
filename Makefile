NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
INCLUDES := -Iinclude

SRCS := \
    src/main.c \
    src/parse.c \
    src/init.c \
    src/time.c \
    src/utils.c \
    src/philo.c \
    src/monitor.c

OBJS := $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
