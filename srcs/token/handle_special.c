#include "minishell.h"

int	handle_special(t_vars *vars, char *token, char *line)
{
	char	c;

	c = line[vars->parse_i];
	if (vars->token_i == 0)
	{
		while (ft_strchr(REDIRS_CHARS, c) != NULL)
		{
			token = add_c_tok(c, vars, vars->token_i, token);
			vars->parse_i++;
			c = line[vars->parse_i];
		}
	}
	token = add_c_tok('\0', vars, vars->token_i, token);
	vars->parse_i--;
	return (FINISHED);
}