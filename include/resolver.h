/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:53 by helarras          #+#    #+#             */
/*   Updated: 2024/08/29 15:39:20 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOLVER_H
# define RESOLVER_H

#include "token.h"

typedef struct s_resolver {
    t_token *tokens;
    uint32_t size;
    t_token *current;
    t_token *next;
} t_resolver;

// initialize resolver.
t_resolver  *init_resolver(t_lexer *lexer);

// merge tokens and expand variables.
void    rslv_optimize(t_resolver *resolver);

// utils
bool    urslv_should_merge(t_resolver *resolver);





#endif