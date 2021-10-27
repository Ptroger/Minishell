/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:45:10 by aribesni          #+#    #+#             */
/*   Updated: 2021/10/15 17:45:13 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(char *str)
{
    ft_putendl(str);
}

void    ft_echo_n(char *str)
{
    printf("%s", str);
//    ft_putstr(str);
}
