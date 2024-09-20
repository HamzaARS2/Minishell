/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:54:58 by helarras          #+#    #+#             */
/*   Updated: 2024/09/20 10:59:22 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_token *uprsr_next_arg(t_token *token)
{
    t_token *current;

    current = token;
    while (current)
    {
        if (current->type == WORD || current->type == VARIABLE || current->state != DEFAULT)
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

uint32_t    uprsr_count_cmd(t_token *token)
{
    uint32_t count;
    t_token *current;
    
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
    printf("count: %i\n", count);
    return (count);
}
