#include "../includes/minishell.h"
#include <string.h>

int	str_index(char *line, char c)
{
	static int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	copy_until_dol(char *line, char *newline)
{
	int	i;

	i = 0;
	while (line[i] != '$' && line[i])
	{
		newline[i] = line[i];
		i++;
	}
}

char	*insert_env(char *line, char *env, int l, int i)
{
	int		j;
	int		k;
	char	*newline;
	int		len;

	j = 0;
	k = i + 1;
	len = ft_strlen(line) + l;
	newline = malloc(len);
	newline[len - 1] = '\0';
	copy_until_dol(line, newline);
	while (env && env[j])
	{
		newline[i] = env[j];
		i++;
		j++;
	}
	while (ft_isalnum(line[k]) == 1 || line[k] == '_')
		k++;
	while (line[k])
	{
		newline[i] = line[k];
		k++;
		i++;
	}
	free(line);
	return (newline);
}

char	*expand_readline(t_vars *vars, char *line)
{
	char	*token;
	char	*name;
	int		i;
	int		j;
	int		t;

	name = malloc(TOKENSIZE + 1);
	i = -1;
	while (line[++i])
	{
		j = 0;
		if (line[i] == '$')
		{
			t = i + 1;
			if (line[t] == '?')
			{
				name = add_c_tok(line[t], vars, j, name);
				j++;
			}
			while (ft_isalnum(line[t]) == 1 || line[t] == '_')
			{
				name = add_c_tok(line[t], vars, j, name);
				t++;
				j++;
			}
			name[j] = '\0';
			if (name[0] == '\0')
			{
				free(name);
				return (line);
			}
			token = my_get_env(vars, name);
			j = ft_strlen(token) - ft_strlen(name);
			line = insert_env(line, token, j, i);
			i = -1;
		}
	}
	free(name);
	return (line);
}

void	write_file(t_vars *vars, char *name)
{
	char	*line;
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		throw_error(NULL, errno);
		exit(errno);
	}
	line = readline("heredoc> ");
	if (!line)
	{
		if (close(fd) != 0)
			throw_error(NULL, errno);
		exit(0);
	}
	while (ft_strcmp(line, name) != 0)
	{
		if (!line)
		{
			if (close(fd) != 0)
				throw_error(NULL, errno);
			exit(0);
		}
		if (ft_strcmp(line, name) != 0)
		{
			if (ft_strchr(name, '"') >= 0)
				line = expand_readline(vars, line);
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
		}
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	if (close(fd) != 0)
		 throw_error(NULL, errno);
}

int	redirect_pid(t_vars *vars, char *token, char *name)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_g.pid = fork();
	if (g_g.pid < 0)
		throw_error(NULL, g_g.pid);
	else if (g_g.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ft_strcmp(token, "<") == 0)
			redirect_input(name);
		else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
			redirect_output(name, token);
		else if (ft_strcmp(token, "<<") == 0)
		{
			write_file(vars, name);
			redirect_input("temp");
		}
	}
	return (g_g.pid);
}

int	redirect(t_vars *vars, char *token, char *name)
{
	if (ft_strcmp(token, "<") == 0)
		redirect_input(name);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		redirect_output(name, token);
	else if (ft_strcmp(token, "<<") == 0)
	{
		write_file(vars, name);
		printf("je viens ici?\n");
		redirect_input("temp");
	}
	return (1);
}

int	handle_redirs(t_vars *vars, t_list *tokens)
{
	char	*token;
	char	*name;
	t_list	*temp;

	temp = tokens;
	token = tokens->token;
	name = tokens->next->token;
	(void)vars;
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
//	if (temp && ft_strcmp(temp->token, "|") == 0)
//		return (redirect_pid(vars, token, name, file));
	return (redirect(vars, token, name));
}
