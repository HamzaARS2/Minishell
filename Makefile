CC := cc
#CFLAGS := -Wall -Wextra -Werror

UTILS = lexer/lexer_utils.c lexer/token_utils.c utils/ft_strlen.c utils/substr.c utils/ft_isalpha.c
MAIN_FILES = minishell.c strsplit.c lexer/lexer.c lexer/token.c $(UTILS)
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
