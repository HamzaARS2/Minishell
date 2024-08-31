/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:53 by helarras          #+#    #+#             */
/*   Updated: 2024/08/31 10:21:03 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVER_H
# define RESOLVER_H

#include "token.h"

typedef struct s_resolver {
    t_token *tokens;
    uint32_t size;
    char    **env;
    t_token *current;
    t_token *next;
} t_resolver;

// initialize resolver.
t_resolver  *init_resolver(t_lexer *lexer, char **env);

// merge tokens.
void    rslv_optimize(t_resolver *resolver);

// expand variable tokens.
void    rslv_expand(t_resolver *resolver);

// utils
bool    urslv_should_merge(t_resolver *resolver);
bool    urslv_should_expand(t_resolver *resolver);
void    urslv_reset(t_resolver *resolver);
void    urslv_expand_variable(t_resolver *resolver);




#endif