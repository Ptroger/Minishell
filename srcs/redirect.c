#include "../includes/minishell.h"
#include <string.h>

void	redirect_input(char *name, int *file)
{
	int	stdin;

	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		printf("error = %s\n", strerror(*file));
		return ;
	}
	stdin = dup2(*file, STDIN_FILENO);
}

void	redirect_output(char *name, int *file)
{
	int	stdout;

	*file = open(name, O_WRONLY | O_CREAT, 0777);
	if (*file == -1)
	{
		printf("%s\n", strerror(*file));
		return ;
	}
	stdout = dup2(*file, STDOUT_FILENO);
}

int	redirect_pid(char *token, char *name, int *file)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(pid));
		return (pid);
	}
	else if (pid == 0)
	{
		if (ft_strcmp(token, "<") == 0)
			redirect_input(name, file);
		else if (ft_strcmp(token, ">") == 0)
			redirect_output(name, file);
	}
	return (pid);
}

int	redirect(char *token, char *name, int *file)
{
	if (ft_strcmp(token, "<") == 0)
		redirect_input(name, file);
	else if (ft_strcmp(token, ">") == 0)
		redirect_output(name, file);
	return (1);
}

int	handle_redirs(t_list *tokens, int *file)
{
	char	*token;
	char	*name;
	t_list	*temp;

	temp = tokens;
	token = ft_strdup(tokens->token);
	name = ft_strdup(tokens->next->token);
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
	if (temp && ft_strcmp(temp->token, "|") == 0)
		return(redirect_pid(token, name, file));
	return(redirect(token, name, file));
}
