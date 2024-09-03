#ifndef TOKEN_H
# define TOKEN_H

#include <stdint.h>

typedef enum s_type {
    WORD = 30,
    PIPE = 31,
    SSPACE = 32,
    IN_RED = 33,
    OUT_RED = 34,
    HERE_DOC = 35,
    APPEND = 36,
    DQUOTES = 37,
    SQUOTES = 38,
    VARIABLE = 39,
    OR = 40,
    AND = 41,
    ERROR = 101

} t_type;

typedef enum s_state {
    DEFAULT,
    IN_DQUOTES,
    IN_SQUOTES
} t_state;

typedef struct s_token {
    uint32_t        id;
    char            *value;
    t_type          type;
    t_state         state;
    struct s_token  *prev;
    struct s_token  *next;
} t_token;


// utils
void    add_last_token(t_token *token_list, t_token *token_node);
t_token *get_last_token(t_token *token_list);


// create token.
t_token *tkn_create_token(char *value, t_type type);
// add token to the list.
void    tkn_add_token(t_token **token_lst, t_token *new_token);
// extract part of DQUOTES from a token.
t_token *tkn_extract(t_type type, char *str, uint32_t start, uint32_t end);

#endif