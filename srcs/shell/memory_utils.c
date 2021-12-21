/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:13:40 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:13:41 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_vars *vars, int code)
{
	destroy_vars(vars);
	exit(code);
}

char	*dupfree(char *s1, char *s2)
{
	char	*ret;

	ret = NULL;
	if (s2)
		free(s2);
	if (!s1)
		return (NULL);
	ret = ft_strdup(s1);
	return (ret);
}
