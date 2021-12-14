#include "minishell.h"

void	redirect_input(char *name)
{
	int	oldfd;
	int	fd;

	fd = open(name, O_RDONLY, 0777);
	if (fd == -1)
	{
		throw_error(NULL, errno);
		return ;
	}
	oldfd = fd;
	printf("je viensla\n");
	dup2(fd, STDOUT_FILENO);
	printf("puisla\n");
	if (close(oldfd) != 0)
		throw_error(NULL, errno);
}

void	redirect_output(char *name, char *token)
{
	int	oldfd;
	int	stdout;
	int	fd;

	if (ft_strcmp(token, ">>") == 0)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		throw_error(NULL, errno);
		return ;
	}
	oldfd = fd;
	printf("jeviensla\n");
	stdout = dup2(fd, STDOUT_FILENO);
	printf("puisla\n");
	if (close(oldfd) != 0)
		throw_error(NULL, errno);
	printf("ici\n");
}
