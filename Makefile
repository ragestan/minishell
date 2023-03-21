NAME=minishell
SRC = main.c\
		ft_split.c\
		utils.c\
		execution1.c\
		export.c\
	  	cd.c\
	  	unset.c\
	 	 echo.c\
	  	env.c\
	 	 pipex.c\
		 execut_fun//utils1.c\

CC = gcc 

CFLAGS = -Wall -Wextra -Werror

OBJ=$(SRC:.c=.o)

all:	$(NAME)

$(NAME) : $(OBJ)
	$(CC) ${CFLAGS} ${OBJ}   -o $(NAME) -lreadline

clean:	
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
 
.PHONY: all clean fclean re