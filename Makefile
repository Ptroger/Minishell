NAME    =       minishell

SRCS    =       srcs/read.c                 \
                srcs/parse.c                \
                srcs/ft_lstnew.c			\
                srcs/ft_lstadd_back.c		\
                srcs/ft_strcpy.c			\

INCLUDE =       includes/

OBJS    =       $(SRCS:%.c=%.o)

CFLAGS  =       -Wall -Wextra -Werror -g -I ./$(INCLUDE)

LIBS = -lreadline

CC              =       gcc

RM              =       rm -f

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):        $(OBJS) $(DIRH)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

all:            $(NAME)

clean:
	$(RM) $(OBJS)

fclean:         clean
	$(RM) $(NAME)

re:                     fclean all

.PHONY:         re all clean fclean%