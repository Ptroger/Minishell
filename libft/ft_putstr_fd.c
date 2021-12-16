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
#include <stdlib.h>
#include "../includes/minishell.h"
#include <errno.h>

void	ft_putstr_fd(char *str, int fd)
{
	int	res;

	if (!str)
		return ;
	res = write(fd, str, ft_strlen(str));
	if (res == -1)
	{
		throw_error(NULL, errno);
		exit(errno);
	}
}
