/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:27:02 by helarras          #+#    #+#             */
/*   Updated: 2024/08/22 19:46:36 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool    ulex_extract_command(t_lexer *lexer, t_token **token)
{
    unsigned int    start;
    unsigned int    size;
    char            *command;

    start = lexer->i;
    while (lexer->c && ft_isalpha(lexer->c))
        lexer_advance(lexer);
    size = lexer->i - start;
    if (size == 0)
        return (false);
    command = substr(lexer->content, start, lexer->i);
    if (!command)
        return (false);
    *token = create_token(command, COMMAND);
    if (!(*token))
    {
        free(command);
        return (false);
    }
    return (true);
}
