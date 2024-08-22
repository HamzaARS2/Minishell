/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:53:57 by helarras          #+#    #+#             */
/*   Updated: 2024/08/22 18:59:30 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool    ft_isalpha(char c)
{
    return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}