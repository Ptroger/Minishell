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

char  **ft_command_size(int size)
{
   int   i;
   char  **cmd;

   cmd = (char**)malloc(sizeof(char*) * (size + 1));
   if (!cmd)
      return (NULL);
   i = size;
   while (i)
   {
      cmd[i] = NULL;
      i--;
   }
   return (cmd);
}

void	ft_add_elem_pipe(t_pipe **store)
{
	t_pipe	*new_elem;

	new_elem = malloc(sizeof(t_pipe));
	if (!new_elem)
		return ;
   new_elem->cell = NULL;
	new_elem->next = *store;
	*store = new_elem;
}

void  ft_process()
{
   int      i;
   int      status;
   int      pfd[2];
   char     *token_1;
   char     *token_2;
   char     **cmd_1;
   char     **cmd_2;
   pid_t    child_1;
   pid_t    child_2;
   t_pipe   *temp_p;

   if (pipe(pfd) == -1)
   {
      printf("pipe failed\n");
      return ;
   }
   i = 0;
   temp_p = store;
   while (temp_p)
   {
      token_1 = ft_strdup(temp_p->cell[i]);
      cmd_1 = ft_command_size(temp_p->size + 1);
      if (temp_p->size > 1)
      {
         while (i < temp_p->size - 1)
         {
            cmd_1[i + 1] = ft_strdup(temp_p->cell[i + 1]);
            i++;
         }
      }
      child_1 = fork();
      if (child_1 < 0)
      {
         printf("fork failed\n");
         return ;
      }
      if (child_1 == 0)
      {
         close(pfd[0]);
         dup2(pfd[1], 1);
         close(pfd[1]);
         ft_find_cmd(token_1, cmd_1, tab);
      }
   }
}

void  ft_child(t_pipe *store, char **tab)
{
   int      i;
   int      status;
   int      pfd[2];
   char     *token_1;
   char     *token_2;
   char     **cmd_1;
   char     **cmd_2;
   pid_t    child_1;
   pid_t    child_2;
   t_pipe   *temp_p;

   if (pipe(pfd) == -1)
   {
      printf("pipe failed\n");
      return ;
   }
   i = 0;
   temp_p = store;
   while (temp_p)
   {
      token_1 = ft_strdup(temp_p->cell[i]);
      cmd_1 = ft_command_size(temp_p->size + 1);
      if (temp_p->size > 1)
      {
         while (i < temp_p->size - 1)
         {
            cmd_1[i + 1] = ft_strdup(temp_p->cell[i + 1]);
            i++;
         }
      }
      child_1 = fork();
      if (child_1 < 0)
      {
         printf("fork failed\n");
         return ;
      }
      if (child_1 == 0)
      {
         close(pfd[0]);
         dup2(pfd[1], 1);
         close(pfd[1]);
         ft_find_cmd(token_1, cmd_1, tab);
      }
   }
/*   token_1 = ft_strdup(temp_p->cell[i]);
   cmd_1 = ft_command_size(temp_p->size + 1);
   if (temp_p->size > 1)
   {
      while (i < temp_p->size - 1)
      {
         cmd_1[i + 1] = ft_strdup(temp_p->cell[i + 1]);
         i++;
      }
   }
   child_1 = fork();
   if (child_1 < 0)
   {
      printf("fork failed\n");
      return ;
   }
   if (child_1 == 0)
   {
      close(pfd[0]);
      dup2(pfd[1], 1);
      close(pfd[1]);
      ft_find_cmd(token_1, cmd_1, tab);
   }
   i = 0;
   temp_p = store;
   temp_p = temp_p->next;
   token_2 = ft_strdup(temp_p->cell[i]);
   cmd_2 = ft_command_size(temp_p->size + 1);
   if (temp_p->size > 1)
   {
      while (i < temp_p->size - 1)
      {
         cmd_2[i + 1] = ft_strdup(temp_p->cell[i + 1]);
         i++;
      }
   }
   child_2 = fork();
   if (child_2 < 0)
   {
      printf("fork failed\n");
      return ;
   }
   if (child_2 == 0)
   {
      close(pfd[1]);
      dup2(pfd[0], 0);
      close(pfd[0]);
      ft_find_cmd(token_2, cmd_2, tab);
   }
*/   close(pfd[1]);
   close(pfd[0]);
   waitpid(child_1, &status, 0);
   waitpid(child_2, &status, 0);
}

int  ft_pipe(t_list *tokens, t_pipe *store, char **tab)
{
   int      i;
   int      j;

   t_list   *temp_1;
   t_list   *temp_2;
   t_pipe   *temp_p;

   i = 0;
   temp_1 = tokens;
   temp_2 = tokens;
   while (temp_1)
   {
      if (ft_strcmp(temp_1->token, "|") == 0)
         i++;
      temp_1 = temp_1->next;
   }
   i++;
   while (i > 0)
   {
      ft_add_elem_pipe(&store);
      i--;
   }
   temp_1 = tokens;
   temp_p = store;
   while (temp_p)
   {
      i = 0;
      j = 0;
      while (ft_strcmp(temp_1->token, "|") != 0 && temp_1->next)
      {
         temp_1 = temp_1->next;
         i++;
      }
      if (ft_strcmp(temp_1->token, "|") == 0 && temp_1->next)
         temp_1 = temp_1->next;
      temp_p->cell = (char**)malloc(sizeof(char*) * i + 1);
      if (!temp_p->cell)
         return (-1);
      while (ft_strcmp(temp_2->token, "|") != 0 && j < i + 1)
      {
         temp_p->cell[j] = ft_strdup(temp_2->token);
         if (temp_2->next)
            temp_2 = temp_2->next;
         j++;
      }
      if (ft_strcmp(temp_2->token, "|") == 0 && temp_2->next)
         temp_2 = temp_2->next;
      temp_p->size = j;
      temp_p = temp_p->next;
   }
   ft_child(store, tab);
   return (0);
}