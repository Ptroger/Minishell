#include "../../includes/minishell.h"

char	*my_get_env(t_vars *vars, char *name)
{
	t_sort *envs;

	envs = vars->t_env;
	while (envs)
	{
		if (ft_strcmp((const char *)name, (const char *)envs->name) == 0)
			return (envs->info);
		envs = envs->next;
	}
	return (NULL);
}

char	*expand_env(t_vars *vars, char *token, char *name, char c)
{
	char	*env;
	int		i;

	i = 0;
	env = my_get_env(vars, name);
	if (ft_strcmp("?", name) == 0)
	{
		ft_strcpy_ari(token, ft_itoa(vars->exit_status));
		return (token);
	}
	if (!env)
	{
		token = add_char_to_token('\0', vars, vars->token_i, token);
		return (NULL);
	}
	while (env[i])
	{
		token = add_char_to_token(env[i], vars, vars->token_i, token);
		i++;
	}
	if (vars->state == BASIC || (vars->state == D_QUOTE && c == '"'))
		token = add_char_to_token('\0', vars, vars->token_i, token);
	return (token);
}

int	handle_dollar_quoted(t_vars *vars, char *token, char *line, char *name)
{
	int	j;
	int	temp;

	j = 0;
	temp = vars->token_i;
	if (ft_isalnum(line[vars->parse_i + 1]) == 0 && line[vars->parse_i + 1] != '?')
	{
		token = add_char_to_token('$', vars, vars->token_i, token);
		return (0);
	}
	while (ft_strchr(END_CHARS, line[++vars->parse_i]) == NULL)
	{
		name = add_char_to_token(line[vars->parse_i], vars, j, name);
		j++;
	}
	name = add_char_to_token('\0', vars, j, name);
	vars->token_i = temp;
	token = expand_env(vars, token, name, line[vars->parse_i]);
	if (line[vars->parse_i] == '"')
	{
		printf("ici\n");
		return (1);
	}
	if (line[vars->parse_i] == ' ')
		token = add_char_to_token(' ', vars, vars->token_i, token);
	return (0);
}

void	handle_dollar_unquoted(t_vars *vars, char *token, char *line, char *name)
{
	int	j;
	int	temp;

	temp = vars->token_i;
	j = 0;
	if (!line[vars->parse_i + 1] || line[vars->parse_i + 1] == '"')
	{
		token = add_char_to_token(line[vars->parse_i], vars, vars->token_i, token);
		token = add_char_to_token('\0', vars, vars->token_i, token);
		return ;
	}
	while (ft_strchr(END_CHARS, line[++vars->parse_i]) == NULL)
	{
		name = add_char_to_token(line[vars->parse_i], vars, j, name);
		j++;
	}
	name = add_char_to_token('\0', vars, j, name);
	vars->token_i = temp;
	token = expand_env(vars, token, name, line[vars->parse_i]);
	free(name);
	vars->parse_i--;
	return ;
}

int	handle_dollar(t_vars *vars, char *token, char *line)
{
	char	*name;

	name = malloc(sizeof(char) * vars->token_size + 1);
	name[vars->token_size] = '\0';
	if (vars->state == BASIC)
	{
		handle_dollar_unquoted(vars, token, line, name);
			return (1);
	}
	else if (vars->state == D_QUOTE)
	{
		if (handle_dollar_quoted(vars, token, line, name) == 1)
		{
			free(name);
			return (1);
		}
	}
	else if (vars->state == S_QUOTE)
		token = add_char_to_token('$', vars, vars->token_i, token);
	free(name);
	return (0);
}