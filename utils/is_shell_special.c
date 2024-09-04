/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_shell_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:28:31 by helarras          #+#    #+#             */
/*   Updated: 2024/09/04 12:20:35 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool    is_shell_special(char c)
{
    if (c == 32 || c == '$' || c == '|' || c == '<' || c == '>' || c == '"'
        || c == '"' || c == '\'' || c == '\'' || c == '&')
        return (true);
    return (false);
}