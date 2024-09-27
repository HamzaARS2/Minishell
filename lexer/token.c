/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:16:34 by helarras          #+#    #+#             */
/*   Updated: 2024/09/24 15:25:08 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/token.h"

t_token *tkn_create_token(char *value, t_type type)
{
    t_token *token;
    static  uint32_t id;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->id = ++id;
    token->value = value;
    token->type = type;
    token->state = DEFAULT;
    token->prev = NULL;
    token->next = NULL;
    return (token);
}

void    tkn_add_token(t_token **token_lst, t_token *new_token)
{
    if (!(*token_lst))
        *token_lst = new_token;
    else 
        add_last_token(*token_lst, new_token);
}

t_token *tkn_extract(t_type type, char *str, uint32_t start, uint32_t end)
{
    t_token *token;
    char    *word;

    word = substr(str, start, end);
    if (!word)
        return (NULL);
    token = tkn_create_token(word, type);
    if (!token)
    {
        free(word);
        return (NULL);
    }
    return (token);
}

