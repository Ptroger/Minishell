/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:39:41 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:32:51 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_absolute(char *token)
{
	if (token && (token[0] == '.' || token[0] == '/'))
		return (TRUE);
	return (FALSE);
}

int	ft_is_key(char *str)
{
	if (ft_strcmp(str, "|") == 0 || ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}

int	ft_is_redir(char *str)
{
	if (ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, ">>") == 0)
		return (1);
	return (0);
}
