/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:37:43 by helarras          #+#    #+#             */
/*   Updated: 2024/10/09 12:38:25 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVLST_H
# define ENVLST_H

#include "resolver.h"

t_envlst    *init_envlst(char **env);
char        *get_env_value(t_envlst *envlst, char *variable);
t_envlst    *create_envlst(char *content);
void    add_envlst(t_envlst **envlst_list, t_envlst *envlst);

#endif