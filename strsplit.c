/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:07:03 by helarras          #+#    #+#             */
/*   Updated: 2024/08/20 12:01:42 by helarras         ###   ########.fr       */
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

char    *substr(char *str, int start, int end)
{
    char    *newstr;
    int     strsize;
    int     i;

    i = 0;
    strsize = end - start;
    if (strsize <= 0)
        return (NULL);
    newstr = malloc((strsize + 1) * sizeof(char));
    if (!newstr)
        return (NULL);
    while (str[start] && strsize > i)
        newstr[i++] = str[start++];
    newstr[i] = 0;
    return (newstr);
}

char    *strsplit(char *str, char *charset, bool reset)
{
    static int  offset;
    int         start;
    char        *token;
    
    if (reset)
        offset = 0;
    start = offset;
    while (str[offset] && !is_exist(charset, str[offset]))
        offset++;
    token = substr(str, start, offset);
    if (!token)
        return (NULL);
    if (str[offset])
        offset++;
    return (token);
}
