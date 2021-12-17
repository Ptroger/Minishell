/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 18:26:55 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 09:38:11 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_vars *vars, t_list *tokens)
{
	char	*ptr;

	ptr = NULL;
	if (tokens->next && is_special(tokens->next) == FALSE)
	{
		if (tokens->next->type == ARG)
		{
			throw_error("Invalid arguments", 1);
			clean_exit(vars, 1);
		}
	}
	else
	{
		ptr = getcwd(NULL, 0);
		ft_putstr_fd(ptr, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(ptr);
	}
}
