/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:23 by helarras          #+#    #+#             */
/*   Updated: 2024/10/16 08:38:09 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
#include "../include/builtins.h"

bool    exec_builtin(t_executor *executor, t_ast *node, t_builtins_type type)
{
    if (type == CD)
        return (mshell_cd(node->args, *executor->envlst));
    else if (type == EXPORT)
        return (mshell_export(executor, node));
    else if (type == ENV)
        return (mshell_env(executor));
    else if (type == EXIT)
        return(mshell_exit(executor, node->args));
    else if (type == UNSET)
        return(mshell_unset(executor->envlst, node));
    else if (type == PWD)
        return(mshell_pwd(executor));
    else if (type == ECHO)
        return(mshell_echo(*executor, node->args));
    return (false);
}