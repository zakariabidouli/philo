cc = gcc

FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo

M_SRC = philo.c parse_in.c ft_atoi.c utils.c\

M_OBJ = $(M_SRC:.c=.o)

all: $(NAME)

$(NAME): $(M_OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(M_OBJ)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(M_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
