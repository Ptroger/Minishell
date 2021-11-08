#include "../../includes/minishell.h"

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
		new_token = malloc(sizeof(char) * vars->token_size + 1);
		new_token[vars->token_size] = '\0';
		ft_strcpy(token, new_token, i);
		token = new_token;
		token[i] = c;
		free(ptr);
	}
	vars->token_i++;
	return (token);
}

static void	finish_token(t_vars *vars, char *token)
{
	t_list	*new_tok;

	new_tok = ft_lstnew((void *)token);
	ft_lstadd_back(&vars->tokens, new_tok);
	vars->state = BASIC;
}

static int	set_state(char c, t_vars *vars, char *token, char *line)
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
		token = add_char_to_token(line[vars->parse_i], vars, vars->token_i, token);
	}
	return (0);
}

int	handle_quotes(t_vars *vars, char *token, char *line)
{
	if (set_state(line[vars->parse_i], vars, token, line) == 1)
	{
		vars->parse_i += 1;
		token = add_char_to_token('\0', vars, vars->token_i, token);
		return (1);
	}
	return (0);
}

int	handle_space(t_vars *vars, char *token, char *line)
{
	if (vars->state == D_QUOTE || vars->state == S_QUOTE)
		token = add_char_to_token(' ', vars, vars->token_i, token);
	else if (vars->parse_i >= 1 && line[vars->parse_i - 1] != ' ' && vars->state == BASIC)
	{
		token = add_char_to_token('\0', vars, vars->token_i, token);
		vars->parse_i += 1;
		return (1);
	}
	return (0);
}

int	handlers(t_vars *vars, char *token, char *line)
{
	if (line[vars->parse_i] == '$')
	{
		printf("vars->parse_i == %d\n", vars->parse_i);
		if (handle_dollar(vars, token, line) == 1)
		{
			return (1);
		}
		printf("DANS token %s|\n", token);
		printf("vars->parse_i == %d\n", vars->parse_i);
	}
	else if (line[vars->parse_i] == '\'' || line[vars->parse_i] == '"')
	{
		if (handle_quotes(vars, token, line) == 1)
			return (1);
		printf("state = %d\n", vars->state);
	}
	else if (line[vars->parse_i] == ' ')
	{
		if (handle_space(vars, token, line) == 1)
			return (1);
	}
	else if (line[vars->parse_i] != ' ' || vars->state == D_QUOTE || vars->state == S_QUOTE)
		token = add_char_to_token(line[vars->parse_i], vars, vars->token_i, token);
	return (0);
}

char	*get_next_token(char *line, t_vars *vars)
{
	char	*token;

	token = malloc(sizeof(char) * vars->token_size + 1);
	token[vars->token_size] = '\0';
	while (line[vars->parse_i])
	{
		if (handlers(vars, token, line) == 1)
			return (token);
		vars->parse_i += 1;
	}
	vars->finish_line = TRUE;
	token = add_char_to_token('\0', vars, vars->token_i, token);
	return (token);
}

void	parse(char *line, t_vars *vars)
{
	char	*token;

	while (vars->finish_line == FALSE)
	{
		vars->token_i = 0;
		token = get_next_token(line, vars);
		finish_token(vars, token);
	}
	vars->finish_line = FALSE;
}