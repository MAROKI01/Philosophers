NAME = philo

CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread

SRC = main.c atoi.c routine_utils.c init.c routine.c manipulate_threads.c helpers.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)