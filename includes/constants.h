#ifndef CONSTANTS_H
# define CONSTANTS_H

//// PROMPT ////

# define PROMPT "\033[0;36m\033[1mMinishell> \033[0;m"
# define RUNNING 1
# define EXIT 0

//// STATES ////

# define BASIC 0
# define D_QUOTE 1
# define S_QUOTE 2
# define EXTENDING 3
# define D_STRING 4
# define S_STRING 5
# define F_STRING 6

//// TOKEN_TYPES ////

# define TOK_REDIR 0
# define TOK_PIPE 1
# define TOK_VAR 2
# define TOK_QUOTE 3
# define TOK_SIMP 4

//// OTHER ////

# define TRUE 1
# define FALSE -1
# define TOKENSIZE 1024
# define END_CHARS " $\"\0\'"
# define REDIRS_CHARS "<>|"
# define REDIRS_STRINGS (const char **){"<", ">", "|", "<<", ">>"}
#endif