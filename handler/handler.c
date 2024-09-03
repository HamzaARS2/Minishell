/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:03:49 by helarras          #+#    #+#             */
/*   Updated: 2024/09/03 11:49:04 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handler.h"

t_handler *init_handler(t_lexer *lexer, on_error_cb callback)
{
    t_handler *handler;

    handler = malloc(sizeof(t_handler));
    if (!handler)
        return (NULL);
    handler->lexer = lexer;
    handler->error = NO_ERROR;
    handler->callback = callback;
    return (handler);
}

void    hdl_print_error(t_handler *handler)
{
    if (handler->error == NO_ERROR)
        return ;
    printf("minishell: SYNTAX_ERROR\n");
}

void    hdl_post_error(t_handler *handler, t_error error)
{
    handler->error = error;
    handler->callback(handler);
}

bool    hdl_run_quotes_check(t_handler *handler)
{
    if (handler->lexer->state == DEFAULT)
        return (true);
    hdl_post_error(handler, SYNTAX_ERROR);
    return (false);
}
