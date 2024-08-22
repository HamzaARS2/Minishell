/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:07:03 by helarras          #+#    #+#             */
/*   Updated: 2024/08/22 19:15:42 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool is_exist(char *haystack, char needle)
{
    int i;

    i = 0;
    while (haystack[i])
    {
        if (needle == haystack[i])
            return (true);
        i++;
    }
    return (false);
}

char    *strsplit(char *str, char *charset, bool reset)
{
    static int  offset;
    int         start;
    char        *token;
    
    if (reset)
        offset = 0;
    while (is_exist(charset, str[offset]))
        offset++;
    start = offset;
    while (str[offset] && !is_exist(charset, str[offset]))
        offset++;
    token = substr(str, start, offset);
    if (!token)
        return (NULL);
    while (is_exist(charset, str[offset]))
        offset++;
    return (token);
}
