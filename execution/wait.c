#include "../include/execution.h"

t_pids  *create_node(pid_t pid)
{
    t_pids  *pids;

    pids = malloc(sizeof(t_pids));
    if (!pids)
        return (NULL);
    pids->pid = pid;
    pids->next = NULL;
    return (pids);
}
void    last_node(t_pids **current)
{
    while ((*current)->next)
        *current = (*current)->next;
}
void print_pids(t_pids *pids, int flag)
{
    t_pids *current = pids;

    printf("%d : ", flag);
    printf("pids:");
    while (current)
    {
        printf(" %d ", current->pid);
        current = current->next;
    }
    printf("\n");
}
void    add_pid(t_pids **pids, pid_t pid)
{
    t_pids  *current;
    t_pids  *new_node;

    current = *pids;

    new_node = create_node(pid);
    if (current)
    {
        last_node(&current);
        current->next = new_node;
    }
    else 
        *pids = new_node;        
}

void    ft_wait(t_executor *executor)
{
    t_pids  *current;
    t_pids  *next_node;

    current = executor->pids;
    while (current)
    {
        if (current->pid < 0)
            *executor->ex_status = 1;
        else 
        {
            waitpid(current->pid, executor->ex_status, 0);
            *executor->ex_status = WEXITSTATUS(*executor->ex_status);
        }
        current = current->next;
    }
    current = executor->pids;
    while (current)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}



