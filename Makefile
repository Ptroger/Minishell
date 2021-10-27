NAME    =       minishell

SRCS    =		srcs/token/read.c \
				srcs/token/parse.c \
				srcs/token/ft_lstnew.c \
        		srcs/token/ft_lstadd_back.c	\
				srcs/token/ft_strcpy.c \
				srcs/token/ft_lstiter.c \
				srcs/token/ft_lstclear.c \
				srcs/builtin/call_command.c \
				srcs/builtin/cd.c \
				srcs/builtin/echo.c \
				srcs/builtin/env.c \
				srcs/builtin/export.c \
				srcs/builtin/ft_split.c \
				srcs/builtin/ft_putchar.c \
				srcs/builtin/ft_putendl.c \
				srcs/builtin/ft_putstr.c \
				srcs/builtin/ft_strcat.c \
				srcs/builtin/ft_strcpy_ari.c \
				srcs/builtin/ft_strcmp.c \
				srcs/builtin/ft_strdup.c \
				srcs/builtin/ft_strlen.c \
				srcs/builtin/pwd.c \

INCLUDE =       includes/

OBJS    =       $(SRCS:%.c=%.o)

CFLAGS  =       -Wall -Wextra -Werror -fsanitize=address -g -I ./$(INCLUDE)

LIBS =			-lreadline

CC =			gcc

RM =			rm -f

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):        $(OBJS) $(DIRH)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

all:            $(NAME)

clean:
	$(RM) $(OBJS)

fclean:         clean
	$(RM) $(NAME)

re:             fclean all

.PHONY:         re all clean fclean%
