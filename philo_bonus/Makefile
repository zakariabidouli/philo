CC = gcc

Flags = -g -Werror -Wextra -Wall -pthread 

NAME = philo_bonus

SRC = parse.c philo_bonus.c utils.c ft_atoi.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

%.o: %.c philo_bonus.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re