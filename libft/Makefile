NAME = libft.a

SRC_NAME = ft_isprint.c ft_memmove.c ft_putnbr_fd.c \
ft_strjoin.c ft_strncmp.c ft_calloc.c ft_islower.c ft_isupper.c \
ft_itoa.c ft_memset.c ft_strlcpy.c ft_strcpy.c \
ft_substr.c ft_bzero.c ft_strcmp.c \
ft_memccpy.c ft_putstr_fd.c ft_strcat.c \
ft_strdup.c ft_strlcat.c ft_strtrim.c \
ft_isalnum.c ft_memchr.c \
ft_putchar_fd.c ft_strlen.c \
ft_tolower.c ft_isalpha.c ft_isupper.c \
ft_memcmp.c ft_strchr.c \
ft_strnstr.c ft_toupper.c \
ft_isascii.c ft_memcpy.c ft_putendl_fd.c \
 ft_strmapi.c ft_atoi.c \
ft_strrchr.c ft_isdigit.c \
ft_split.c ft_putchar.c ft_putstr.c ft_putendl.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

BONUS_NAME = ft_lstnew.c ft_lstadd_back.c ft_lstadd_front.c ft_lstdelone.c \
ft_lstiter.c ft_lstmap.c ft_lstsize.c ft_lstclear.c ft_lstlast.c

BONUS_OBJ = $(BONUS_NAME:.c=.o)

CC = gcc
CFLAGS = -Werror -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJ_NAME) $(BONUS_OBJ)
	@ar rc $(NAME) $(OBJ_NAME) $(BONUS_OBJ)
	@ranlib $(NAME)
	@echo "static lib created: libft.a"

bonus : $(NAME) $(BONUS_OBJ)
	@ar rc $(NAME) $(BONUS_OBJ)
	@echo "Bonus added to libft.a"

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^ $(INC)

clean:
	@rm -fv $(OBJ_NAME) $(BONUS_OBJ)

fclean: clean
	@rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC)

.PHONY: all clean bonus fclean re norme
