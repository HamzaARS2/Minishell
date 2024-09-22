/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:03:53 by ajbari            #+#    #+#             */
/*   Updated: 2024/09/22 19:16:46 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "../include/ast.h"

typedef struct s_exec_fds {
    int infd;
    int outfd;

} t_exec_fds;

void    exec_cmd(t_ast *node, t_exec_fds fds);


#endif