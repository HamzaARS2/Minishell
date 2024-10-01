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
    // print_pids(*pids,  1);
        
}

void    ft_wait(t_executor *executor)
{
    t_pids  *current;
    t_pids  *next_node;

    current = executor->pids;
    while (current)
    {
        printf("status in wait:%d\n",  (executor->status));
        waitpid(current->pid, &(executor->status), 0);
        executor->status = WEXITSTATUS(executor->status);
        current = current->next;
    }
    //FREE THE PIDS LIST
    current = executor->pids;
    while (current)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}



