/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:54:58 by helarras          #+#    #+#             */
/*   Updated: 2024/09/20 19:16:39 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"


t_token *uprsr_next_arg(t_token *token)
{
    t_token *current;

    current = token;
    while (current)
    {
        if (current->type == WORD || current->type == VARIABLE
            || current->type == SPLIT_VAR || current->state != DEFAULT)
            return (current);
        else if (current->type >= 33 && current->type <= 36)
        {
            current = current->next;
            if (current)
                current = current->next;
        } else
            break ;
    }
    return (NULL);
}

uint32_t    uprsr_count_args(t_token *token)
{
    t_token *current;
    uint32_t count;

    count = 0;
    current = token;
    while (current)
    {
        current = uprsr_next_arg(current);
        if (!current)
            break ;
        count++;
        current = current->next;
    }
    return (count);
}

char    **uprsr_build_cmd(t_parser *parser)
{
    uint32_t count;
    char    **cmd;
    t_token *current;
    uint32_t i;

    i = 0;
    current = parser->current;
    count = uprsr_count_args(parser->current);
    cmd = malloc ((count + 1) * sizeof(char *));
    if (!cmd)
        return (NULL);
    while (current && i < count)
    {
        current = uprsr_next_arg(current);
        if (!current)
            break ;
        cmd[i] = current->value;
        if (parser->current->type == WORD || parser->current->type == VARIABLE
            || parser->current->type == SPLIT_VAR || parser->current->state != DEFAULT)
            prsr_advance(parser);
        current = current->next;
        i++;
    }
    cmd[i] = NULL;
    return (cmd);
}
