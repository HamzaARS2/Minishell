/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:54:58 by helarras          #+#    #+#             */
/*   Updated: 2024/09/15 14:10:16 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

uint32_t    uprsr_count_cmd(t_token *token)
{
    uint32_t count;
    t_token *current;
    
    count = 0;
    current = token;
    while (current)
    {
        if (current->type != WORD && current->type != VARIABLE)
            break ;
        count++;
        current = current->next;
    }
    return (count);
}
