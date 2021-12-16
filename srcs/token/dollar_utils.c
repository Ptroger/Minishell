#include "minishell.h"

char	*my_get_env(t_vars *vars, char *name)
{
	t_sort	*envs;

	envs = vars->t_env;
	while (envs)
	{
		if (ft_strcmp((const char *)name, (const char *)envs->name) == 0)
			return (envs->info);
		envs = envs->next;
	}
	return (NULL);
}

void	cat_ret(char *token, t_vars *vars)
{
	int		i;
	char	*ret;

	ret = ft_itoa(vars->exit_status);
	i = 0;
	while (ret[i])
	{
		add_c_tok(ret[i], vars, vars->token_i, token);
		i++;
	}
	free(ret);
}

int	is_valid(t_vars *vars, char *line)
{
	if (ft_isalnum(line[vars->parse_i + 1]) == 0
		&& line[vars->parse_i + 1] != '?')
		return (FALSE);
	return (TRUE);
}

void	ft_strcpy_2(char *old, char *new, int i)
{
	int	n;

	n = 0;
	if (!old || !new)
		return ;
	while (old[n] && n < i)
	{
		new[n] = old[n];
		n++;
	}
	new[n] = '\0';
}
