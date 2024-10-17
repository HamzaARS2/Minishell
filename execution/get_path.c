/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:33:20 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:35:05 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

char	*is_path(t_envlst *env)
{
	if (ft_strcmp(env->key, "PATH"))
		return (NULL);
	return (env->value + 1);
}

char	*get_path(t_envlst *envlst)
{
	t_envlst	*current;
	char		*path;

	current = envlst;
	while (current)
	{
		path = is_path(current);
		if (path)
			return (path);
		current = current->next;
	}
	return (NULL);
}

char	**get_paths(t_envlst *envlst)
{
	char	*path;
	char	**dirs;

	path = get_path(envlst);
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (dirs == NULL)
	{
		fprintf(stderr, "Error: Failed to split path.\n");
		return (NULL);
	}
	return (dirs);
}
