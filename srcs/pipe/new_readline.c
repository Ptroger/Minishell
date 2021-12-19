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
    while (line[ft_strlen(line) - 1] == '|')
    {
        tmp = ft_strjoin(tmp, line);
        tmp = ft_strjoin(tmp, " ");
        free(line);
        line = readline("> ");
        if (!line)
		{
        	free(tmp);
        	clean_exit(*vars, 0);
		}
    }
    tmp = ft_strjoin(tmp, line);
    tmp = ft_strjoin(tmp, " ");
    free(line);
    parse(tmp, *vars);
    if ((*vars)->tokens)
        set_type(*vars);
    if (check_syntax(*vars) == TRUE && (*vars)->tokens)
        call_command(vars, FALSE);
}

int ft_new_readline(t_vars **vars)
{
    char	*line;
    char    *tmp;
    t_list  *temp;

    temp = (*vars)->tokens;
	line = readline("> ");
	if (!line)
		clean_exit(*vars, 0);
    tmp = malloc(sizeof(char) * ft_strlen(line) + 1);
    while (temp)
    {
        tmp = ft_strjoin(tmp, temp->token);
        tmp = ft_strjoin(tmp, " ");
        temp = temp->next;
    }
    ft_new_readline_2(vars, line, tmp);
    return (1);
}