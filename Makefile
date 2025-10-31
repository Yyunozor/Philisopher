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
	src/actions.c \
	src/routine.c \
	src/threads.c \
	src/monitor.c

OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

-include $(DEPS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all
