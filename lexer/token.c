/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:16:34 by helarras          #+#    #+#             */
/*   Updated: 2024/08/22 19:24:49 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

t_token *create_token(char *content, t_type type)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->content = content;
    token->type = type;
    return (token);
}

void    add_token(t_token **token_lst, t_token *new_token)
{
    if (!*token_lst)
        *token_lst = new_token;
    else
        add_last_token(*token_lst, new_token);
}