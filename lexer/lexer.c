#include "../include/minishell.h"

t_lexer *init_lexer(char *content)
{
    t_lexer *lexer;

    if (!content)
        return (NULL);
    lexer = malloc(sizeof(t_lexer));
    if (!lexer)
        return (NULL);
    lexer->content = content;
    lexer->size = ft_strlen(content);
    lexer->i = 0;
    lexer->c = content[0];
    return (lexer);
}

void    lxr_advance(t_lexer *lexer)
{
    if (lexer->i >= lexer->size)
        return ;
    lexer->i++;
    lexer->c = lexer->content[lexer->i];
}

t_token *lxr_tokenize(t_lexer *lexer)
{
    t_token *token;

    token = 0;
    while (lexer->c && lexer->i < lexer->size)
    {
        if (ulxr_extract_space(lexer, &token))
            return (token);
        if (ulxr_extract_word(lexer, &token))
            return (token);
        if (ulxr_extract_option(lexer, &token))
            return (token);
        if (ulxr_extract_pipe(lexer, &token))
            return (token);
        if (ulxr_extract_inred(lexer, &token))
            return (token);
        if (ulxr_extract_outred(lexer, &token))
            return (token);
        if (ulxr_extract_dquotes(lexer, &token))
            return (token);
        if (ulxr_extract_variable(lexer, &token))
            return (token);
        if (ulxr_extract_squotes(lexer, &token))
            return (token);
    }
    return (token);
}

void    lxr_generate_tokens(t_lexer *lexer)
{
    t_token *token;
    t_state state;

    state = DEFAULT;
    if (!lexer)
        return ;
    while (true)
    {
        token = lxr_tokenize(lexer);
        tkn_add_token(&lexer->tokens, token);
    }
}

void    lxr_set_states(t_lexer *lexer)
{
    t_token *current;
    t_state state;

    state = DEFAULT;
    current = lexer->tokens;
    while (current)
    {
        current->state = state;
        if (state == DEFAULT && current->type == DQUOTES)
            state = IN_DQUOTES;
        else if (state == IN_DQUOTES && current->type == DQUOTES)
            state = DEFAULT;
        current = current->next;
    }
}

//ls -la | echo "hello world" > out.txt