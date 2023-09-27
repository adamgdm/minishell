#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"




// typedef struct s_list {
// 	t_token			*head;
// 	t_token			*tail;
// 	int				size;
// }	t_list;
enum e_state {
	GENERAL,
	IN_QUOTE,
	IN_DQUOTE,
	QUOTED
};

enum e_token{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	PIPE = '|',
	ESCAPE = '\\',
	ENV = '$',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	REDIRECT_APPEND,
	HERE_DOC
};

typedef struct s_token {
	char			*content;
	enum e_token	type;
	enum e_state	state;
	char			*before_expanded;
	int				space_check;
	struct s_token	*next;
} t_token;

typedef struct s_commands {
	int					in_file;
	int					out_file;
	char				**cmd;
	struct s_commands	*next;
} t_commands;

typedef struct s_env {
    char *str;
    struct s_env *next;
} t_env;

typedef struct s_data 
{
	t_env *env;
	t_env *envnoeq;
} t_data;

//	-----------------------    PARSING    ------------------------


t_token*	_lexer(char *input);
t_token*    _create_token(char *value, enum e_token type, enum e_state state, int check_space);
void		_add_token(t_token **head, t_token *new);
void		_update_tokens(t_token **result);
int			_it_contains(int c);
void		_expander(t_token **head);
char*		_append(char *str, char c);
int			_syntax_check(t_token** result);
t_commands  *_parser(t_token **result);
t_commands  *_create_command(char **commands, int in_file, int out_file);
void		_add_command(t_commands **head, t_commands *new);
void		_print_array(char **array);
void		_free_all_tokens(t_token **head);


//	-----------------------    PARSING    ------------------------

int ft_strcmp(const char *s1, const char *s2);

char* ft_strcpy(char* dest, const char* src);

int	ft_rulefinder(char *cmd, char *arraytofind);

char *getValue(char *input);

char *fetchValue(char *str, t_env *head);

t_env *charArrayToEnvList(char **charArray);

void appendEnvNode(t_env **head, char *str); 

t_env *createEnvNode(char *str);

void delete_last_node(t_env **head);

void deleteNode(t_env **head, char *target);

void add_last_node(t_env **head, const char *str);

void add_before_last_node(t_env **head, const char *str);

void printenv(t_env *head, int fd);

int ft_iseqin(char *str);

void    ft_echo(char **cmd, int fd);

void    ft_execute(t_data **data, t_commands *cmnd, char **envp);

int     ft_count(char **str);

char    *ft_retpwd(void);

int ft_which_line(char **envp, char *str);

char *ft_line_w_out_path(char *str, int len);

char **ft_find_path(char **envp, t_env *head);

char *ft_makethelist(char *cmd, char **path, t_env *head);

void ft_execve(char **envp, char **cmnd, t_env *head);

void    ft_exit(t_data *data, t_commands *cmnds);

void    ft_pwd(int fd);

void    ft_cd(t_data **data, char *path, char *pwd);

void    ft_env(t_env **env, int fd);

void    ft_unset(t_data **data, t_commands *cmnd);

void    ft_export(t_env **env, t_env **envnocmd, t_commands *cmnd, int fd);

int ft_doesmatch(char *str, char *qst);

void ft_initialize(t_data **x, char **env);

void free_commands(t_commands *head);

#endif
