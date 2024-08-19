CC := cc
#CFLAGS := -Wall -Wextra -Werror

MAIN_FILES = minishell.c

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
