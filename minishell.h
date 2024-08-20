#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser/token.h"

typedef void (*string_cb) (char *);


char    *strsplit(char *str, char *charset, bool reset);

#endif