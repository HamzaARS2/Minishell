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
#include "ast.h"

typedef void (*string_cb) (char *);


// utils
unsigned int    ft_strlen(char *str);
char    *substr(char *str, int start, int end);
bool    ft_isalnum(char c);
bool    is_shell_special(char c);

#endif