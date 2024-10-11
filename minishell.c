#include "include/minishell.h"


// Function to convert AST type to string (for printing purposes)
const char *get_ast_type_string(t_ast_type type) {
    switch (type) {
        case AST_COMMAND: return "COMMAND";
        case AST_PIPE: return "PIPE";
        case AST_IN_RED: return "REDIRECTION IN";
        case AST_OUT_RED: return "REDIRECTION OUT";
        case AST_APPEND: return "REDIRECTION APPEND";
        case AST_HEREDOC: return "HEREDOC";
        case AST_INQ_HEREDOC: return "INQ_HEREDOC";
        default: return "UNKNOWN";
    }
}
void print_redirect_list(t_redirect *head, int depth) {
    t_redirect *current = head;

    while (current != NULL) {
        for (int i = 0; i < depth; i++) printf("  ");
        printf(" | Type: ");
        switch (current->type) {
            case AST_IN_RED:
                printf("Input  (<) |");
                break;
            case AST_OUT_RED:
                printf("Output  (>) |");
                break;
            case AST_APPEND:
                printf("Append  (>>) |");
                break;
            case AST_HEREDOC:
                printf("Heredoc  (<<) |");
                break;
            case AST_INQ_HEREDOC:
                printf("Inq Heredoc  (<<) |");
                break;
            default:
                printf("Unknown  |");
        }
        printf("  file: %s  |\n", current->content);
        current = current->next;
    }
}
// Function to print an AST node
void print_ast(t_ast *node, int depth) {
    if (node == NULL) {
        return;
    }

    // Print indentation based on the depth in the tree
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }

    // Print the type of the node
    printf("Node Type: %s\n", get_ast_type_string(node->type));

    // Print the command if it's a command node
    if (node->args != NULL) {
        for (int i = 0; node->args[i] != NULL; i++) {
            for (int j = 0; j < depth; j++) {
                printf("  ");
            }
            printf("Command: %s\n", node->args[i]);
        }
    }

    print_redirect_list(node->redirect, depth);

    // Recursively print the left and right subtrees
    if (node->left != NULL) {
        print_ast(node->left, depth + 1);
    }
    if (node->right != NULL) {
        print_ast(node->right, depth + 1);
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
        case SPLIT_VAR:
            printf("SPLIT_VAR\n");
            break;
        case STATUS:
            printf("STATUS\n");
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
void    on_new_line(t_mshell *mshell, char *line)
{
    if (!mshell_parse(mshell, line))
        return ;
    print_tokens(mshell->lexer->tokens);
    print_ast(mshell->ast, 10);
    // mshell_execute(mshell);
}
void    display_prompt(t_mshell *mshell)
{
    char    *line;

    while (true)
    {
        line = readline("minishell > ");
        if (line)
        {
            add_history(line);
            on_new_line(mshell, line);
        }
        else
            break;
    }
}

void    on_destroy() {
    system("leaks -q minishell");
}

int main(int ac, char **av, char **env) {
    t_mshell mshell;
    // atexit(on_destroy);

    init_mshell(&mshell, env);
    display_prompt(&mshell);

}
