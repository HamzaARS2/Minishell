/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:49:02 by helarras          #+#    #+#             */
/*   Updated: 2024/10/07 14:49:30 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
#include "include/execution.h"

void init_mshell(t_mshell *mshell, char **env)
{
    mshell->envlst = init_envlst(env);
    mshell->ast = NULL;
    mshell->lexer = NULL;
    mshell->handler = NULL;
    mshell->resolver = NULL;
    mshell->parser = NULL;
}

bool    mshell_parse(t_mshell *mshell, char *line)
{
    mshell->lexer = init_lexer(line);
    lxr_generate_tokens(mshell->lexer);
    mshell->handler = init_handler(mshell->lexer);
    if (!hdl_run_quotes_check(mshell->handler))
        return (false);
    if (!hdl_run_pipe_check(mshell->handler))
        return (false);
    if (!hdl_run_redirects_check(mshell->handler))
        return (false);
    mshell->resolver = init_resolver(mshell->lexer, mshell->envlst);
    rslv_expand(mshell->resolver, true);
    rslv_optimize(mshell->resolver);
    mshell->parser = init_parser(mshell->lexer->tokens);
    mshell->ast = prsr_parse(mshell->parser);
    return (true);
}

void mshell_execute(t_mshell *mshell)
{
    init_executor(&mshell->executor, mshell->envlst);

    // TODO: execute the whole AST.
    // TODO: execute the whole AST.
    hrdoc_collect(mshell->ast, mshell->envlst);
    exec(mshell->ast, &(mshell->executor));
    //TODO: FREE THE PATHS;
    

    //* HAMZA'S PREVIOUS PROTOTYPE
    /*     t_executor executor;

        init_executor(&executor, mshell->ast, NULL);
        execute_ast(&executor); */
}

// FREE PIDS();