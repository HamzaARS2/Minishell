/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:49:02 by helarras          #+#    #+#             */
/*   Updated: 2024/10/01 15:43:13 by ajbari           ###   ########.fr       */
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

void mshell_parse(t_mshell *mshell, char *line)
{
    mshell->lexer = init_lexer(line);
    lxr_generate_tokens(mshell->lexer);
    mshell->handler = init_handler(mshell->lexer);
    if (!hdl_run_quotes_check(mshell->handler))
        return;
    if (!hdl_run_poa_check(mshell->handler))
        return;
    if (!hdl_run_redirects_check(mshell->handler))
        return;
    mshell->resolver = init_resolver(mshell->lexer, mshell->envlst);
    rslv_expand(mshell->resolver);
    rslv_optimize(mshell->resolver);
    mshell->parser = init_parser(mshell->lexer->tokens);
    mshell->ast = prsr_parse(mshell->parser);
}

void mshell_execute(t_mshell *mshell)
{
    init_executor(&mshell->executor);

    // TODO: execute the whole AST.
    exec(mshell->ast, &(mshell->executor));

    //* HAMZA'S PREVIOUS PROTOTYPE
    /*     t_executor executor;

        init_executor(&executor, mshell->ast, NULL);
        execute_ast(&executor); */
}

// FREE PIDS();