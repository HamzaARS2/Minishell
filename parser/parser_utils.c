/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:54:58 by helarras          #+#    #+#             */
/*   Updated: 2024/09/09 16:55:25 by helarras         ###   ########.fr       */
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
        if (current->type != WORD)
            break ;
        count++;
        current = current->next;
    }
    return (count);
}
