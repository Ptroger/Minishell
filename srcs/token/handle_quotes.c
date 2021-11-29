#include "../../includes/minishell.h"

void	set_quote(char c, t_vars *vars)
{
	if (c == '"')
		vars->state = D_QUOTE;
	else if (c == '\'')
		vars->state = S_QUOTE;
}

static int	set_state(char c, t_vars *vars, char *token, char *line)
{
	char	t;

	t = line[vars->parse_i + 1];
	if (vars->state == BASIC)
		set_quote(c, vars);
	else
	{
		if (vars->state == D_QUOTE && c == '"')
		{
			if (t == '\0' || t == ' ')
				return (1);
			vars->state = BASIC;
		}
		else if (vars->state == S_QUOTE && c == '\'')
		{
			if (t == '\0' || t == ' ')
				return (1);
			vars->state = BASIC;
		}
		else
			token = add_c_tok(line[vars->parse_i], vars, vars->token_i, token);
	}
	return (0);
}

int	handle_quotes(t_vars *vars, char *token, char *line)
{
	if (set_state(line[vars->parse_i], vars, token, line) == 1)
	{
		token = add_c_tok('\0', vars, vars->token_i, token);
		return (1);
	}
	return (0);
}
