#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>
#include "lexer.h"
#include "parser.h"
#include "resolver.h"

typedef void (*newline_cb) (char *, char **);


// utils
unsigned int    ft_strlen(char *str);
char    *substr(char *str, int start, int end);
bool    ft_isalnum(char c);
bool    is_shell_special(char c);
char	*strcombine(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);



#endif