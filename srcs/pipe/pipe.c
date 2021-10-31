/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:59:54 by aribesni          #+#    #+#             */
/*   Updated: 2021/10/29 09:59:56 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int  ft_pipe(t_list *tokens, char **tab)
{
   int     i;
   int     status;
   int     pfd[2];
   char    *cmd[3] = {NULL, NULL, NULL};
   pid_t   child_1;
   pid_t   child_2;

   i = 0;
   if (tokens->next)
   {
      if (tokens->next->next)
      {
         if (ft_strcmp(tokens->next->token, "|") != 0)
            cmd[1] = ft_strdup(tokens->next->next->token);
      }
   }
   if (pipe(pfd) == -1)
   {
      printf("pipe failed\n");
      return (-1);
   }
   child_1 = fork();
   if (child_1 < 0)
   {
      printf("fork failed\n");
      return (-1);
   }
   if (child_1 == 0)
   {
      while (tab[i])
      {
         close(pfd[1]);
         dup2(pfd[0], 0);
         close(pfd[0]);
         cmd[0] = find_path(tokens->next->next->token, tab[i]);
         if (execve(cmd[0], cmd, 0) == -1)
            i++;
         free(cmd[0]);
      }
   }
   child_2 = fork();
   if (child_2 < 0)
   {
      printf("fork failed\n");
      return (-1);
   }
   if (child_2 == 0)
   {
      while (tab[i])
      {
         close(pfd[0]);
         dup2(pfd[1], 1);
         close(pfd[1]);
         cmd[0] = find_path(tokens->token, tab[i]);
         if (execve(cmd[0], cmd, 0) == -1)
            i++;
         free(cmd[0]);
      }
   }
   close(pfd[0]);
   close(pfd[1]);
   waitpid(child_1, &status, 0);
   waitpid(child_2, &status, 0);
   return (0);
}