/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:48:49 by aribesni          #+#    #+#             */
/*   Updated: 2021/11/10 13:25:37 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_pile(t_sort **pile_a)
{
	t_sort		*temp;

	while (*pile_a)
	{
		temp = *pile_a;
		(*pile_a) = (*pile_a)->next;
		free(temp);
	}
}

void	ft_free_pile_p(t_pipe **pile_a)
{
	t_pipe		*temp;

	while (*pile_a)
	{
		temp = *pile_a;
		(*pile_a) = (*pile_a)->next;
		free(temp);
	}
}

void	ft_unset_exp(t_sort **t_env, int i)
{
	int		j;
	t_sort	*temp_1;
	t_sort	*temp_2;
	t_sort	*temp_3;

	j = i - 1;
	temp_1 = *t_env;
	temp_2 = *t_env;
	temp_3 = *t_env;
	while (i-- && temp_2)
		temp_2 = temp_2->next;
	while (j-- && temp_1)
		temp_1 = temp_1->next;
	temp_3 = temp_2->next;
	temp_2->next = NULL;
	temp_1->next = temp_3;
}

void	ft_unset_env(t_sort **t_env, int i)
{
	int		j;
	t_sort	*temp_1;
	t_sort	*temp_2;
	t_sort	*temp_3;

	j = i - 1;
	temp_1 = *t_env;
	temp_2 = *t_env;
	temp_3 = *t_env;
	while (i-- && temp_2->next)
		temp_2 = temp_2->next;
	while (j-- && temp_1)
		temp_1 = temp_1->next;
	temp_3 = temp_2->next;
	temp_2->next = NULL;
	temp_1->next = temp_3;
}

void	ft_parse_unset(t_list *tokens, t_sort **t_env,  t_sort **t_exp, char *tmp)
{
	int		i;
	int		j;
	t_sort	*temp_env;
	t_sort	*temp_exp;

	i = 0;
	j = 0;
	temp_env = *t_env;
	temp_exp = *t_exp;
	if (ft_isalpha(tmp[0]) == 1 || tmp[0] == '_')
	{
		while (tokens->next->token[j] && (tokens->next->token[j] != '+' && tokens->next->token[j] != '='/* && tokens->next->token[j + 1] != '=')*/))
			j++;
		while (tmp[i] != '=' && tmp[i])
		{
			if (((!ft_isalnum(tmp[i])) && tmp[i] != '_') && (tmp[i] == '+' && tmp[i + 1] != '='))
			{
				printf("minishell: unset: `%s': not a valid identifier\n", tmp);
				return ;
			}
			i++;
		}
		while (temp_env->next && ft_strcmp(tokens->next->token, temp_env->name) != 0)
		{
			temp_env = temp_env->next;
			i++;
		}
		i = 0;
		while (temp_exp->next && ft_strncmp(tokens->next->token, temp_exp->data, j) != 0)
		{
			temp_exp = temp_exp->next;
			i++;
		}
		if (temp_env && ft_strcmp(tokens->next->token, temp_env->name) == 0)
			ft_unset_env(t_env, i);
		if (temp_exp && ft_strncmp(tokens->next->token, temp_exp->data, j) == 0)
			ft_unset_exp(t_exp, i);
//		ft_free_pile(t_exp);
//		*t_exp = NULL;
//		ft_set_exp(t_exp, t_env);
	}
	else
		printf("minishell: unset: `%s': not a valid identifier\n", tmp);
}

void	ft_unset(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	int		i;
	char	*tmp;
	t_list	*temp;

	i = 0;
	tmp = NULL;
	temp = tokens;
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0 && is_special(tokens->next) == FALSE)
	{
		while (temp && temp->next && ft_strcmp(temp->next->token, "|") != 0 && is_special(temp->next) == FALSE)
		{
			tmp = ft_strdup(temp->next->token);
			ft_parse_unset(temp, t_env, t_exp, tmp);
			temp = temp->next;
			if (tmp)
				free(tmp);
		}
	}
}
/*
void	ft_parse_export(t_list *tokens, t_sort **t_env, t_sort **t_exp, char *tmp)
{
	int		i;

	i = 0;
	if (ft_isalpha(tmp[0]) == 1 || tmp[0] == '_')
	{
		while (tmp[i] != '=' && tmp[i])
		{
			if (((!ft_isalnum(tmp[i])) && tmp[i] != '_') && (tmp[i] == '+' && tmp[i + 1] != '='))
			{
				printf("minishell: export: `%s': not a valid identifier\n", tmp);
				return ;
			}
			i++;
		}
		ft_set_list(tokens, t_env, t_exp);
	}
	else
		printf("minishell: export: `%s': not a valid identifier\n", tmp);
}

void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	char	*tmp;
	t_list	*temp;

	tmp = NULL;
	temp = tokens;
	if (tokens->next && ft_strcmp(tokens->next->token, "|") != 0 && is_special(tokens->next) == FALSE)
	{
		while (temp && temp->next && ft_strcmp(temp->next->token, "|") != 0 && is_special(temp->next) == FALSE)
		{
			tmp = ft_strdup(temp->next->token);
			ft_parse_export(temp, t_env, t_exp, tmp);
			temp = temp->next;
			if (tmp)
				free(tmp);
		}
	}
	else
		ft_display_exp(t_exp);
}
*/