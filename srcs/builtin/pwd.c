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

void	ft_pwd(t_list *tokens)
{
	char	*buf;

	buf = NULL;
	if (tokens->next)
	{
		if (tokens->next->type == ARG)
		{
			throw_error("Invalid arguments", 1);
			exit(1);
		}
	}
	else
		printf("%s\n", (getcwd(buf, sizeof(buf))));
}
