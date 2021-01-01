/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:58:58 by ptroger           #+#    #+#             */
/*   Updated: 2019/11/06 15:00:33 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

void	ft_putstr_fd_echo(char *str, int fd)
{
	int	res;

	if (!str)
		return ;
	res = write(fd, str, ft_strlen(str));
	if (res != 0)
	{
		throw_error(NULL, res);
		exit(errno);
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}
