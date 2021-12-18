#include "../includes/minishell.h"
#include <string.h>

int	redirect(t_vars *vars, t_list *tokens, char *name, int *file)
{
	t_list	*toks;
	char	*token;

	token = tokens->token;
	toks = vars->tokens;
	if (ft_strcmp(token, "<") == 0)
		redirect_input(vars, tokens);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		redirect_output(vars, tokens, token);
	else if (ft_strcmp(token, "<<") == 0)
	{
		while (toks && ft_strcmp(toks->token, "<<") != 0)
			toks = toks->next;
		if (toks->index == tokens->index)
		{
			write_file(vars, name);
			redir_temp(vars, tokens, "temp", file);
		}
	}
	return (1);
}

int	handle_redirs(t_vars *vars, t_list *tokens, int *file)
{
	char	*name;
	t_list	*temp;

	temp = tokens;
	name = tokens->next->token;
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
	return (redirect(vars, tokens, name, file));
}
