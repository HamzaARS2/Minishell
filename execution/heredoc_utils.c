/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:36:22 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 17:39:15 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"

void	uhrdoc_clear(t_lexer *lexer, t_resolver *resolver, char *line)
{
	t_token	*current;
	t_token	*temp;

	current = lexer->tokens;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}
	free(lexer);
	lexer = NULL;
	free(resolver);
	resolver = NULL;
	free(line);
	line = NULL;
}

bool	uhrdoc_env_exist(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '_'
				|| line[i + 1] == '?'))
			return (true);
		i++;
	}
	return (false);
}

uint32_t	uhrdoc_get_size(t_token *tokens)
{
	t_token		*current;
	uint32_t	size;

	size = 0;
	current = tokens;
	while (current)
	{
		size += ft_strlen(current->value);
		current = current->next;
	}
	return (size);
}

char	*uhrdoc_join_tokens(t_token *tokens, uint32_t size)
{
	uint32_t	i;
	uint32_t	k;
	t_token		*current;
	char		*newline;

	i = 0;
	current = tokens;
	newline = malloc((size + 1) * sizeof(char));
	if (!newline)
		return (NULL);
	while (current)
	{
		k = 0;
		while (current->value && current->value[k])
			newline[i++] = current->value[k++];
		current = current->next;
	}
	newline[i] = 0;
	return (newline);
}

void	uhrdoc_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}
