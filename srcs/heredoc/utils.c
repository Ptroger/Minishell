#include "minishell.h"

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

int	insert_helper(char *newline, char *env, int i)
{
	int	j;

	j = 0;
	while (env && env[j])
	{
		newline[i] = env[j];
		i++;
		j++;
	}
	return (i);
}

char	*insert_env(char *line, char *env, int l, int i)
{
	int		k;
	char	*newline;
	int		len;

	k = i + 1;
	len = ft_strlen(line) + l;
	newline = malloc(len);
	newline[len - 1] = '\0';
	copy_until_dol(line, newline);
	i = insert_helper(newline, env, i);
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

int	expand_helper(t_vars *vars, char *line, char *name, int i)
{
	int	t;
	int	j;

	t = i + 1;
	j = 0;
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
		return (FINISHED);
	}
	return (CONTINUE);
}
