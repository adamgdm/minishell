CFLAGS = -fsanitize=address -g
NAME = minishell
SRC = parsing/lexer.c minishell.c parsing/utils_lexer.c parsing/tokens.c \
		parsing/expander.c parsing/update_tokens.c parsing/syntax_checker.c \
		parsing/parser.c parsing/commands.c exec/helpers_1.c Builtins/pwd.c \
		Builtins/cd.c Builtins/env.c Builtins/unset.c Builtins/export.c exec/helpers_2.c \
		Builtins/exit.c Builtins/echo.c exec/helpers_3.c
OBJ = $(SRC:.c=.o)
LIBFT = libft.a
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline libft/libft.a -o $(NAME)

re: fclean all

clean:
	$(RM) $(OBJ)
	make -C libft clean

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)


