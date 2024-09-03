/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:00 by helarras          #+#    #+#             */
/*   Updated: 2024/09/03 15:37:00 by helarras         ###   ########.fr       */
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

bool    hdl_run_special_check(t_handler *handler)
{
    t_token *current;

    current = handler->lexer->tokens;
    while (current)
    {
        if (uhdl_is_poa(current))
        {
            if (!uhdl_search_forward(current) || !uhdl_search_back(current))
            {
                hdl_post_error(handler, SYNTAX_ERROR);
                return (false);
            }
        }
        else if (uhdl_is_redirct(current) || uhdl_is_double_redirect(current))
        {
            if (!uhdl_search_forward(current))
            {
                hdl_post_error(handler, SYNTAX_ERROR);
                return (false);
            }
        }
        current = current->next;
    }
    return (true);
}
