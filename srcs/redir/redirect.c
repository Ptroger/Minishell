/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:04:02 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:04:04 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>

int	redirect(t_vars *vars, t_list *tokens, char *name, int *file)
{
	t_list	*toks;
	char	*token;

	token = tokens->token;
	toks = vars->tokens;
	if (tokens->type != H_DOC)
		is_dir(vars, name, FALSE);
	if (ft_strcmp(token, "<") == 0)
		redirect_input(vars, tokens, file);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		redirect_output(vars, tokens, token, file);
	else if (ft_strcmp(token, "<<") == 0)
	{
		while (toks && ft_strcmp(toks->token, "<<") != 0)
			toks = toks->next;
		if (toks->index == tokens->index && vars->hrdc == FALSE)
		{
			write_file(vars, name);
			redir_temp(vars, tokens, H_DOC_PATH, file);
			vars->hrdc = TRUE;
		}
	}
	return (1);
}

int	handle_redirs(t_vars *vars, t_list *tokens, int *file)
{
	char	*name;
	t_list	*temp;

	temp = tokens;
	if (tokens->next)
		name = tokens->next->token;
	while (temp && ft_strcmp(temp->token, "<<") != 0)
		temp = temp->next;
	if (temp)
		redirect(vars, temp, name, file);
	return (redirect(vars, tokens, name, file));
}
