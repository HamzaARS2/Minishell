#ifndef PARSER_H
# define PARSER_H

typedef enum s_type {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    
} t_type;

typedef struct s_token {
    char    *content;
} t_token;



#endif