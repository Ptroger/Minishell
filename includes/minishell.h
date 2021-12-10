#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "constants.h"
# include "../libft/libft.h"

typedef struct		s_glob
{
	pid_t	pid;
	int		ret;
}					t_glob;

typedef struct		s_sort
{
	char			*name;
    char			*data;
	char			*info;
    struct s_sort	*next;
}					t_sort;

typedef struct		s_pipe
{
	int				size;
	char			*token;
	char			**cmd;
	char			**cell;
	struct s_pipe	*next;
}					t_pipe;

typedef struct	s_vars
{
	int		shell;
	int		state;
  	int		token_i;
	int		parse_i;
	int		name_i;
	int		token_size;
	int		finish_line;
	int		exit_status;
	int		special_i;
	int		size;
	char	**path;
	t_pipe	*store;
	t_list	*tokens;
	t_sort	*t_env;
	t_sort	*t_exp;
}				t_vars;

t_glob	g_g;

// TOKENS FUNCTIONS
void	parse(char *line, t_vars *vars);
int		handle_dollar(t_vars *vars, char *token, char *line);
int		handle_quotes(t_vars *vars, char *token, char *line);
int		handle_space(t_vars *vars, char *token, char *line);

// TOKEN UTILS
void	add_token(t_vars *vars, int i);
char	*add_c_tok(char c, t_vars *vars, int i, char *token);
char	*my_get_env(t_vars *vars, char *name);
int		is_valid(t_vars *vars, char *line);
void	cat_ret(char *token, t_vars *vars);
int		ft_mul_strcmp(const char **s1, const char *s2);
void	ft_strcpy_2(char *old, char *ne, int i);
char	*get_tok_index(t_list *lst, int i);
void	finish_token(t_vars *vars, char *token, int i);

// REDIRECTIONS
void	redirect_input(char *name, int *file);
void	redirect_output(char *name, int *file, char *token);
int		handle_redirs(t_vars *vars, t_list *tokens, int *file);
int		is_redir(char *token);
int		is_special(t_list *tokens);
int		ft_pipe(t_vars **vars, t_pipe *pipe);
void	ft_add_elem_pipe(t_pipe **store);

// EXECUTION
int		call_command(t_vars **vars, int is_child);
void	ft_find_cmd(t_vars **vars, char *token, char **cmd, char **tab);

// ENVS
void	ft_get_env_name(t_sort **t_env, char **env);
void	ft_set_env(t_sort **t_env, char **env);

// BUILTINS
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_dup(t_pipe *temp_p, int count, int size, int *pfd);
void	ft_echo(t_list *tokens);
void	ft_echo_n(t_list *tokens);
void	ft_env(t_sort **env);
void	ft_unset(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_export(t_list *tokens, t_sort **t_env, t_sort **t_exp);
void	ft_call_builtin(t_vars **vars, t_list *tokens);
int		ft_is_builtin(char *token);

// MEMORY
void	destroy_vars(t_vars *vars);
t_vars	*ft_init_vars(void);

// OTHERS
void	sig_handler(int sig);
int		throw_error(t_vars *vars, char *err, int errcode);
void	ft_add_elem(t_sort **sort, char *env);
void	ft_add_elem_exp(t_sort **sort, char *env);
void	ft_add_elem_exp_2(t_sort **sort, t_sort *new_elem, char *env);
void	ft_reverse_rotate(t_sort **pile);
void	ft_set_exp(t_sort **t_exp, t_sort **t_env);
void	ft_swap(t_sort **pile);
int		ft_error(char *str);
int		ft_is_key(char *str);
int		ft_new_readline(t_vars **vars);
int		ft_pile_in_order(t_sort **pile_a);
char	*find_path(char *token, char *tab);
char	*ft_return_max(t_sort **pile_a);
char	**ft_command_size(int size);

#endif
