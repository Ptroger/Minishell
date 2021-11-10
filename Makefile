NAME    =       minishell

SRCS    =		srcs/token/read.c \
				srcs/token/parse.c \
				srcs/token/handle_dollar.c \
				srcs/token/ft_strcpy.c \
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

LIBFT = 		./libft/libft.a

CC =			gcc

RM =			rm -f

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME):	$(LIBFT) $(OBJS) $(DIRH)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME) $(LIBFT)


$(LIBFT):
	@$(MAKE) -s -C libft

all:            $(NAME)

clean:
	@$(MAKE) -s -C libft clean
	$(RM) $(OBJS)

fclean:         clean
	@$(MAKE) -s -C libft fclean
	$(RM) $(NAME)

re:             fclean all

.PHONY:         re all clean fclean%
