/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:51 by helarras          #+#    #+#             */
/*   Updated: 2024/08/28 15:44:05 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_resolver  *init_resolver(t_lexer *lexer)
{
    t_resolver *resolver;

    resolver = malloc(sizeof(t_resolver));
    if (!resolver)
        return (NULL);
    resolver->tokens = lexer->tokens;
    resolver->size = lexer->size;
    resolver->current_tkn = resolver->tokens;
    resolver->current_id = resolver->current_tkn->id;
    return (resolver);
}

void    rslv_advance(t_resolver *resolver)
{
    if (!resolver->current_tkn)
        return ;
    resolver->current_tkn = resolver->current_tkn->next;
    resolver->current_id = resolver->current_tkn->id;
}

void    rslv_optimize(t_resolver *resolver)
{
    t_token *merged_tkn;
    
    merged_tkn = NULL;
    while (resolver->current_tkn)
    {
        if (rslv_merge_indq(resolver, &merged_tkn))
            return (merged_tkn);
    }
}

t_token *rslv_merge_indq(t_resolver *resolver, t_token **token)
{
    t_token *start_tkn;
    
    if (resolver->current_tkn->state != IN_DQUOTES)
        return (false);
    start_tkn = resolver->current_tkn;
    while (resolver->current_tkn && resolver->current_tkn->state == IN_DQUOTES)
        rslv_advance(resolver);
        
}

t_token *merge_next(t_token *token, t_token *next_tkn)
{
    t_token *merged_tkn;
    char    *value;
    
    if (next_tkn->type)
    value = strcombine(token->value, next_tkn->value);
    merged_tkn = tkn_create_token(value, WORD);
    return (merged_tkn);
}

// minishell > ls -la | echo hi"hello world" > out.txt
// Result: 1 command = {ls}                || state = DEFAULT || type = WORD
// Result: 2 command = { }                || state = DEFAULT || type = SSPACE
// Result: 3 command = {-la}                || state = DEFAULT || type = WORD
// Result: 4 command = { }                || state = DEFAULT || type = SSPACE
// Result: 5 command = {|}                || state = DEFAULT || type = PIPE
// Result: 6 command = { }                || state = DEFAULT || type = SSPACE
// Result: 7 command = {echo}                || state = DEFAULT || type = WORD
// Result: 8 command = { }                || state = DEFAULT || type = SSPACE
// Result: 9 command = {"}                || state = DEFAULT || type = DQUOTES
// Result: 10 command = {hello}                || state = IN_DQUOTES || type = WORD
// Result: 11 command = { }                || state = IN_DQUOTES || type = SSPACE
// Result: 12 command = {world}                || state = IN_DQUOTES || type = WORD
// Result: 13 command = {"}                || state = DEFAULT || type = DQUOTES
// Result: 14 command = { }                || state = DEFAULT || type = SSPACE
// Result: 15 command = {>}                || state = DEFAULT || type = OUT_RED
// Result: 16 command = { }                || state = DEFAULT || type = SSPACE
// Result: 17 command = {out.txt}                || state = DEFAULT || type = WORD