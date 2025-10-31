NAME := philo

SRCS := \
    src/main.c \
    src/parse.c \
    src/init.c \
    src/time.c \
    src/utils.c \
    src/philo.c \
    src/monitor.c

OBJS := $(SRCS:.c=.o)
DEPS := $(OBJS:.o=.d)

CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
CPPFLAGS := -MMD -MP -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
