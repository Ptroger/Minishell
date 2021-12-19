#include "minishell.h"

char	*add_c_tok(char c, t_vars *vars, int i, char *token)
{
	char	*new_token;
	char	*ptr;

	
	if (i < vars->token_size)
		token[i] = c;
	else
	{
		ptr = token;
		vars->token_size *= 2;
		new_token = malloc(sizeof(char) * vars->token_size + 1);
		new_token[vars->token_size] = '\0';
		ft_strcpy_2(token, new_token, i);
		token = new_token;
		token[i] = c;
		free(ptr);
	}
	if (c)
		vars->token_i++;
	return (token);
}

void	add_token(t_vars *vars, int i)
{
	t_list	*list;
	char	*token;

	
	token = malloc(sizeof(char) * vars->token_size);
	list = ft_lstnew((void *)token, i);
	ft_lstadd_back(&vars->tokens, list);
}

void	finish_token(t_vars *vars, char *token, int i)
{
	t_list	*new_tok;

	if (token[0])
	{
		new_tok = ft_lstnew((void *) token, i);
		if (vars->been_quoted == TRUE)
			new_tok->type = ARG;
		ft_lstadd_back(&vars->tokens, new_tok);
	}
	else
		free(token);
	vars->state = BASIC;
}

int	handle_space(t_vars *vars, char *token, char *line)
{
	if (vars->state == D_QUOTE || vars->state == S_QUOTE)
		token = add_c_tok(' ', vars, vars->token_i, token);
	else if (vars->token_i == 0)
		return (CONTINUE);
	else if (vars->parse_i >= 1 && line[vars->parse_i - 1]
		!= ' ' && vars->state == BASIC)
	{
		token = add_c_tok('\0', vars, vars->token_i, token);
		return (FINISHED);
	}
	return (CONTINUE);
}
