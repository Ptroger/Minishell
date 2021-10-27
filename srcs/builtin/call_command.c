/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:23:57 by aribesni          #+#    #+#             */
/*   Updated: 2021/10/24 15:23:59 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_call_builtin(t_list *tokens, t_sort **t_env, t_sort  **t_exp)
{
    if (ft_strcmp(tokens->token, "cd") == 0)
        ft_cd(tokens->next->token);
    if (ft_strcmp(tokens->token, "echo") == 0)
    {
        if (ft_strcmp(tokens->next->token, "-n") == 0)
            ft_echo_n(tokens->next->next->token);
        else
            ft_echo(tokens->next->token);
    }
    if (ft_strcmp(tokens->token, "env") == 0)
        ft_env(t_env);
    if (ft_strcmp(tokens->token, "exit") == 0)
        exit(1);
    if (ft_strcmp(tokens->token, "export") == 0)
        ft_export(tokens, t_exp);
    if (ft_strcmp(tokens->token, "pwd") == 0)
            ft_pwd();
}

int     ft_is_buitlin(char *token)
{
    if (ft_strcmp(token, "cd") == 0 || ft_strcmp(token, "echo") == 0
    || ft_strcmp(token, "env") == 0 || ft_strcmp(token, "exit") == 0
    || ft_strcmp(token, "export") == 0 || ft_strcmp(token, "pwd") == 0
    || ft_strcmp(token, "unset") == 0)
        return (1);
    return (0);
}

char    *find_path(t_list *tokens, char *tab)
{
    char    *path;

    path = malloc(sizeof(char) * ft_strlen(tokens->token) + ft_strlen(tab) + 2);
    path = ft_strcpy_ari(path, tab);
    path = ft_strcat(path, "/");
    path = ft_strcat(path, tokens->token);
    return (path);
}

void    call_command(t_list *tokens, t_sort **t_env, t_sort  **t_exp)
{
    int     i;
    char    *cmd[3] = {NULL, NULL, NULL};
    char    **tab;
    pid_t   pid;

    i = 0;
    tab = ft_split(getenv("PATH"), ':');
    if (ft_is_buitlin(tokens->token) == 1)
        ft_call_builtin(tokens, t_env, t_exp);
    else
    {
        if (tokens->next)
            cmd[1] = ft_strdup(tokens->next->token);
        pid = fork();
        wait(NULL);
        if (pid == 0)
        {
            while (tab[i])
            {
                cmd[0] = find_path(tokens, tab[i]);
                if (execve(cmd[0], cmd, 0) == -1)
                    i++;
                free(cmd[0]);
            }
            exit(0);
        }
    }
}
