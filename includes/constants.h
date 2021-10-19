#ifndef CONSTANTS_H
# define CONSTANTS_H

//// PROMPT ////

# define PROMPT "minishell> "
# define RUNNING 1
# define EXIT 0

//// STATES ////

# define BASIC 0
# define D_QUOTE 1
# define S_QUOTE 2

//// TOKEN_TYPES ////

# define TOK_REDIR 0
# define TOK_PIPE 1
# define TOK_VAR 2
# define TOK_QUOTE 3
# define TOK_SIMP 4

//// OTHER ////

# define TOKENSIZE 1024
#endif