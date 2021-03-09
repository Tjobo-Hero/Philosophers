# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: timvancitters <timvancitters@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/04 10:25:28 by timvancitte   #+#    #+#                  #
#    Updated: 2021/03/09 12:09:28 by timvancitte   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
DEBUG = debug
SRC = main.c utils.c parser.c initialize.c # philosophers.c philo_eat.c philo_write.c philo_utils.c \
		mutex.c get_time.c initialize.c free_philo.c utils.c
OBJ = $(SRC:.c=.o)
CC = clang
CFLAGS = -Wall -Werror -Wextra -g3
.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -pthread

debug: $(OBJ)
	$(CC) $(OBJ) -o $(DEBUG) -g -fsanitize=thread

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG)

re: fclean all