#include "include/minishell.h"

void    display_prompt(newline_cb newline, char **env)
{
    char    *line;

    while (true)
    {
        line = readline("minishell > ");
        if (line)
        {
            add_history(line);
            newline(line, env);
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
        case SSPACE:
            printf("SSPACE\n");
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
        case APPEND:
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
        case ERROR:
            printf("ERROR\n");
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

void    print_state(t_state state) {
    if (state == DEFAULT)
        printf("DEFAULT");
    else if (state == IN_DQUOTES)
        printf("IN_DQUOTES");
    else
        printf("IN_SQUOTES");
}

void    print_tokens(t_token *tokens) {
    t_token *current;

    current = tokens;
    while (current) {
        printf("Result: id = %i command = {%s}                || state = ", current->id, current->value);
        print_state(current->state);
        printf(" || type = ");
        print_type_name(current->type);
        current = current->next;
    }
}

void    on_error(t_handler *handler)
{
    hdl_print_error(handler);
    // TODO: run resources cleaner.
    rl_redisplay();
}

void    on_new_line(char *line, char **env)
{
    t_lexer *lexer = init_lexer(line);
    lxr_generate_tokens(lexer);
    t_handler *handler = init_handler(lexer, on_error);
    if (!hdl_run_quotes_check(handler))
        return ;
    t_resolver *resolver = init_resolver(lexer, env);
    print_tokens(lexer->tokens);
    rslv_expand(resolver);
    printf("\n################################## *AFTER EXPANDING* #####################################\n\n");
    print_tokens(lexer->tokens);
    rslv_optimize(resolver);
    printf("\n################################## *AFTER OPTIMIZATION* #####################################\n\n");
    print_tokens(lexer->tokens);
}

void    on_destroy() {
    system("leaks -q minishell");
}

int main(int ac, char **av, char **env) {
    atexit(on_destroy);
    display_prompt(on_new_line, env);
}
