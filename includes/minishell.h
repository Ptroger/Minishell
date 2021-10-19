#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "constants.h"

typedef struct	s_list
{
	char			*token;
	int				i;
	struct s_list	*next;
}				t_list;

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int		shell;
	int		state;
	int		token_size;
	t_list	*tokens;
}				t_vars;

void	parse(char *line, t_vars *vars);
void	ft_strcpy(char *old, char *ne, int i);
t_list	*ft_lstnew(void *content, int i);
void	ft_lstadd_back(t_list **alst, t_list *new);

#endif
