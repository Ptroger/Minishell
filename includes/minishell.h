#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "constants.h"

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int	shell;
}				t_vars;

typedef struct	s_corres
{

}				t_corres;

void	parse(char *line);

#endif
