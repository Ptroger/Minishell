#include "../includes/minishell.h"
#include <string.h>

void	redirect_input(t_vars *vars, char *name, int *file)
{
//	int	file;
	int	stdin;

	(void)vars;
//	printf("name == %s\n", name);
	*file = open(name, O_RDONLY, 0777);
	if (*file == -1)
	{
		printf("error = %s\n", strerror(*file));
		return ;
	}
	stdin = dup2(*file, STDIN_FILENO);
//	call_command(&vars, TRUE);
//	close(file);
//	exit(0);
}

void	redirect_output(t_vars *vars, char *name, int *file, char *token)
{
//	int	file;
	int	stdout;

	if (ft_strcmp(token, ">>") == 0)
		file = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	(void)vars;
	*file = open(name, O_WRONLY | O_CREAT, 0777);
	if (*file == -1)
	{
		printf("%s\n", strerror(*file));
		return ;
	}
	stdout = dup2(*file, STDOUT_FILENO);
//	call_command(&vars, TRUE);
//	close(file);
//	exit(0);
}

void	read_until(t_vars *vars, char *name, char *token)
{
	char	*line;

	(void)vars;
	printf("token == %s\n", token);
//	token = malloc(jesaispasdecombienencore);
	line = readline("heredoc> ");
	token = ft_strcpy_ari(token, line);
	while (ft_strcmp(line, name) != 0)
	{
		token = ft_strcat(token, (const char *)line);
		free(line);
		line = readline("heredoc> ");
		printf("line == |%s|\n", line);
	}
	free(line);
	printf("token = %s\n", token);
	call_command(&vars, TRUE);
//	TODO: voir avec Aristide pour call command dans quel token je dois rentrer le nouveau token
}

int	redirect_pid(t_vars *vars, char *token, char *name, int *file)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(pid));
		return (pid);
	}
	else if (pid == 0)
	{

		if (ft_strcmp(token, "<") == 0)
			redirect_input(vars, name, file);
		else if (ft_strcmp(token, ">") == 0)
			redirect_output(vars, name, file);
		else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0)
			redirect_output(vars, name, file, token);
	}
/*	else
	{
//		printf("je suis papa \n");
		wait(NULL);
//		printf("la\n");
	}
*/	return (pid);
//	return (1);
}

int	redirect(t_vars *vars, char *token, char *name, int *file)
{
/*	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("%s\n", strerror(pid));
		return (pid);
	}
	else if (pid == 0)
	{
*/		if (ft_strcmp(token, "<") == 0)
			redirect_input(vars, name, file);
		else if (ft_strcmp(token, ">") == 0)
			redirect_output(vars, name, file);
/*	}
	else
	{
//		printf("je suis papa \n");
		wait(NULL);
//		printf("la\n");
	}
	return (pid);
*/	return (1);
}

int	handle_redirs(t_vars **vars, t_list *tokens, t_pipe *store, int *file)
{
	char	*token;
	char	*name;
	t_list	*temp;

	temp = tokens;
//	token = get_tok_index(tokens, (*vars)->special_i);
	token = ft_strdup(tokens->token);
//	printf("token : %s\n", token);
//	name = get_tok_index(tokens, (*vars)->special_i + 1);
	name = ft_strdup(tokens->next->token);
//	printf("name : %s\n", name);
//	printf("ici token = %s\n", tokens->token);
//	if (ft_strcmp("|", tokens->token) == 0)
//		return (ft_pipe(vars, store));
//	else
	(void)store;
//	printf("name : %s\n", name);
//	printf("token : %s\n", token);
	while (temp && ft_strcmp(temp->token, "|") != 0)
		temp = temp->next;
	if (temp && ft_strcmp(temp->token, "|") == 0)
		return(redirect_pid(*vars, token, name, file));
	return(redirect(*vars, token, name, file));
}
