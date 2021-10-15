#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "constants.h"

typedef struct	s_list
{
	char	token[1024];
	int		i;
	t_list	*previous;
	t_list	*next;
}				t_list;

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int		shell;
	int		state;
	t_list	*tokens;
}				t_vars;

void	parse(char *line, t_vars *vars);

#endif
