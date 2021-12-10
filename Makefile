NAME    =       minishell

SRCS    =		srcs/token/parse.c \
				srcs/token/handle_dollar.c \
				srcs/token/handle_quotes.c \
				srcs/token/dollar_utils.c \
				srcs/token/parse_utils.c \
				srcs/builtin/call_command.c \
				srcs/builtin/builtin_utils.c \
				srcs/builtin/builtin_utils_2.c \
				srcs/builtin/cd.c \
				srcs/builtin/echo.c \
				srcs/builtin/env.c \
				srcs/builtin/export.c \
				srcs/builtin/pwd.c \
				srcs/builtin/unset.c \
				srcs/pipe/new_readline.c \
				srcs/pipe/pipe.c \
				srcs/pipe/pipe_utils.c \
				srcs/redir/redirect.c \
				srcs/redir/redirs_utils.c \
				srcs/redir/utils.c \
				srcs/shell/signals.c \
				srcs/shell/read.c \
				srcs/shell/memory.c \
				srcs/shell/errors.c \
				srcs/shell/utils.c \
				srcs/pipe/pipe_utils_2.c \

INCLUDE =       includes/

OBJS    =       $(SRCS:%.c=%.o)

CFLAGS  =       -Wall -Wextra -Werror -g -I ./$(INCLUDE) -fsanitize=address

LIBS =			-lreadline -L /usr/local/opt/readline/lib
LIB_INC = 		-I /usr/local/opt/readline/include
LIBFT = 		./libft/libft.a

CC =			gcc

RM =			rm -f

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LIB_INC)

$(NAME):	$(LIBFT) $(OBJS)
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
