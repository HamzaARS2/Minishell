CC := cc
# CFLAGS := -Wall -Wextra -Werror

UTILS = lexer/lexer_extract.c lexer/lexer_extract_extra.c lexer/token_utils.c utils/ft_strlen.c utils/substr.c utils/ft_isalnum.c \
utils/is_shell_special.c utils/strcombine.c utils/ft_strncmp.c utils/ft_strdup.c resolver/resolver_utils.c \
resolver/resolver_utils_extra.c handler/handler_utils.c parser/parser_utils.c parser/ast_utils.c \
utils/ft_split.c utils/ft_strchr.c utils/ft_putstr_fd.c utils/ft_strcmp.c utils/ft_strtrim.c utils/ft_isdigit.c \
utils/ft_itoa.c utils/is_only_spaces.c

BUILTINS = builtins/builtin_check.c builtins/mshell_cd.c builtins/mshell_export.c builtins/mshell_env.c builtins/mshell_exit.c \
builtins/builtins_utils.c builtins/mshell_unset.c builtins/mshell_pwd.c builtins/mshell_echo.c \
builtins/exec_builtin.c

MAIN_FILES = minishell.c lexer/lexer.c lexer/token.c resolver/resolver.c handler/handler.c handler/checker.c \
parser/parser.c parser/procedures.c parser/procedures_extra.c parser/ast.c envlst.c envlst_utils.c shell_control.c \
execution/execution.c execution/wait.c execution/redirection.c execution/heredoc.c execution/heredoc_utils.c \
execution/get_path.c execution/cmd_expand.c execution/execution_utils.c \
$(UTILS) $(BUILTINS)

MAIN_OBJS = $(MAIN_FILES:.c=.o)

RL_PATH = -L/Users/helarras/.brew/opt/readline/lib
RL_INCLUDE = -I/Users/helarras/.brew/opt/readline/include
# Get the Readline installation path

# Set Readline flags

NAME := minishell

ADS := -fsanitize=address -g

all: $(NAME) clean

$(NAME): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) $(RL_PATH) -lreadline -o $(NAME) $(ADS)

%.o: %.c
	$(CC) $(CFLAGS) $(RL_INCLUDE) -c $< -o $@
clean:
	rm -rf $(MAIN_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all 
