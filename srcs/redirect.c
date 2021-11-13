#include "../includes/minishell.h"
#include <string.h>

void	redirect_input(t_vars *vars, char *name)
{
	int	file;
	int	stdin;

//	printf("name == %s\n", name);
	file = open(name, O_RDONLY, 0777);
	if (file == -1)
	{
		printf("error = %s\n", strerror(file));
		return ;
	}
	stdin = dup2(file, STDIN_FILENO);
	call_command(&vars, TRUE);
	close(file);
	exit(0);
}

void	redirect_output(t_vars *vars, char *name)
{
	int	file;
	int	stdout;

	file = open(name, O_WRONLY | O_CREAT, 0777);
	if (file == -1)
	{
		printf("%s\n", strerror(file));
		return ;
	}
	stdout = dup2(file, STDOUT_FILENO);
	call_command(&vars, TRUE);
	close(file);
	exit(0);
}

int	redirect(t_vars *vars, char *token, char *name)
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
			redirect_input(vars, name);
		else if (ft_strcmp(token, ">") == 0)
			redirect_output(vars, name);
	}
	else
	{
//		printf("je suis papa \n");
		wait(NULL);
//		printf("la\n");
	}
	return (pid);
}

int	handle_redirs(t_vars *vars, t_list *tokens, t_pipe *store, char **tab)
{
	char	*token;
	char	*name;

	token = get_tok_index(tokens, vars->special_i);
	name = get_tok_index(tokens, vars->special_i + 1);
	if (ft_strcmp("|", tokens->token) == 0)
		return (ft_pipe(&vars, tokens, store, tab));
	else
		return (redirect(vars, token, name));
}
