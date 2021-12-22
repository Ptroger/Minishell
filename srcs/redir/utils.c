/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptroger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:04:26 by ptroger           #+#    #+#             */
/*   Updated: 2021/12/20 12:04:27 by ptroger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sys/stat.h"
#include "sys/types.h"
#include "minishell.h"

void	need_exit(t_vars *vars, int ret, int is_exec, char *path)
{
	if (ret == -1 && errno == ENOTDIR)
	{
		ft_putstr_fd(path, 2);
		throw_error(": Not a directory", 126);
		clean_exit(vars, 126);
	}
	else if (ret == -1 && errno == 2 && is_exec == TRUE)
	{
		ft_putstr_fd(path, 2);
		throw_error(": No such file or directory", 127);
		clean_exit(vars, 127);
	}
	else if (ret == -1 && is_exec == TRUE)
	{
		ft_putstr_fd(path, 2);
		throw_error(": command not found", 127);
		clean_exit(vars, 127);
	}
}

int	is_dir(t_vars *vars, char *path, int is_exec)
{
	int			x;
	struct stat	p;
	int			ret;

	p.st_mode = 1;
	x = 0;
	stat(path, &p);
	x = S_ISDIR(p.st_mode);
	ret = access(path, X_OK & W_OK);
	if (x == 0)
		return (FALSE);
	else if (is_exec >= TRUE && x == 0)
	{
		need_exit(vars, ret, is_exec, path);
		return (FALSE);
	}
	else
	{
		ft_putstr_fd(path, 2);
		throw_error(": is a directory", 1);
		clean_exit(vars, 1);
	}
	return (TRUE);
}

int	shall_exec(t_vars *vars, t_list *token)
{
	t_list	*toks;

	toks = vars->tokens;
	if (token->type == H_DOC)
	{
		while (toks && toks->type != H_DOC)
			toks = toks->next;
		if (toks && toks->index != token->index)
			return (FALSE);
	}
	return (TRUE);
}

int	is_special(t_list *tokens)
{
	if (ft_strcmp("<", tokens->token) == 0 || ft_strcmp(">", tokens->token) == 0
		|| ft_strcmp("<<", tokens->token) == 0
		|| ft_strcmp(">>", tokens->token) == 0)
		return (TRUE);
	return (FALSE);
}

char	*get_tok_index(t_list *lst, int i)
{
	while (lst->next && lst->index != i)
		lst = lst->next;
	if (!lst)
		return (NULL);
	return (lst->token);
}
