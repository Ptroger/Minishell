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

//// TYPES ////

# define NONE -1
# define CMD 0
# define ARG 1
# define R_IN 2
# define R_OUT 3
# define H_DOC 4
# define F_OPEN 5
# define F_EXIT 6
# define LIMITOR 7
# define PIPE 8

//// OTHER ////

# define TRUE 1
# define FALSE -1
# define FINISHED 0
# define CONTINUE 1
# define TOKENSIZE 1024
# define END_CHARS " $\"\0\'"
# define REDIRS_CHARS "<>|"

#endif