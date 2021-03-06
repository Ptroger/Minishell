/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:20:37 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:20:39 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_env(t_vars *vars, char *token, char *name)
{
	char	*env;
	int		i;

	i = 0;
	if (ft_strcmp("?", name) == 0)
	{
		cat_ret(token, vars);
		return (token);
	}
	env = my_get_env(vars, name);
	if (!env)
	{
		token = add_c_tok('\0', vars, vars->token_i, token);
		return (NULL);
	}
	while (env[i])
	{
		token = add_c_tok(env[i], vars, vars->token_i, token);
		i++;
	}
	if (vars->state == BASIC)
		token = add_c_tok('\0', vars, vars->token_i, token);
	return (token);
}

int	parse_env(t_vars *vars, char *token, char *line, char *name)
{
	if (is_valid(vars, line) == FALSE)
	{
		token = add_c_tok('$', vars, vars->token_i, token);
		return (FALSE);
	}
	vars->parse_i++;
	if (line[vars->parse_i] == '?')
	{
		name = add_c_tok(line[vars->parse_i], vars, vars->special_i, name);
		vars->special_i++;
	}
	else
	{
		while (ft_strchr(END_CHARS, line[vars->parse_i]) == NULL
			&& (ft_isalnum(line[vars->parse_i]) || line[vars->parse_i] == '_'))
		{
			name = add_c_tok(line[vars->parse_i], vars, vars->special_i, name);
			vars->special_i++;
			vars->parse_i++;
		}
		vars->parse_i--;
	}
	name = add_c_tok('\0', vars, vars->special_i, name);
	return (TRUE);
}

int	handle_dollar_quoted(t_vars *vars, char *token, char *line, char *name)
{
	int	temp;

	temp = vars->token_i;
	if (parse_env(vars, token, line, name) == FALSE)
		return (CONTINUE);
	vars->token_i = temp;
	token = expand_env(vars, token, name);
	if (line[vars->parse_i + 1] == '"' && line[vars->parse_i + 2] == '\0')
	{
		token = add_c_tok('\0', vars, vars->token_i, token);
		vars->parse_i++;
		return (FINISHED);
	}
	return (CONTINUE);
}

int	handle_dollar_unquoted(t_vars *vars, char *token, char *line, char *name)
{
	int		temp;
	char	c;

	c = line[vars->parse_i + 1];
	temp = vars->token_i;
	if (parse_env(vars, token, line, name) == FALSE)
		return (CONTINUE);
	vars->token_i = temp;
	token = expand_env(vars, token, name);
	if (c != '\0' && c != ' ')
		return (CONTINUE);
	token = add_c_tok('\0', vars, vars->token_i, token);
	return (FINISHED);
}

int	handle_dollar(t_vars *vars, char *token, char *line)
{
	char	*name;

	name = malloc(sizeof(char) * vars->token_size + 1);
	name[vars->token_size] = '\0';
	vars->special_i = 0;
	if (vars->state == BASIC)
	{
		if (handle_dollar_unquoted(vars, token, line, name) == FINISHED)
		{
			free(name);
			return (FINISHED);
		}
	}
	else if (vars->state == D_QUOTE)
	{
		if (handle_dollar_quoted(vars, token, line, name) == FINISHED)
		{
			free(name);
			return (FINISHED);
		}
	}
	else if (vars->state == S_QUOTE)
		token = add_c_tok('$', vars, vars->token_i, token);
	free(name);
	return (CONTINUE);
}
