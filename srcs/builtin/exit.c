/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:38:48 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 15:44:10 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_args(t_vars *vars, t_list *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	if (i == 1)
		clean_exit(vars, 0);
	return (i);
}

int	is_ok(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '-')
		i++;
	if (!token[i])
		return (FALSE);
	while (token[i])
	{
		if (ft_isdigit(token[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	many_args(void)
{
	throw_error("exit: too many arguments", 2);
	g_g.ret = 1;
}

void	ft_exit(t_vars *vars, t_list *tokens)
{
	int				count;
	long long int	code;

	count = get_args(vars, tokens);
	code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (tokens->next && tokens->next->token)
	{
		if (is_ok(tokens->next->token) == -1)
		{
			throw_error("exit: numeric argument required", 2);
			clean_exit(vars, 2);
		}
	}
	if (count > 2)
		many_args();
	if (count == 2)
	{
		code = ft_atoi(tokens->next->token);
		code = code % 256;
		clean_exit(vars, code);
	}
}
