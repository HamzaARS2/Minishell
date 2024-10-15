/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:23 by helarras          #+#    #+#             */
/*   Updated: 2024/10/15 10:52:21 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/builtins.h"

bool    exec_builtin(t_executor *executor, t_ast *node, t_builtins_type type)
{
    if (type == CD)
        return (cd(node->args, *executor->envlst));
    else if (type == EXPORT)
        return (mshell_export(executor, node));
    else if (type == ENV)
        return (mshell_env(executor));
    else if (type == EXIT)
        return(mshell_exit(node->args));
    else if (type == UNSET)
        return(mshell_unset(executor->envlst, node));
    else if (type == PWD)
        return(mshell_pwd(executor));
    else if (type == ECHO)
        return(mshell_echo(node->args));
    return (false);
}