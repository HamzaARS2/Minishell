/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:26:45 by helarras          #+#    #+#             */
/*   Updated: 2024/10/09 09:50:00 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
// utils
unsigned int    ft_strlen(char *str);
char            *substr(char *str, int start, int end);
bool            ft_isalnum(char c);
bool            is_shell_special(char c);
char	        *strcombine(char *s1, char *s2, bool should_free);
int             ft_strncmp(const char *s1, const char *s2, size_t n);
char	        *ft_strdup(char *s1);
char			**ft_split(char *str, char c);
char            *ft_strchr(const char *s, int c);


void	        ft_putstr_fd(char *s, int fd);


#endif

