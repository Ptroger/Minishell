#include "../includes/minishell.h"
#include <string.h>

void	redirect_input(t_vars *vars, char *name, int *file)
{
	int	stdin;

	(void)vars;
	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		printf("error = %s\n", strerror(*file));
		return ;
	}
	stdin = dup2(*file, STDIN_FILENO);
}

void	redirect_output(t_vars *vars, char *name, int *file, char *token)
{
	int	stdout;

	if (ft_strcmp(token, ">>") == 0)
		*file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		*file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	(void)vars;
	*file = open(name, O_WRONLY | O_CREAT, 0777);
	if (*file == -1)
	{
		printf("%s\n", strerror(*file));
		return ;
	}
	stdout = dup2(*file, STDOUT_FILENO);
}

void	read_until(t_vars *vars, char *name, char *token)
{
	char	*line;

	(void)vars;
	printf("token == %s\n", token);
//	token = malloc(jesaispasdecombienencore);
	line = readline("heredoc> ");
	token = ft_strcpy(token, line);
	while (ft_strcmp(line, name) != 0)
	{
		token = ft_strcat(token, (const char *)line);
		free(line);
		line = readline("heredoc> ");
		printf("line == |%s|\n", line);
	}
	free(line);
	printf("token = %s\n", token);
	call_command(&vars, TRUE);
//	TODO: voir avec Aristide pour call command dans quel token je dois rentrer le nouveau token
}

int	redirect_pid(t_vars *vars, char *token, char *name, int *file)
{
	g.pid = fork();
	if (g.pid == -1)
	{
		printf("%s\n", strerror(g.pid));
		return (g.pid);
	}
	else if (g.pid == 0)
	{

		if (ft_strcmp(token, "<") == 0)
			redirect_input(vars, name, file);
		else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
			redirect_output(vars, name, file, token);
		else if (ft_strcmp(token, "<<") == 0)
			read_until(vars, name, token);
	}
	return (g.pid);
}

int	redirect(t_vars *vars, char *token, char *name, int *file)
{
	if (ft_strcmp(token, "<") == 0)
		redirect_input(vars, name, file);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		redirect_output(vars, name, file, token);
	else if (ft_strcmp(token, "<<") == 0)
		read_until(vars, name, token);
	return (1);
}

int	handle_redirs(t_vars **vars, t_list *tokens, t_pipe *store, int *file)
{
	char	*token;
	char	*name;
	t_list	*temp;

	(void)store;
	temp = tokens;
	token = ft_strdup(tokens->token);
	name = ft_strdup(tokens->next->token);
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
	if (temp && ft_strcmp(temp->token, "|") == 0)
		return(redirect_pid(*vars, token, name, file));
	return(redirect(*vars, token, name, file));
}
