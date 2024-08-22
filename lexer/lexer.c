#include "../minishell.h"

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

void    lexer_advance(t_lexer *lexer)
{
    if (lexer->i >= lexer->size)
        return ;
    lexer->i++;
    lexer->c = lexer->content[lexer->i];
}



t_token *lexer_tokenize(t_lexer *lexer)
{
    t_token *token;

    while (lexer->c && lexer->i < lexer->size)
    {
        if (ulex_extract_command(lexer, &token))
            return (token);
    } 
    return (token); 
}

