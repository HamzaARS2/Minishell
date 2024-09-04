/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:00 by helarras          #+#    #+#             */
/*   Updated: 2024/09/04 12:01:14 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handler.h"

bool    hdl_run_quotes_check(t_handler *handler)
{
    if (handler->lexer->state == DEFAULT)
        return (true);
    hdl_post_error(handler, SYNTAX_ERROR);
    return (false);
}

bool    hdl_run_poa_check(t_handler *handler)
{
    t_token *current;

    current = handler->lexer->tokens;
    while (current)
    {
        if (uhdl_is_poa(current))
        {
            if (!hdl_search_forward(current, uhdl_poa_validation) 
                || !hdl_search_back(current, uhdl_poa_validation))
                {
                    hdl_post_error(handler, SYNTAX_ERROR);
                    return (false);
                }
        }
        current = current->next;
    }
    return (true);
}

bool    hdl_run_redirects_check(t_handler *handler)
{
    t_token *current;

    current = handler->lexer->tokens;
    while (current)
    {
        if (uhdl_is_redirct(current) || uhdl_is_double_redirect(current))
        {
            if (!hdl_search_forward(current, uhdl_redirects_validation))
            {
                hdl_post_error(handler, SYNTAX_ERROR);
                return (false);
            }
        }
        current = current->next;
    }
    return (true);
}
