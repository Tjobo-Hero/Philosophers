# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: timvancitters <timvancitters@student.co      +#+                      #
#                                                    +#+                       #
#    Created: 2021/03/15 11:47:02 by timvancitte   #+#    #+#                  #
#    Updated: 2021/03/15 16:06:36 by timvancitte   ########   odam.nl          #
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

NAME			=	philo_three

SRC_FILES		= 	main \
					eat_think_sleep \
					free_function \
					initialize \
					parser \
					utils \
					pid_action \

SRC_DIR			= 	./src/
OBJ_DIR			= 	./obj/
INCLUDE_DIR		= 	./include/

SRC_FILES 		:= 	$(SRC_FILES:%=%.o)
OBJ_FILES 		:= 	$(SRC_FILES:%=$(OBJ_DIR)%)
INCLUDE_DIR 	:= 	$(INCLUDE_DIR:%=-I%)

OBJS			=  	$(subst .c,.o, $(SRC))

FLAGS 			=	-Wall -Wextra -Werror -g3
FLAGS_THREAD	= 	-lpthread
COMPILE			=	gcc


all: $(NAME)

$(NAME): $(OBJ_FILES)
	@echo "$(_GREEN)----------------------------------------------------"
	@$(COMPILE) $(INCLUDES) $(FLAGS) $(FLAG_THREAD) -o $(NAME) $(OBJ_FILES)
	@echo "$(_BOLD)Executable				./$(NAME)"
	@echo "$(_GREEN)----------------------------------------------------"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@mkdir -p $(OBJ_DIR)
				@echo "$(_WHITE)Compiling...				$(_WHITE)$<"
				@$(CC) $(INCLUDE_DIR) \
				-c $^ \
				-o $@ \
				$(FLAGS)

clean:
	@echo "$(_YELLOW)----------------------------------------------------"
	@echo "$(_WHITE)$(_BOLD)Removed Object files philo_one"
	@echo "$(_YELLOW)----------------------------------------------------"
	@$(RM) -rf $(OBJ_DIR)

fclean: clean
	@echo "$(_RED)----------------------------------------------------"
	@echo "$(_WHITE)$(_BOLD)Delete ./philo_one"
	@echo "$(_RED)----------------------------------------------------"
	@$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
