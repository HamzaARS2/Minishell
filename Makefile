CC := cc
#CFLAGS := -Wall -Wextra -Werror

UTILS = lexer/lexer_extract.c lexer/lexer_extract_extra.c lexer/token_utils.c utils/ft_strlen.c utils/substr.c utils/ft_isalnum.c \
utils/is_shell_special.c

MAIN_FILES = minishell.c lexer/lexer.c lexer/token.c $(UTILS)
MAIN_OBJS = $(MAIN_FILES:.c=.o)

NAME := minishell

all: $(NAME)

$(NAME): $(MAIN_OBJS)
	$(CC) $(MAIN_OBJS) -lreadline -o $(NAME)

clean:
	rm -rf $(MAIN_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
