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
void print_type_name(t_type type) {
    switch (type) {
        case WORD:
            printf("WORD\n");
            break;
        case OPTION:
            printf("OPTION\n");
            break;
        case SPACE:
            printf("SPACE\n");
            break;
        case PIPE:
            printf("PIPE\n");
            break;
        case IN_RED:
            printf("IN_RED\n");
            break;
        case OUT_RED:
            printf("OUT_RED\n");
            break;
        case HERE_DOC:
            printf("HERE_DOC\n");
            break;
        case APPENED:
            printf("APPENED\n");
            break;
        case DQUOTES:
            printf("DQUOTES\n");
            break;
        case SQUOTES:
            printf("SQUOTES\n");
            break;
        case VARIABLE:
            printf("VARIABLE\n");
            break;
        case OR:
            printf("OR\n");
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

void    print_tokens(t_token *tokens) {
    t_token *current;

    current = tokens;
    while (current) {
        printf("Result: command = {%s}                || type = ", current->value);
        print_type_name(current->type);
        current = current->next;
    }
}
void    on_new_line(char *line)
{
    t_lexer *lexer = init_lexer(line);
    t_token *token;
    while (true) {
        token = lxr_tokenize(lexer);
        if (token) {
            lxr_insert_token(lexer, token);
        }
        else
            break;
    }
    print_tokens(lexer->tokens);
}

void    on_destroy() {
    system("leaks -q minishell");
}

int main(int ac, char **av, char **env) {
    // atexit(on_destroy);
    display_prompt(on_new_line);
   
}
