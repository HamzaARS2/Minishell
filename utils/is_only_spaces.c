/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:27:18 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 16:28:14 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

bool	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (str[i++] != 32)
			return (false);
	return (true);
}
