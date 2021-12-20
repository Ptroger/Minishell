/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aribesni <aribesni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:00:18 by aribesni          #+#    #+#             */
/*   Updated: 2021/12/20 15:00:20 by aribesni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_exp(t_sort **t_exp)
{
	t_sort	*temp_exp;

	temp_exp = *t_exp;
	while (temp_exp->next)
	{
		printf("%s", "declare -x ");
		if (temp_exp->data[0] == '_' && temp_exp->data[1] == '='
			&& temp_exp->data[2] == '/')
			temp_exp = temp_exp->next;
		printf("%s\n", temp_exp->data);
		temp_exp = temp_exp->next;
	}
	printf("%s", "declare -x ");
	printf("%s\n", temp_exp->data);
}


void	ft_set_list_3(t_sort *new_env, int i, int j, int tmp)
{
	while (new_env->data[i])
	{
		new_env->info[j] = new_env->data[i];
		i++;
		j++;
	}
	new_env->info[j] = '\0';
	new_env->next = NULL;
	if (tmp == 1)
	{
		free(new_env->data);
		new_env->data = ft_strjoin(new_env->name, "=");
		new_env->data = ft_strjoin(new_env->data, new_env->info);
	}
}

void	ft_set_list_2(t_sort *new_env)
{
	int		i;
	int		j;
	int		tmp;

	i = 0;
	j = 0;
	tmp = 0;
	new_env->name = malloc(sizeof(char) * ft_strlen(new_env->data));
	new_env->info = malloc(sizeof(char) * ft_strlen(new_env->data));
	if (!new_env->name)
		return ;
	while (new_env->data[i] != '+' && new_env->data[i] != '=')
	{
		new_env->name[i] = new_env->data[i];
		i++;
	}
	new_env->name[i] = '\0';
	if (new_env->data[i] == '+' && new_env->data[i + 1] == '=')
	{
		tmp++;
		i++;
	}
	i++;
	ft_set_list_3(new_env, i, j, tmp);
}


void	ft_set_list(t_list *tokens, t_sort **t_env, t_sort **t_exp)
{
	int		i;
	int		j;
	char	*tmp;
	t_sort	*temp_env;
	t_sort	*temp_exp;

	i = 0;
	j = 0;
	temp_env = *t_env;
	temp_exp = *t_exp;
	while (tokens->next->token[j] && (tokens->next->token[j] != '+' 
        && tokens->next->token[j] != '='))
		j++;
	tmp = (char *)malloc(sizeof(char) * j + 1);
	if (!tmp)
		return ;
	while (i < j)
	{
		tmp[i] = tokens->next->token[i];
		i++;
	}
	tmp[i] = '\0';
	ft_browse_env(tokens, t_env, t_exp, tmp);
	free(tmp);
}
