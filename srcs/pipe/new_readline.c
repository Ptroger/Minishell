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

void    ft_new_readline_2(t_vars **vars, char *line, char *tmp)
{
    char    *ptr;

    while (line[ft_strlen(line) - 1] == '|')
    {
        ptr = tmp;
        tmp = ft_strjoin(tmp, line);
        free(ptr);
        ptr = tmp;
        tmp = ft_strjoin(tmp, " ");
        free(ptr);
        free(line);
        line = readline("> ");
        if (!line)
		{
        	free(tmp);
        	clean_exit(*vars, 0);
		}
    }
    tmp = ft_strjoin(tmp, line);
    ptr = tmp;
    tmp = ft_strjoin(tmp, " ");
    free(ptr);
    free(line);
    parse(tmp, *vars);
    call_command(vars, FALSE);
}

int ft_new_readline(t_vars **vars)
{
    char	*line;
    char    *tmp;
    char    *ptr;
    t_list  *temp;

    temp = (*vars)->tokens;
	line = readline("> ");
	if (!line)
		clean_exit(*vars, 0);
    tmp = ft_strdup(temp->token);
    temp = temp->next;
    while (temp)
    {
        ptr = tmp;
        tmp = ft_strjoin(tmp, " ");
        free(ptr);
        ptr = tmp;
        tmp = ft_strjoin(tmp, temp->token);
        free(ptr);
        temp = temp->next;
    }
    ft_new_readline_2(vars, line, tmp);
    return (1);
}