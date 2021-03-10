# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: timvancitters <timvancitters@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/04 10:25:28 by timvancitte   #+#    #+#                  #
#    Updated: 2021/03/10 18:13:30 by timvancitte   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# COLORS #

# This is a minimal set of ANSI/VT100 color codes
_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m

# Colors
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m

# Inverted, i.e. colored backgrounds
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m

### COMPILING ###

NAME			=	philo_one

SOURCES			= 	src/main.c \
					src/eat_think_sleep.c \
					src/free_function.c \
					src/initialize.c \
					src/parser.c \
					src/utils.c \

OBJECTS 		=	${SOURCES:%.c=%.o}

FLAGS 			=	-Wall -Wextra -Werror
FLAGS_THREAD	= 	-lpthread
INCLUDES 		=	-I include/
COMPILE			=	gcc


all: $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(_GREEN)----------------------------------------------------"
	@$(COMPILE) $(INCLUDES) $(FLAGS) $(FLAG_THREAD) -o $(NAME) $(OBJECTS)
	@echo "$(_BOLD)Executable				./philo_one"
	@echo "$(_GREEN)----------------------------------------------------"

%.o: %.c
	@echo "$(GREY)Compiling...				$(WHITE)$<"
	@$(COMPILE) $(INCLUDES) $(FLAGS) -c -o $@ $<

clean:
	@echo "$(_YELLOW)----------------------------------------------------"
	@echo "$(_WHITE)$(_BOLD)Removed Object files philo_one"
	@echo "$(_YELLOW)----------------------------------------------------"
	@/bin/rm -f $(OBJECTS) $@ $<

fclean: clean
	@echo "$(_RED)----------------------------------------------------"
	@echo "$(_WHITE)$(_BOLD)Delete ./philo_one"
	@echo "$(_RED)----------------------------------------------------"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
