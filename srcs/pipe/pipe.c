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

void  ft_child(t_list *tokens, t_pipe *store, char **tab)
{
   int      i;
   int      size;
   int      status;
   int      pfd[2];
   char     *token_1;
   char     *token_2;
   char     **cmd_1;
   char     **cmd_2;
   pid_t    child_1;
   pid_t    child_2;
   t_list   *temp;

   size = 1;
   temp = tokens;
   if (pipe(pfd) == -1)
   {
      printf("pipe failed\n");
      return (-1);
   }
   while (ft_strcmp(temp->token, "|") != 0)
      temp = temp->next;
   temp = temp->next;
   token_1 = ft_strdup(temp->token);
   while (temp)
   {
      temp = temp->next;
      size++;
   }
   cmd_1 = ft_command_size(size);
   i = 1;
   temp = tokens;
   while (ft_strcmp(temp->token, "|") != 0)
      temp = temp->next;
   temp = temp->next;
   if (size > 2)
   {
      if (temp->next)
         temp = temp->next;
      while (temp)
      {
         cmd_1[i] = temp->token;
         temp = temp->next;
         i++;
      }
   }
   i = 0;
   child_1 = fork();
   if (child_1 < 0)
   {
      printf("fork failed\n");
      return (-1);
   }
   if (child_1 == 0)
   {
      close(pfd[1]);
      dup2(pfd[0], 0);
      close(pfd[0]);
      ft_find_cmd(token_1, cmd_1, tab);
   }
   i = 0;
   size = 1;
   temp = tokens;
   token_2 = ft_strdup(temp->token);
   while (ft_strcmp(temp->token, "|") != 0)
   {
      temp = temp->next;
      size++;
   }
   cmd_2 = ft_command_size(size);
   i = 1;
   temp = tokens;
   if (size > 2)
   {
      if (temp->next)
         temp = temp->next;
      while (ft_strcmp(temp->token, "|") != 0)
      {
         cmd_2[i] = temp->token;
         temp = temp->next;
         i++;
      }
   }
   i = 0;
   child_2 = fork();
   if (child_2 < 0)
   {
      printf("fork failed\n");
      return (-1);
   }
   if (child_2 == 0)
   {
      close(pfd[0]);
      dup2(pfd[1], 1);
      close(pfd[1]);
      ft_find_cmd(token_2, cmd_2, tab);
   }
   close(pfd[0]);
   close(pfd[1]);
   waitpid(child_1, &status, 0);
   waitpid(child_2, &status, 0);
}

void  ft_store_elem(t_list *tokens, t_pipe *store)
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
         return ;
      while (ft_strcmp(temp_2->token, "|") != 0 && j < i + 1)
      {
         temp_p->cell[j] = ft_strdup(temp_2->token);
         if (temp_2->next)
            temp_2 = temp_2->next;
         printf("%s\n", temp_p->cell[j]);
         j++;
      }
      if (ft_strcmp(temp_2->token, "|") == 0 && temp_2->next)
         temp_2 = temp_2->next;
      temp_p = temp_p->next;
   }
}

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

int  ft_pipe(t_list *tokens, t_pipe *store, char **tab)
{
   int      i;
   int      size;
   int      status;
   int      pfd[2];
   char     *token_1;
   char     *token_2;
   char     **cmd_1;
   char     **cmd_2;
   pid_t    child_1;
   pid_t    child_2;
   t_list   *temp;

   size = 1;
   ft_store_elem(tokens, store);
   temp = tokens;
   if (pipe(pfd) == -1)
   {
      printf("pipe failed\n");
      return (-1);
   }
   while (ft_strcmp(temp->token, "|") != 0)
      temp = temp->next;
   temp = temp->next;
   token_1 = ft_strdup(temp->token);
   while (temp)
   {
      temp = temp->next;
      size++;
   }
   cmd_1 = ft_command_size(size);
   i = 1;
   temp = tokens;
   while (ft_strcmp(temp->token, "|") != 0)
      temp = temp->next;
   temp = temp->next;
   if (size > 2)
   {
      if (temp->next)
         temp = temp->next;
      while (temp)
      {
         cmd_1[i] = temp->token;
         temp = temp->next;
         i++;
      }
   }
   i = 0;
   child_1 = fork();
   if (child_1 < 0)
   {
      printf("fork failed\n");
      return (-1);
   }
   if (child_1 == 0)
   {
      close(pfd[1]);
      dup2(pfd[0], 0);
      close(pfd[0]);
      ft_find_cmd(token_1, cmd_1, tab);
   }
   i = 0;
   size = 1;
   temp = tokens;
   token_2 = ft_strdup(temp->token);
   while (ft_strcmp(temp->token, "|") != 0)
   {
      temp = temp->next;
      size++;
   }
   cmd_2 = ft_command_size(size);
   i = 1;
   temp = tokens;
   if (size > 2)
   {
      if (temp->next)
         temp = temp->next;
      while (ft_strcmp(temp->token, "|") != 0)
      {
         cmd_2[i] = temp->token;
         temp = temp->next;
         i++;
      }
   }
   i = 0;
   child_2 = fork();
   if (child_2 < 0)
   {
      printf("fork failed\n");
      return (-1);
   }
   if (child_2 == 0)
   {
      close(pfd[0]);
      dup2(pfd[1], 1);
      close(pfd[1]);
      ft_find_cmd(token_2, cmd_2, tab);
   }
   close(pfd[0]);
   close(pfd[1]);
   waitpid(child_1, &status, 0);
   waitpid(child_2, &status, 0);
   return (0);
}