/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:20:59 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:21:00 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flag_mix(t_vars *vars)
{
	t_list	*tokens;
	int		i;

	tokens = vars->tokens;
	while (tokens)
	{
		i = 0;
		if (ft_strchr(tokens->token, '<') != NULL)
			i += 1;
		if (ft_strchr(tokens->token, '>') != NULL)
			i += 1;
		if (ft_strchr(tokens->token, '|') != NULL)
			i += 1;
		if (i > 0 && tokens->type == NONE)
			tokens->type = SYNTAX_ERROR;
		tokens = tokens->next;
	}
}

int	handle_special(t_vars *vars, char *token, char *line)
{
	if (vars->token_i == 0)
	{
		while (line[vars->parse_i]
			&& ft_strchr(REDIRS_CHARS, line[vars->parse_i]) != NULL)
		{
			token = add_c_tok(line[vars->parse_i], vars, vars->token_i, token);
			vars->parse_i++;
		}
	}
	token = add_c_tok('\0', vars, vars->token_i, token);
	vars->parse_i--;
	return (FINISHED);
}
