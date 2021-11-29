#include "../includes/minishell.h"

void	write_file(char *name, int *file)
{
	char	*line;

	*file = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	line = readline("heredoc> ");
	while (ft_strcmp(line, name) != 0)
	{
		if (ft_strcmp(line, name) != 0)
		{
			ft_putstr_fd(line, *file);
			ft_putchar_fd('\n', *file);
		}
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	close(*file);
}

int	redirect_pid(char *token, char *name, int *file)
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
			redirect_input(name, file);
		else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
			redirect_output(name, file, token);
		else if (ft_strcmp(token, "<<") == 0)
		{
			write_file(name, file);
			redirect_input("temp", file);
		}
	}
	return (g.pid);
}

int	redirect(char *token, char *name, int *file)
{
	if (ft_strcmp(token, "<") == 0)
		redirect_input(name, file);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		redirect_output(name, file, token);
	else if (ft_strcmp(token, "<<") == 0)
	{
		write_file(name, file);
		redirect_input("temp", file);
	}
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
		return (redirect_pid(token, name, file));
	return (redirect(token, name, file));
}
