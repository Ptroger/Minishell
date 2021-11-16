#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "constants.h"
# include "../libft/libft.h"

typedef struct      s_sort
{
	char			*name;
    char            *data;
    struct s_sort   *next;
}                   t_sort;

typedef	struct		s_pipe
{
	int				size;
	char			*token;
	char			**cmd;
	char			**cell;
	struct s_pipe	*next;
}					t_pipe;

typedef struct	s_vars
{
//	shell = savoir si il faut arrêter minishell
	int		shell;
	int		state;
  	int		token_i;
	int		parse_i;
	int		name_i;
	int		token_size;
	int		finish_line;
	char	**path;
	int		exit_status;
	int		special_i;
	int		size;
	t_pipe	*store;
	t_list	*tokens;
	t_sort	*t_env;
	t_sort	*t_exp;
}				t_vars;

void	add_token(t_vars *vars, int i);
void	ft_add_elem(t_sort **sort, char *env);
void	ft_add_elem_exp(t_sort **sort, char *env);
void	ft_add_elem_exp_2(t_sort **sort, t_sort *new_elem, char *env);
void	ft_add_elem_pipe(t_pipe **store);
void	ft_call_builtin(t_vars **vars);
void    ft_cd(char *path);
void	ft_dup(t_pipe *temp_p, int count, int size, int *pfd);
void    ft_echo(t_list *tokens);
void    ft_echo_n(t_list *tokens);
void    ft_env(t_sort **env);
void    ft_export(t_list *tokens, t_sort **t_env, t_sort  **t_exp);
void	ft_find_cmd(t_vars **vars, char *token, char **cmd, char **tab);
void	ft_free_pile(t_sort **pile_a);
void	ft_free_pile_p(t_pipe **pile_a);
void	ft_get_env_name(t_sort  **t_env, char **env);
void	ft_reverse_rotate(t_sort **pile);
void	ft_set_env(t_sort  **t_env, char **env);
void	ft_set_exp(t_sort  **t_exp, t_sort  **t_env);
void	ft_strcpy_2(char *old, char *ne, int i);
void	ft_swap(t_sort **pile);
void    ft_pwd();
void    ft_unset(t_list *tokens, t_sort **t_env, t_sort  **t_exp);
void	parse(char *line, t_vars *vars);
int		call_command(t_vars **vars, int is_child);
int		ft_error(char *str);
int		ft_is_builtin(char *token);
int		ft_is_key(char *str);
int		ft_pile_in_order(t_sort **pile_a);
int  	ft_pipe(t_vars **vars, t_pipe *pipe);
int		handle_dollar(t_vars *vars, char *token, char *line);
char	*add_char_to_token(char c, t_vars *vars, int i, char *token);
char    *find_path(char *token, char *tab);
char	*ft_return_max(t_sort **pile_a);
char  	**ft_command_size(int size);
int		ft_mul_strcmp(const char **s1, const char *s2);
int 	is_special(t_vars *vars, t_list *tokens);
char	*get_tok_index(t_list *lst, int i);
int		handle_redirs(t_vars **vars, t_list *tokens, t_pipe *store);

#endif
