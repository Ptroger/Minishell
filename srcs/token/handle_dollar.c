#include "../../includes/minishell.h"

//static int	handle_space(t_vars *vars, char *token)
//{
//	if (vars->state == BASIC || vars->state == F_STRING)
//		return (1);
//	else
//		token = add_char_to_token(' ', vars, vars->token_i, token);
//	return (0);
//}
//
//static int	handle_quotes(t_vars *vars, char *token, char *line)
//{
//	if (vars->state == EXTENDING)
//		return (1);
//	if (vars->state == BASIC)
//	{
//		if (line[vars->parse_i] == '"')
//		{
//			token = add_char_to_token('$', vars, vars->token_i, token);
//			vars->token_i++;
//			vars->state = D_STRING;
//		}
//		else
//			vars->state = S_STRING;
//	}
//	else
//	{
//		if ((vars->state == D_QUOTE || vars->state == D_STRING) && line[vars->parse_i] == '"')
//		{
//			vars->state = F_STRING;
//			return (0);
//		}
//		else if ((vars->state == S_QUOTE || vars->state == S_STRING) && line[vars->parse_i] == '\'')
//		{
//			vars->state = F_STRING;
//			return (0);
//		}
//		token = add_char_to_token(line[vars->parse_i], vars, vars->token_i, token);
//		vars->token_i++;
//	}
//	return (0);
//}

char	*expand_env(t_vars *vars, char *token, char *name, char c)
{
	char	*env;
	int		i;

	i = 0;
	env = getenv(name);
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
	if (ft_isalnum(line[vars->parse_i + 1]) == 0)
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
		return (1);
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