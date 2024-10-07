CC := cc
#CFLAGS := -Wall -Wextra -Werror

UTILS = lexer/lexer_extract.c lexer/lexer_extract_extra.c lexer/token_utils.c utils/ft_strlen.c utils/substr.c utils/ft_isalnum.c \
utils/is_shell_special.c utils/strcombine.c utils/ft_strncmp.c utils/ft_strdup.c resolver/resolver_utils.c \
resolver/resolver_utils_extra.c handler/handler_utils.c parser/parser_utils.c parser/ast_utils.c \
utils/ft_split.c


MAIN_FILES = minishell.c lexer/lexer.c lexer/token.c resolver/resolver.c handler/handler.c handler/checker.c \
parser/parser.c parser/procedures.c parser/procedures_extra.c parser/ast.c envlst.c shell_control.c \
execution/execution.c execution/wait.c execution/redirection.c execution/heredoc.c execution/heredoc_utils.c \
execution/get_path.c execution/cmd_expand.c execution/execution_utils.c \
$(UTILS)

MAIN_OBJS = $(MAIN_FILES:.c=.o)

NAME := minishell

ADS := -fsanitize=address -g

all: $(NAME) clean

$(NAME): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -lreadline -o $(NAME) $(ADS)

clean:
	rm -rf $(MAIN_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all 
