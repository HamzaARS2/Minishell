/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:46:03 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 22:46:22 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_parser	*init_parser(t_token *tokens)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->tokens = tokens;
	parser->current = tokens;
	parser->ast = NULL;
	return (parser);
}

void	prsr_advance(t_parser *parser)
{
	if (!parser->current)
		return ;
	parser->current = parser->current->next;
}

t_ast	*prsr_parse(t_parser *parser)
{
	return (prsr_parse_pipe(parser));
}
