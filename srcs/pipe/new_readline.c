/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:08:17 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/26 22:08:19 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_new_readline(t_vars **vars)
{
    int     i;
    int     count;
    char	*line;
    char    *tmp;
    t_list  *temp;

    count = 0;
    temp = (*vars)->tokens;
	line = readline("pipe> ");
    tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
    while (temp)
    {
        tmp = ft_strjoin(tmp, temp->token);
        tmp = ft_strjoin(tmp, " ");
        temp = temp->next;
    }
    while (line[ft_strlen(line) - 1] == '|')
    {
        i = 0;
        tmp = ft_strjoin(tmp, line);
        tmp = ft_strjoin(tmp, " ");
        free(line);
        count++;
        while (i < count)
        {
            printf("pipe> ");
            i++;
        }
        line = readline("pipe> ");
    }
    tmp = ft_strjoin(tmp, line);
    tmp = ft_strjoin(tmp, " ");
    free(line);
    parse(tmp, *vars);
    call_command(vars, FALSE);
    return (1);
}