#include "minishell.h"

int	is_special(t_vars *vars, t_list *tokens)
{
	if (ft_strcmp("<", tokens->token) == 0 || ft_strcmp(">", tokens->token) == 0 || ft_strcmp("<<", tokens->token) == 0
		|| ft_strcmp(">>", tokens->token) == 0)
	{
		vars->special_i = tokens->index;
		return (TRUE);
	}

	return (FALSE);
}

int	is_redir(char *token)
{
	if (ft_strcmp("|", token) == 0 || ft_strcmp("<", token) == 0
		|| ft_strcmp(">", token) == 0 || ft_strcmp("<<", token) == 0
		|| ft_strcmp(">>", token) == 0)
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


int	ft_mul_strcmp(const char **s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != NULL)
	{
		if (ft_strcmp(s1[i], s2) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}