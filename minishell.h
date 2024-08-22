#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer/lexer.h"

typedef void (*string_cb) (char *);


char    *strsplit(char *str, char *charset, bool reset);

// utils
unsigned int    ft_strlen(char *str);
char    *substr(char *str, int start, int end);
bool    ft_isalpha(char c);

#endif