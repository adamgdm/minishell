CFLAGS = -Wall -Wextra -Werror -I  $(HOME)/.brew/Cellar/readline/8.2.1/include
NAME = minishell
SRC =  minishell_utils.c parsing/lexer_files/lexer.c minishell.c \
		minishell_utils2.c parsing/lexer_files/utils_lexer.c parsing/lexer_files/tokens.c \
		parsing/lexer_files/expander.c parsing/lexer_files/update_tokens.c parsing/syntax_files/syntax_checker.c \
		parsing/parser_files/parser.c parsing/parser_files/commands.c \
		parsing/parser_files/utils_parser.c  parsing/parser_files/here_doc.c \
		parsing/lexer_files/expander_utils.c parsing/lexer_files/lexer_utils.c \
		parsing/lexer_files/lexer_utils2.c parsing/lexer_files/lexer_utils3.c \
		parsing/lexer_files/lexer_utils4.c Builtins/cd1.c Builtins/cd2.c \
		parsing/parser_files/parser_utils.c parsing/parser_files/parser_utils2.c \
		parsing/parser_files/parser_utils3.c Builtins/exit1.c Builtins/export.c \
		parsing/syntax_files/syntax_utils.c parsing/syntax_files/syntax_utils2.c\
		parsing/parser_files/here_doc_utils.c parsing/lexer_files/expander_utils2.c\
		exec/helpers_1.c Builtins/pwd.c Builtins/additional_fncts_1.c Builtins/export2.c\
		Builtins/cd.c Builtins/env.c Builtins/unset.c Builtins/export1.c exec/helpers_2.c \
		Builtins/exit.c Builtins/echo.c exec/helpers_3.c Builtins/export3.c exec/exec_fncts1.c \
		exec/execution.c exec/exec_fncts.c exec/exec_fncts2.c exec/exec_fncts3.c \
		exec/exec_fncts4.c exec/exec_fncts5.c exec/exec_fncts6.c addons.c addons1.c
OBJ = $(SRC:.c=.o)
LIBFT = libft.a
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ)
	$(CC) $(OBJ)  -o $(NAME) libft/libft.a -lreadline -I  $(HOME)/.brew/Cellar/readline/8.2.1/include -L $(HOME)/.brew/Cellar/readline/8.2.1/lib $(CFLAGS)
# $(CC)  $(OBJ)  -o $(NAME)  $(CFLAGS) libft/libft.a 

re: fclean all

clean:
	$(RM) $(OBJ)
	make -C libft clean

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)


