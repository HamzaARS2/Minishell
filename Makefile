CC := cc
#CFLAGS := -Wall -Wextra -Werror

UTILS = lexer/lexer_extract.c lexer/lexer_extract_extra.c lexer/token_utils.c utils/ft_strlen.c utils/substr.c utils/ft_isalnum.c \
utils/is_shell_special.c utils/strcombine.c utils/ft_strncmp.c utils/ft_strdup.c resolver/resolver_utils.c

MAIN_FILES = minishell.c lexer/lexer.c lexer/token.c resolver/resolver.c $(UTILS)
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