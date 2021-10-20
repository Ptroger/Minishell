#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "constants.h"

typedef struct	s_list
{
	char			*token;
	struct s_list	*next;
}				t_list;

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int		shell;
	int		state;
	int		token_size;
	int		finish_line;
	t_list	*tokens;
}				t_vars;

void	parse(char *line, t_vars *vars);
void	ft_strcpy(char *old, char *ne, int i);
t_list	*ft_lstnew(void *content);
void	ft_lstiter(t_list *lst, void (*f)(char *));
void	ft_lstclear(t_list **alst, void (*del)(void *));
void	add_token(t_vars *vars);
void	ft_lstadd_back(t_list **alst, t_list *new);

#endif
