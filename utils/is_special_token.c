/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:13:06 by helarras          #+#    #+#             */
/*   Updated: 2024/09/01 08:16:59 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool    is_special_token(t_token *token)
{
    if (token->type == SSPACE || token->type == PIPE || token->type == OUT_RED
        || token->type == IN_RED || token->type == HERE_DOC || token->type == APPEND
        || token->type == OR || token->type == AND)
        return (true);
    return (false);
}