NAME 	= philo

SRC 	= 	lib.c 		check.c 	main.c\
			free.c		init.c		threads.c\
			utils.c		print.c		monitor.c

D_SRC	= src
D_OBJ	= obj
INCL	= philo.h

SRC 	:= $(SRC:%.c=$(D_SRC)/%.c)
OBJ 	= $(SRC:$(D_SRC)/%.c=$(D_OBJ)/%.o)

FLAGS 	= -Wall -Werror -Wextra -pthread # -fsanitize=address -fsanitize=undefined # -fsanitize=thread
OPT		= -O3

PINK 		=  \033[1;35m
NO_COLOR 	=	\033[0m 

all : $(NAME)

$(NAME) : $(OBJ) $(INCL)
	gcc $(OBJ) $(FLAGS) $(OPT) -I. -o $(NAME)
	@echo "$(PINK)You compiled the mandatory part of the project.$(NO_COLOR)"

$(D_OBJ)/%.o : $(D_SRC)/%.c $(INCL)
	@mkdir -p $(D_OBJ)
	gcc $(FLAGS) -I. -c $< -o $@

clean :
	@$(RM) -rf $(D_OBJ)

fclean : clean
	@$(RM) -rf $(NAME)

re : fclean all

.PHONY :
	all clean fclean re bonus