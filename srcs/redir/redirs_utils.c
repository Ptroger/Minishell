#include "minishell.h"

void	redirect_input(char *name, int *file)
{
	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		throw_error(NULL, errno);
		exit(errno);
	}
	dup2(*file, STDIN_FILENO);
}

void	redirect_output(char *name, char *token, int *file)
{
	if (ft_strcmp(token, ">>") == 0)
		*file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		*file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*file == -1)
	{
		throw_error(NULL, errno);
		return ;
	}
	dup2(*file, STDOUT_FILENO);
}
