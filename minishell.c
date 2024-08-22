#include "minishell.h"

void    display_prompt(string_cb newline)
{
    char    *line;

    while (true)
    {
        line = readline("minishell > ");
        if (line)
        {
            add_history(line);
            newline(line);
        }
        else
            break;
    }
}

void    on_new_line(char *line)
{
    
}

void    on_destroy() {
    system("leaks -q minishell");
}

int main(int ac, char **av, char **env) {
    // atexit(on_destroy);
    char *line = "ls -la | wc -l";
    t_lexer *lexer = init_lexer(line);
    t_token *token = lexer_tokenize(lexer);
    printf("Result: command = %s | type %i\n", token->content, token->type);
}