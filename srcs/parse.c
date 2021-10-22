#include "../includes/minishell.h"


// TODO: simplifier fonction get next token

char	*add_char_to_token(char c, t_vars *vars, int i, char *token)
{
	char	*new_token;
	char	*ptr;

	if (i < vars->token_size)
		token[i] = c;
	else
	{
		ptr = token;
		vars->token_size *= 2;
		new_token = malloc(sizeof(char) * vars->token_size);
		ft_strcpy(token, new_token, i);
		token = new_token;
		free(ptr);
	}
	return (token);
}

static void	finish_token(t_vars *vars, char *token)
{
	t_list	*new_tok;

	new_tok = ft_lstnew((void *)token);
	ft_lstadd_back(&vars->tokens, new_tok);
	vars->state = BASIC;
}

static int	set_state(char c, t_vars *vars)
{
	if (vars->state == BASIC)
	{
		if (c == '"')
			vars->state = D_QUOTE;
		else if (c == '\'')
			vars->state = S_QUOTE;
	}
	else
	{
		if (vars->state == D_QUOTE && c == '"')
			return (1);
		else if (vars->state == S_QUOTE && c == '\'')
			return (1);
	}
	return (0);
}

char	*get_next_token(char *line, t_vars *vars, int *i)
{
	char	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(char) * vars->token_size);
	token[0] = '\0';
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			token = add_char_to_token(line[*i], vars, j, token);
			if (set_state(line[*i], vars) == 1)
			{
				*i += 1;
				token = add_char_to_token('\0', vars, ++j, token);
				return (token);
			}
		}
		if (line[*i] != ' ')
			token = add_char_to_token(line[*i], vars, j, token);
		if (line[*i] == ' ')
		{
			if (vars->state == D_QUOTE || vars->state == S_QUOTE)
				token = add_char_to_token(line[*i], vars, j, token);
			else if (*i >= 1 && line[*i - 1] != ' ' && vars->state == BASIC)
			{
				token = add_char_to_token('\0', vars, j, token);
				*i += 1;
				return (token);
			}
			else
				j -= 1;
		}
		*i += 1;
		j++;
	}
	vars->finish_line = TRUE;
	token = add_char_to_token('\0', vars, j, token);
	return (token);
}

void	parse(char *line, t_vars *vars)
{
	int		i;
	char	*token;

	i = 0;
	while (vars->finish_line == FALSE)
	{
		token = get_next_token(line, vars, &i);
//		printf("token = %s\n", token);
		finish_token(vars, token);
	}
	vars->finish_line = FALSE;
}