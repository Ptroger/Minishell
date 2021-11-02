/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:24:38 by aribesni          #+#    #+#             */
/*   Updated: 2021/10/19 14:24:39 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(t_sort  **t_env)
{
    t_sort  *temp;

    temp = *t_env;
    while (temp->next)
    {
        printf("%s\n", temp->str);
        temp = temp->next;    
    }
/*    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);    
        i++;
    }
*/
}