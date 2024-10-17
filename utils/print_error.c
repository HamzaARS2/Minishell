/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:53:14 by helarras          #+#    #+#             */
/*   Updated: 2024/10/17 20:14:25 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

int	print_error(int *ex_status, int st, char *err)
{
	*ex_status = st;
	ft_putstr_fd(err, 2);
	return (-1);
}
