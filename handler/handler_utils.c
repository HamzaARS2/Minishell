/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:24:30 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 16:05:54 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/handler.h"

bool	uhdl_is_pipe(t_token *token)
{
	return (token->type == PIPE && token->state == DEFAULT);
}

bool	uhdl_is_redirct(t_token *token)
{
	return ((token->type == IN_RED || token->type == OUT_RED)
		&& (token->state == DEFAULT));
}

bool	uhdl_is_double_redirect(t_token *token)
{
	return ((token->type == HERE_DOC || token->type == APPEND)
		&& (token->state == DEFAULT));
}

t_hdl_state	uhdl_poa_validation(t_token *token)
{
	if (uhdl_is_pipe(token))
		return (INVALID);
	if (token->type == WORD || token->type == VARIABLE || token->type == STATUS
		|| token->state != DEFAULT)
		return (VALID);
	if (uhdl_is_redirct(token) || uhdl_is_double_redirect(token))
		return (VALID);
	return (CONTINUE);
}

t_hdl_state	uhdl_redirects_validation(t_token *token)
{
	if (uhdl_is_pipe(token))
		return (INVALID);
	if (uhdl_is_redirct(token) || uhdl_is_double_redirect(token))
		return (INVALID);
	if (token->type == WORD || token->type == VARIABLE
		|| token->state != DEFAULT)
		return (VALID);
	return (CONTINUE);
}
