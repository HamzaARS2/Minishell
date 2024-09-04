/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:59:26 by helarras          #+#    #+#             */
/*   Updated: 2024/09/04 12:03:31 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

#include "minishell.h"

typedef struct s_handler t_handler;
typedef void (*on_error_cb) (t_handler *);
typedef bool (*validation) (t_token *);

typedef enum e_error {
    NO_ERROR,
    SYNTAX_ERROR
} t_error;

typedef struct s_handler {
    t_lexer *lexer;
    t_error error;
    on_error_cb callback;
} t_handler;


// initialize the error handler.
t_handler   *init_handler(t_lexer *lexer, on_error_cb callback);

// prints the posted error.
void    hdl_print_error(t_handler *handler);

// post error.
void    hdl_post_error(t_handler *handler, t_error error);

// search for next valid arg.
bool    hdl_search_forward(t_token *token, validation is_valid_token);

// search for previous valid arg.
bool    hdl_search_back(t_token *token, validation is_valid_token);

// runs quotes error checker.
bool    hdl_run_quotes_check(t_handler *handler);

// runs pipe/or/and error checker.
bool    hdl_run_poa_check(t_handler *handler);

// runs single/double redirects error checker.
bool    hdl_run_redirects_check(t_handler *handler);

// utils.
bool    uhdl_is_poa(t_token *token);
bool    uhdl_is_redirct(t_token *token);
bool    uhdl_is_double_redirect(t_token *token);
bool    uhdl_poa_validation(t_token *token);
bool    uhdl_redirects_validation(t_token *token);





#endif