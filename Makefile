NAME=minishell
SRC = main.c\
		ft_split.c\
		execution1.c\
		export.c\
	  	cd.c\
	  	unset.c\
	 	 echo.c\
	  	env.c\
		 execut_fun/utils1.c\
		 execut_fun/excute.c\
		 heredoc.c\
		 pwd.c\
		 syntax_handler.c\
		 syntax_handler2.c\
		 exit.c\
		 parsing0.c\
		 parsing01.c\
		 parsing1.c\
		 parsing2.c\
		 parsing3.c\
		 parsing4.c\
		 parsing5.c\
		 parsing6.c\
		 parsing7.c\
		 parsing8.c\
		 parsing9.c\
		 parsing10.c\
		 parsing11.c\
		 parsing12.c\
		 parsing13.c\
		 parsing14.c\
		 parsing15.c\

CC = gcc 

CFLAGS = -Wall -Wextra -Werror  

OBJ=$(SRC:.c=.o)

all:	$(NAME)

$(NAME) : $(OBJ)
	$(CC)   ${CFLAGS} ${OBJ}   -o $(NAME) -lreadline -L /Users/zbentalh/goinfre/homebrew/opt/readline/lib -I /Users/zbentalh/goinfre/homebrew/opt/readline/include

clean:	
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
 
.PHONY: all clean fclean re