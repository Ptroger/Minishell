/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:10:26 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:10:29 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int	throw_error(char *err, int errcode)
{
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	else
		ft_putstr_fd(strerror(errcode), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_g.ret = errcode;
	return (0);
}
