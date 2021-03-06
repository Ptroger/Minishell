/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:34:41 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 15:34:42 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_readline(t_vars *vars, char *line)
{
	char	*token;
	char	*name;
	int		i;
	int		j;

	name = malloc(TOKENSIZE + 1);
	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
		{
			if (expand_helper(vars, line, name, i) == FINISHED)
				return (line);
			token = my_get_env(vars, name);
			j = ft_strlen(token) - ft_strlen(name);
			line = insert_env(line, token, j, i);
			i = -1;
		}
	}
	free(name);
	return (line);
}

void	heredoc_loop(t_vars *vars, char **tab, int fd, int i)
{
	char	*line;

	i--;
	while (i >= 0)
	{
		line = readline("> ");
		if (!line)
		{
			if (close(fd) != 0)
				throw_error(NULL, errno);
			clean_exit(vars, 0);
		}
		if (ft_strcmp(line, tab[i]) != 0 && i == 0)
		{
			if (ft_strchr(tab[i], '"') != NULL)
				line = expand_readline(vars, line);
			ft_putstr_fd(line, fd);
			ft_putchar_fd('\n', fd);
		}
		else if (ft_strcmp(line, tab[i]) == 0)
			i--;
		free(line);
	}
}

int	check_limitors(t_vars *vars, int *i)
{
	t_list	*temp;

	temp = vars->tokens;
	while (temp)
	{
		if (temp->type == LIMITOR)
			*i += 1;
		temp = temp->next;
	}
	return (*i);
}

char	**check_multi(t_vars *vars, int *i)
{
	int		j;
	t_list	*temp;
	char	**tab;

	temp = vars->tokens;
	j = check_limitors(vars, i);
	tab = malloc(sizeof(char *) * (j + 1));
	tab[j] = NULL;
	j--;
	while (temp)
	{
		if (temp->type == LIMITOR)
		{
			tab[j] = ft_strdup(temp->token);
			j--;
		}
		temp = temp->next;
	}
	return (tab);
}

void	write_file(t_vars *vars, char *name)
{
	int		fd;
	int		i;
	char	**tab;

	signal(SIGINT, SIG_DFL);
	i = 0;
	tab = check_multi(vars, &i);
	fd = open(H_DOC_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		ft_putstr_fd(H_DOC_PATH, STDERR_FILENO);
		write(2, ": ", 2);
		throw_error(NULL, errno);
		clean_exit(vars, 1);
	}
	(void)name;
	heredoc_loop(vars, tab, fd, i);
	destroy_tab(tab);
	if (close(fd) != 0)
		throw_error(NULL, errno);
}
