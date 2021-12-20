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

int	get_args(t_list *tokens)
{
	int	i;

	i = -1;
	while (tokens)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

void	ft_exit(t_vars *vars, t_list *tokens)
{
	int				count;
	long long int	code;


	count = get_args(tokens);
	code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (tokens->next && tokens->next->token)
	{
		if (ft_atoi(tokens->next->token) == -1)
		{
			throw_error("exit: numeric argument required", 2);
			clean_exit(vars, 2);
		}
	}
	if (count > 1)
	{
		throw_error("exit: too many arguments", 2);
		g_g.ret = 1;
	}
	else
		code = ft_atoi(tokens->next->token) % 256;
	clean_exit(vars, code);
}
