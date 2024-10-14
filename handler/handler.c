/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:03:49 by helarras          #+#    #+#             */
/*   Updated: 2024/10/14 09:39:31 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handler.h"

t_handler *init_handler(t_lexer *lexer, int *ex_status)
{
    t_handler *handler;

    handler = malloc(sizeof(t_handler));
    if (!handler)
        return (NULL);
    handler->lexer = lexer;
    handler->error = NO_ERROR;
    handler->ex_status = ex_status;
    return (handler);
}

void    hdl_print_error(t_handler *handler)
{
    if (handler->error == NO_ERROR)
        return ;
    ft_putstr_fd("minishell: syntax error\n", 2);
}

void    hdl_post_error(t_handler *handler, t_error error)
{
    handler->error = error;
    *handler->ex_status = 258;
    hdl_print_error(handler);
}

bool    hdl_search_forward(t_token *token, validation validate_token)
{
    t_token *current;
    t_hdl_state state;

    current = token->next;
    while (current)
    {
        state = validate_token(current);
        if (state == VALID)
            return (true);
        else if (state == INVALID)
            return (false);
        current = current->next;
    }
    return (false);
}

bool    hdl_search_back(t_token *token, validation validate_token)
{
    t_token *current;
    t_hdl_state state;
    
    current = token->prev;
    while (current)
    {
        state = validate_token(current);
        if (state == VALID)
            return (true);
        else if (state == INVALID)
            return (false);
        current = current->prev;
    }
    return (false);
}

