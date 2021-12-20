/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:22:10 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 16:22:11 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_unset_2(t_list *tokens, t_sort **t_env, t_sort **t_exp, int j)
{
	int		i;
	t_sort	*temp_env;
	t_sort	*temp_exp;

	i = 0;
	temp_env = *t_env;
	temp_exp = *t_exp;
	while (temp_env->next
		&& ft_strcmp(tokens->next->token, temp_env->name) != 0)
	{
		temp_env = temp_env->next;
		i++;
	}
	i = 0;
	while (temp_exp->next
		&& ft_strncmp(tokens->next->token, temp_exp->data, j) != 0)
	{
		temp_exp = temp_exp->next;
		i++;
	}
	if (temp_env && ft_strcmp(tokens->next->token, temp_env->name) == 0)
		ft_unset_env(t_env, i);
	if (temp_exp && ft_strncmp(tokens->next->token, temp_exp->data, j) == 0)
		ft_unset_exp(t_exp, i);
}

void	ft_parse_unset(t_list *tokens, t_sort **t_env,
t_sort **t_exp, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ft_isalpha(tmp[0]) == 1 || tmp[0] == '_')
	{
		while (tokens->next->token[j] && (tokens->next->token[j] != '+'
				&& tokens->next->token[j] != '='))
			j++;
		while (tmp[i] != '=' && tmp[i])
		{
			if (((!ft_isalnum(tmp[i])) && tmp[i] != '_')
				&& (tmp[i] == '+' && tmp[i + 1] != '='))
			{
				printf("minishell: unset: `%s': not a valid identifier\n",
					tmp);
				return ;
			}
			i++;
		}
		ft_parse_unset_2(tokens, t_env, t_exp, j);
	}
	else
		printf("minishell: unset: `%s': not a valid identifier\n", tmp);
}
