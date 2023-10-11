CFLAGS =  -fsanitize=address -g3 
NAME = minishell
SRC = parsing/lexer.c minishell.c parsing/utils_lexer.c parsing/tokens.c \
		parsing/expander.c parsing/update_tokens.c parsing/syntax_checker.c \
		parsing/parser.c parsing/commands.c \
		parsing/utils_parser.c  parsing/here_doc.c \
		parsing/expander_utils.c parsing/lexer_utils.c \
		parsing/lexer_utils2.c parsing/lexer_utils3.c \
		parsing/lexer_utils4.c \
		parsing/parser_utils.c parsing/parser_utils2.c \
		exec/helpers_1.c Builtins/pwd.c Builtins/additional_fncts_1.c\
		Builtins/cd.c Builtins/env.c Builtins/unset.c Builtins/export1.c exec/helpers_2.c \
		Builtins/exit.c Builtins/echo.c exec/helpers_3.c \
		exec/execution.c exec/exec_fncts.c
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


