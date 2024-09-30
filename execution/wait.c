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
void    last_node(t_pids **head)
{
    while ((*head)->next)
    {
        *head = (*head)->next;
    }
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
    t_pids  *head;
    t_pids  *new_node;

    head = *pids;

    new_node = create_node(pid);
    if (head)
    {
        last_node(&head);
        head->next = new_node;
    }
    else 
        *pids = new_node;
    print_pids(*pids,  1);
        
}



