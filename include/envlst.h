/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:37:43 by helarras          #+#    #+#             */
/*   Updated: 2024/10/15 10:30:54 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVLST_H
# define ENVLST_H

# include "resolver.h"

t_envlst	*init_envlst(char **env);
char		*get_env_value(t_envlst *envlst, char *value);
t_envlst	*create_envlst(char *content);
void		add_envlst(t_envlst **envlst_list, t_envlst *envlst);
char		**get_env(t_envlst *envlst);
void		print_env(t_envlst *envlst, int outfd, bool flag);
#endif