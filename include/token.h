#ifndef TOKEN_H
# define TOKEN_H

#include <stdint.h>

typedef enum s_type {
    WORD = 30,
    OPTION = 31,
    SSPACE = 32,
    PIPE = 33,
    IN_RED = 34,
    OUT_RED = 35,
    HERE_DOC = 36,
    APPEND = 37,
    DQUOTES = 38,
    SQUOTES = 39,
    VARIABLE = 40,
    OR = 41,
    AND = 42,
    ERROR = 101

} t_type;

typedef enum s_state {
    DEFAULT,
    IN_DQUOTES,
    IN_SQUOTES
} t_state;

typedef struct s_token {
    char    *value;
    t_type  type;
    t_state state;
    struct s_token *next;
} t_token;


// utils
void    add_last_token(t_token *token_list, t_token *token_node);
t_token *get_last_token(t_token *token_list);


// create token.
t_token *tkn_create_token(char *content, t_type type);
// add token to the list.
void    tkn_add_token(t_token **token_lst, t_token *new_token);
// extract part of DQUOTES from a token.
t_token *tkn_extract(t_type type, char *str, uint32_t start, uint32_t end);

#endif