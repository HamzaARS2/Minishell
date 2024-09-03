/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:03:49 by helarras          #+#    #+#             */
/*   Updated: 2024/09/03 16:47:49 by helarras         ###   ########.fr       */
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


bool    uhdl_search_forward(t_token *token)
{
    t_token *current;

    current = token->next;
    while (current)
    {
        if (current->type != SSPACE && is_special_token(current) && current->state == DEFAULT)
            return (false);
        if (current->type == WORD || current->state != DEFAULT)
            return (true);
        current = current->next;
    }
    return (false);
}

bool    uhdl_search_back(t_token *token)
{
    t_token *current;

    current = token->prev;
    while (current)
    {
        if (current->type != SSPACE && is_special_token(current) && current->state == DEFAULT)
            return (false);
        if (current->type == WORD || current->state != DEFAULT)
            return (true);
        current = current->prev;
    }
    return (false);
}

bool    hdl_run_poa_check(t_handler *handler)
{
    t_token *current;

    current = handler->lexer->tokens;
    while (current)
    {
        if (current->type != SSPACE && is_special_token(current) && current->state == DEFAULT)
        {
            if (!uhdl_search_forward(current) || !uhdl_search_back(current))
            {
                hdl_post_error(handler, SYNTAX_ERROR);
                return (false);
            }
        }
        current = current->next;
    }
    return (true);
}
