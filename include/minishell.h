#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>
#include "token.h"
#include "lexer.h"
#include "handler.h"
#include "resolver.h"
#include "ast.h"
#include "parser.h"
#include "execution.h"
#include "envlst.h"

typedef struct s_mshell {
    t_envlst        *envlst;
    t_ast           *ast;
    t_lexer         *lexer;
    t_handler       *handler;
    t_resolver      *resolver;
    t_parser        *parser;
    t_executor      executor;
    int             ex_status;
} t_mshell;

void    init_mshell(t_mshell *mshell, char **env);

bool    mshell_parse(t_mshell *mshell, char *line);

void    mshell_execute(t_mshell *mshell);


void    display_prompt(t_mshell *mshell);




#endif