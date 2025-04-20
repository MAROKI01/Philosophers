NAME = philo

FLAGS = -Werror -Wextra -Wall -pthread

SRC = main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm *.o 

fclean: clean
	rm $(NAME)