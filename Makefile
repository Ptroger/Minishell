NAME    =       minishell

SRCS    =		srcs/token/read.c \
				srcs/token/parse.c \
				srcs/token/handle_dollar.c \
				srcs/token/ft_strcpy_2.c \
				srcs/token/destroy.c \
				srcs/builtin/call_command.c \
				srcs/builtin/builtin_utils.c \
				srcs/builtin/builtin_utils_2.c \
				srcs/builtin/cd.c \
				srcs/builtin/echo.c \
				srcs/builtin/env.c \
				srcs/builtin/export.c \
				srcs/builtin/pwd.c \
				srcs/builtin/unset.c \
				srcs/pipe/pipe.c \
				srcs/pipe/pipe_utils.c \
				srcs/redirect.c \
				srcs/utils.c \
				srcs/signals.c \

INCLUDE =       includes/

OBJS    =       $(SRCS:%.c=%.o)

CFLAGS  =       -Wall -Wextra -Werror -g -I ./$(INCLUDE) #-fsanitize=address

LIBS =			-lreadline -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include

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
