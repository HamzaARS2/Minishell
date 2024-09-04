/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:30 by helarras          #+#    #+#             */
/*   Updated: 2024/09/04 12:01:44 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handler.h"

bool    uhdl_is_poa(t_token *token)
{
    return ((token->type == PIPE || token->type == OR || token->type == AND) 
        && (token->state == DEFAULT));
}

bool    uhdl_is_redirct(t_token *token)
{
    return ((token->type == IN_RED || token->type == OUT_RED) 
        && (token->state == DEFAULT));
}

bool    uhdl_is_double_redirect(t_token *token)
{
    return ((token->type == HERE_DOC || token->type == APPEND) 
        && (token->state == DEFAULT));
}

bool    uhdl_poa_validation(t_token *token)
{
    if (uhdl_is_poa(token))
        return (false);
    if (token->type == WORD || token->type == VARIABLE || token->state != DEFAULT)
        return (true);
    if (uhdl_is_redirct(token) || uhdl_is_double_redirect(token))
        return (true);
    return (false);
}

bool    uhdl_redirects_validation(t_token *token)
{
    if (uhdl_is_poa(token))
        return (false);
    if (token->type == WORD || token->type == VARIABLE || token->state != DEFAULT)
        return (true);
    return (false);
}

