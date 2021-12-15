#include "../includes/minishell.h"
#include <string.h>

int	redirect_pid(t_vars *vars, char *token, char *name, int *file)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	g_g.pid = fork();
	if (g_g.pid < 0)
		throw_error(NULL, g_g.pid);
	else if (g_g.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (ft_strcmp(token, "<") == 0)
			redirect_input(name, file);
		else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
			redirect_output(name, token, file);
		else if (ft_strcmp(token, "<<") == 0)
		{
			write_file(vars, name);
			redirect_input("temp", file);
		}
	}
	return (g_g.pid);
}

int	redirect(t_vars *vars, t_list *tokens, char *name, int *file)
{
	t_list	*toks;
	char	*token;

	token = tokens->token;
	toks = vars->tokens;
	if (ft_strcmp(token, "<") == 0)
		redirect_input(name, file);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
		redirect_output(name, token, file);
	else if (ft_strcmp(token, "<<") == 0)
	{
		while (toks && toks->type != H_DOC)
			toks = toks->next;
		if (toks->index == tokens->index)
		{
			write_file(vars, name);
			redirect_input("temp", file);
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
	(void)vars;
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
//	if (temp && ft_strcmp(temp->token, "|") == 0)
//		return (redirect_pid(vars, token, name, file));
	return (redirect(vars, tokens, name, file));
}
