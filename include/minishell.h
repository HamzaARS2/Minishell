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
#include "handler.h"

typedef void (*newline_cb) (char *, char **);


// utils
unsigned int    ft_strlen(char *str);
char            *substr(char *str, int start, int end);
bool            ft_isalnum(char c);
bool            is_shell_special(char c);
char	        *strcombine(char *s1, char *s2);
int             ft_strncmp(const char *s1, const char *s2, size_t n);
char	        *ft_strdup(char *s1);
bool            is_special_token(t_token *token);
void            urslv_skip_heredoc_limiter(t_resolver *resolver);


#endif