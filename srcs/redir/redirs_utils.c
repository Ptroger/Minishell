#include "minishell.h"

void	redirect_input(char *name, int *file)
{
	int	stdin;

	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		printf("error input = %s\n", strerror(*file));
		return ;
	}
	stdin = dup2(*file, STDIN_FILENO);
}

void	redirect_output(char *name, int *file, char *token)
{
	int	stdout;

	if (ft_strcmp(token, ">>") == 0)
		*file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		*file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (*file == -1)
	{
		printf("%s\n", strerror(*file));
		return ;
	}
	stdout = dup2(*file, STDOUT_FILENO);
}
