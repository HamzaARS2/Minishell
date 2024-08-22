#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_type {
    COMMAND,
    OPTION,
    PIPE
} t_type;

typedef struct s_token {
    char    *content;
    t_type  type;
    struct s_token *next;
} t_token;


// utils
void    add_last_token(t_token *token_list, t_token *token_node);
t_token *get_last_token(t_token *token_list);


// token
t_token *create_token(char *content, t_type type);
void    add_token(t_token **token_lst, t_token *new_token);

#endif