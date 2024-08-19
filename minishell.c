#include "minishell.h"

void    display_prompt()
{
    char    *line;

    while (true)
    {
        line = readline("minishell > ");
        if (line)
            add_history(line);
        else
            break;
    }
}

#include <string.h>

int main(int ac, char **av, char **env) {
    char *line = strdup("ls -la | wc -c; echo \"Hello\" ");
    // display_prompt();
}