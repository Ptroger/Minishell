#include "minishell.h"

void	init_token(t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size);
	vars->tokens = ft_lstnew((void *)token, 0);
}

void	ft_putstr_lst(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		write(1, &token[i], 1);
		i++;
	}
}
