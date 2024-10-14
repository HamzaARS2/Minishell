/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:36:00 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/14 11:36:40 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"

void	display_error(char *intro, char *body, char *conclusion)
{
	ft_putstr_fd(intro, 2);
	ft_putstr_fd(body, 2);
	ft_putstr_fd(conclusion, 2);
}
