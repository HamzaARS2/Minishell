/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:04:26 by ajbari            #+#    #+#             */
/*   Updated: 2024/10/17 08:04:27 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "utils.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>

typedef enum s_type
{
	WORD = 30,
	PIPE,
	SSPACE,
	IN_RED,
	OUT_RED,
	APPEND,
	HERE_DOC,
	DQUOTES,
	SQUOTES,
	VARIABLE,
	SPLIT_VAR,
	STATUS
}					t_type;

typedef enum s_state
{
	DEFAULT,
	IN_DQUOTES,
	IN_SQUOTES
}					t_state;

typedef struct s_token
{
	uint32_t		id;
	char			*value;
	t_type			type;
	t_state			state;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

// create token.
t_token				*tkn_create_token(char *value, t_type type);
// add token to the list.
void				tkn_add_token(t_token **token_lst, t_token *new_token);
// extract part of DQUOTES from a token.
t_token				*tkn_extract(t_type type, char *str, uint32_t start,
						uint32_t end);

// utils
void				add_last_token(t_token *token_list, t_token *token_node);
t_token				*get_last_token(t_token *token_list);
bool				is_special_token(t_token *token);
void				free_token(t_token *token);

#endif