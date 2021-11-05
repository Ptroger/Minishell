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

void  ft_process(t_pipe *store, char **tab, int **pfd, pid_t *child_1)
{
   int      i;
   char     *token_1;
   char     **cmd_1;
//   pid_t    child_1;
   t_pipe   *temp_p;

   i = 0;
   temp_p = store;
//   while (temp_p)
//   {
   printf("HERE\n");
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
      *child_1 = fork();
      if (*child_1 < 0)
      {
         printf("fork failed\n");
         return ;
      }
      if (*child_1 == 0)
      {
         close(*pfd[1]);
         dup2(*pfd[0], 0);
         close(*pfd[0]);
         ft_find_cmd(token_1, cmd_1, tab);
      }
//   }
}

void  ft_child(t_pipe *store, char **tab, int size)
{
   int      a;
   int      b;
   int      count;
   int      i;
   int      status;
   int      *pfd;
   char     *token_1;
//   char     *token_2;
//   char     *token_3;
   char     **cmd_1;
//   char     **cmd_2;
//   char     **cmd_3;
   pid_t    child_1;
//   pid_t    child_2;
//   pid_t    child_3;
   t_pipe   *temp_p;

   i = 0;
   if (size % 2 != 0)
      size++;
   pfd = (int*)malloc(sizeof(int) * size);
   if (!pfd)
      return ;
   while (i < size)
   {
      if (pipe(pfd + i) == -1)
      {
         printf("pipe failed\n");
         return ;
      }
      printf("HERE\n");
      i += 2;
   }
   temp_p = store;
   a = 1;
   b = 1;
   count = 0;
   while (temp_p)
   {
      i = 0;
      token_1 = ft_strdup(temp_p->cell[i]);
      printf("token : %s\n", token_1);
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
      i = 0;
      if (child_1 == 0)
      {
         if (count > 0 && count < size - 1)
            dup2(pfd[a - 1], 0);
         dup2(pfd[a], 1);
         while (i < size)
         {
            close(pfd[i]);
            i++;
         }
         ft_find_cmd(token_1, cmd_1, tab);
      }
   //   if (count == 0)
   //   {
   //      a++;
   //      b--;
         count++;
   //   }
      a += 2;
      temp_p = temp_p->next;
   }
//   ft_process(store, tab, &pfd, &child_2);
/*   i = 0;
   temp_p = store;
   pfd = (int*)malloc(sizeof(int) * size + 1);
   pipe(pfd);
   pipe(pfd + 2);
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
   i = 0;
   if (child_1 == 0)
   {
      dup2(pfd[1], 1);
      while (pfd[i])
      {
         close(pfd[i]);
         i++;
      }
      ft_find_cmd(token_1, cmd_1, tab);
   }
   i = 0;
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
   i = 0;
   if (child_2 == 0)
   {
      dup2(pfd[0], 0);
      dup2(pfd[3], 1);
      while (pfd[i])
      {
         close(pfd[i]);
         i++;
      }
      ft_find_cmd(token_2, cmd_2, tab);
   }
   i = 0;
   temp_p = temp_p->next;
   token_3 = ft_strdup(temp_p->cell[i]);
   cmd_3 = ft_command_size(temp_p->size + 1);
   if (temp_p->size > 1)
   {
      while (i < temp_p->size - 1)
      {
         cmd_3[i + 1] = ft_strdup(temp_p->cell[i + 1]);
   //      printf("%s\n", cmd_3[i + 1]);
         i++;
      }
   }
   child_3 = fork();
   if (child_3 < 0)
   {
      printf("fork failed\n");
      return ;
   }
   i = 0;
   if (child_3 == 0)
   {
      dup2(pfd[2], 0);
      while (pfd[i])
      {
         close(pfd[i]);
         i++;
      }
      ft_find_cmd(token_3, cmd_3, tab);
   }
*/   i = 0;
   printf("size : %i\n", size);
   while (i < size)
   {
      close(pfd[i]);
      printf("i : %i\n", i);
      i++;
   }
   i = 0;
   while (i < size - 1)
   {
      wait(&status);
      i++;
   } 
//   waitpid(child_1, &status, 0);
//   waitpid(child_2, &status, 0);   
//   waitpid(child_3, &status, 0);   
}

int  ft_pipe(t_list *tokens, t_pipe *store, char **tab)
{
   int      i;
   int      j;
   int      size;

   t_list   *temp_1;
   t_list   *temp_2;
   t_pipe   *temp_p;

   i = 0;
   size = 0;
   temp_1 = tokens;
   temp_2 = tokens;
   while (temp_1)
   {
      if (ft_strcmp(temp_1->token, "|") == 0)
         size++;
      temp_1 = temp_1->next;
   }
   size++;
   while (i < size)
   {
      ft_add_elem_pipe(&store);
      i++;
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
   ft_child(store, tab, size);
   return (0);
}