/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:53 by helarras          #+#    #+#             */
/*   Updated: 2024/10/12 15:53:52 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVER_H
# define RESOLVER_H

#include "token.h"
#include "lexer.h"

typedef struct s_envlst {
    char            *key;
    char            *value;
    struct s_envlst *next;
    struct s_envlst *prev;
} t_envlst;

typedef struct s_resolver {
    t_token **tokens;
    uint32_t size;
    t_envlst *envlst;
    t_token *current;
    t_token *next;
} t_resolver;

// initialize resolver.
t_resolver  *init_resolver(t_lexer *lexer, t_envlst *envlst);

// advances to the next token.
void    rslv_advance(t_resolver *resolver);

// expand variable tokens.
void    rslv_expand(t_resolver *resolver, bool hd_skip);

// merge tokens.
void    rslv_optimize(t_resolver *resolver);

// utils
bool    urslv_should_merge(t_resolver *resolver);
bool    urslv_should_expand(t_resolver *resolver, bool hd_skip);
void    urslv_reset(t_resolver *resolver);
void    urslv_expand_variable(t_resolver *resolver);
void    urslv_remove_spaces(t_resolver *resolver);
bool    is_special_token(t_token *token);
void    urslv_skip_heredoc_limiter(t_resolver *resolver);
void    urslv_handle_expanding(t_resolver *resolver, char *value);
void    urslv_expand_exstatus(t_resolver *resolver);



#endif