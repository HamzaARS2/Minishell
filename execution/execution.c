/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajbari <ajbari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:56:59 by ajbari            #+#    #+#             */
/*   Updated: 2024/09/27 18:09:18 by ajbari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execution.h"
void    add_pid(t_executor *executor, pid_t pid)
{
    
    t_pids  *head;

    t_pids  *new_node;

    head = executor->pids;
    
    new_node->pid = pid;
    printf("test\n");

    while (head)
        head = head->next;

    head = new_node;
    new_node->next = NULL;
}
void    exec_cmd(t_ast *node, t_executor *executor)
{
    pid_t   pid;

    pid = fork();
    if (pid != 0)
    {
        add_pid(executor, pid);
        exit(0);
    }
        
    //**TO DO: better protection for the execve (access());
    //
    int retur = execve(node->args[0], node->args, NULL);
    printf("return = %d\n",retur);
    exit(1);

    
}
void    exec_pipe(t_ast *ast, t_executor *executor)
{
    //assigning left 
    //assigning right
    t_ast   *left;
    t_ast   *right;

    int p[2];


    left = ast->left;
    right = ast->right;
    
    //pipe()
    pipe(p);
    
    //asign in CONTEXT      

    //close the unneeded pipes
    //execute LEFT  by calling EXEC_TREE()
    //execute RIGHT by calling EXEC_TREE()
    //


}


void    exec_tree(t_ast *ast, t_executor *executor)
{
    if (ast->type == AST_COMMAND)
        exec_cmd(ast, executor);
    if (ast->type == AST_PIPE)
        exec_pipe(ast, executor);

}
void    init_executor(t_executor *executor)
{
    executor->context.fd[0] = STDIN_FILENO;
    executor->context.fd[1] = STDOUT_FILENO;
    executor->context.close_fd = -1;
    executor->pids = NULL;

}
void    exec(t_ast *ast)
{
    t_executor  executor;

    init_executor(&executor);
    printf("fd[0]: %d\n fd[1]: %d\n", executor.context.fd[0], executor.context.fd[1]);
    
    exec_tree(ast, &executor);
    printf("exit status: %d \n", executor.status);

}