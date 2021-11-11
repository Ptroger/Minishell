#include "../includes/minishell.h"
#include <string.h>

char	*get_tok_index(t_list *lst, int i)
{
	while (lst && lst->index != i)
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

int	check_redirs(t_vars *vars)
{
	t_list	*iter;
	int	i;

	i = 0;
	iter = vars->tokens;
	while (iter)
	{
		if (ft_mul_strcmp(REDIRS_STRINGS, iter->token) == TRUE)
		return (i);
		iter = iter->next;
		i++;
	}
	return (-1);
}

void	redirect_input(t_vars *vars, char *token, char *name, int fd)
{
	int	file;
	int	stdin;

	file = open(name, O_RDONLY, 0777);
	if (file == -1)
	{
		printf("%s\n", strerror(file));
		return ;
	}
	stdin = dup2(file, STDIN_FILENO);
	close(file);
//	exec command
	else
		wait(NULL);
}

void	redirect_output(t_vars *vars, char *token, char *name, int fd)
{
	int	file;
	int	stdout;

	file = open(name, O_WRONLY | O_CREAT, 0777);
	if (file == -1)
	{
		printf("%s\n", strerror(file));
		return ;
	}
	stdout = dup2(file, STDOUT_FILENO);
	close(file);
//	exec command
	else
		wait(NULL);
}

void	redirect(t_vars *vars, char *token, char *name, int fd)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(pid));
		return ;
	}
	else if (pid == 0)
	{
		if (ft_strcmp(token, "<") == 0)
			redirect_input(vars, tok, name, fd);
		else if (ft_strcmp(token, ">") == 0)
			redirect_output(vars, tok, name, fd);
//		else if (ft_strcmp(token, "|") == 0)
//			redirect_pipe(vars);
	}
}

void	handle_redirs(t_vars *vars)
{
	int res;
	char	*token;
	char	*name;

	token = get_tok_index(vars->tokens, res - 1);
	name = get_tok_index(vars->tokens, res + 1);
	res = check_redirs(vars);
	//		ya r
	if (res == -1)
		return ;
	//		Cas ou on redirige depuis ou vers l'entrée ou la sortie standard
	else if (res == 0 && ft_lstlast(vars->tokens)->index == 1)
		redirect(vars, NULL, name, TRUE);
	//		Cas normal
	else
		redirect(vars, token, name, FALSE)
}