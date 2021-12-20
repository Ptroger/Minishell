#include "minishell.h"

void	cpy_env(t_sort *temp, char **env, int i, int *j)
{
	while (env[i][*j] != '=')
	{
		temp->name[*j] = env[i][*j];
		*j += 1;
	}
}

int	check_quote(char *str)
{
	int		i;
	int		count;
	char	type;

	type = 0;
	count = 0;
	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	if (str[i])
		type = str[i];
	i = 0;
	while (str[i])
	{
		if (str[i] == type)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (TRUE);
	ft_putstr_fd("No matching quotes found\n", 2);
	return (FALSE);
}

