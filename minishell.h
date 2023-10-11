#ifndef MINISHELL_H
#define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "libft/libft.h"



//------------------------------------    NORMINETTE    ------------------------------------

typedef struct s_vars
{
	char	*save;
	int		i;
	int		j;
	int		k;
}	t_vars;


//------------------------------------    NORMINETTE    ------------------------------------

enum e_state {
	GENERAL,
	IN_QUOTE,
	IN_DQUOTE,
	QUOTED
};

enum					e_token
{
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

typedef struct s_token
{
	char				*content;
	enum e_token		type;
	enum e_state		state;
	char				*before_expanded;
	int					space_check;
	struct s_token		*next;
}						t_token;

typedef struct s_commands
{
	int					in_file;
	int					out_file;
	int					*pipefd;
	int					error_exist;
	int					pid;
	char				**cmd;
	struct s_commands	*next;
	struct s_commands	*previous;
}						t_commands;

typedef struct s_env
{
	char				*str;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	t_env				*env;
	t_env				*envnoeq;
	int					SHLVL;
}						t_data;

typedef struct s_execcomnand
{
	char				*command;
	char				**args;
	char				**environement;
}						t_execcommand;

typedef struct s_forchitat
{
	int					forchita;
	struct s_forchitat	*next;
}						t_forchitat;

//	-----------------------    PARSING    ------------------------


t_token*	_lexer(char *input);
t_token*    _create_token(char *value, enum e_token type, enum e_state state, int check_space);
void		_add_token(t_token **head, t_token *new);
void		_update_tokens(t_token **result);
int			_it_contains(int c);
void		_expander(t_token **head, t_data *data);
char*		_append(char *str, char c);
int			_syntax_check(t_token** result);
t_commands  *_parser(t_token **result, t_data *data);
t_commands  *_create_command(char **commands, int in_file, int out_file, int *pipefd, int error);
void		_add_command(t_commands **head, t_commands *new);
void		_print_array(char **array);
void		_free_all_tokens(t_token **head, int check);
int			_process_env_value(char *value);
int			*_here_doc(char *content, int check, t_data *data);
char		*_expand_word(char *content, t_data *data);
void		ft_sigints(int sig);
void		_join_exit_status(char **save, int *i);
void		_join_digit(char **save, char *content, t_data *data, int *i);
void		_join_dollar_with_char(char **save, char *content, int *i);
void		_join_the_word(char **save, char *content, char *tmp, t_data *data);
void   		_norminette(char **save, char *content, t_data *data, t_vars *vars);
void		_token_creation(char *input, t_token **head, int *i);


//	-----------------------    PARSING    ------------------------

void					ft_exportpwdoldpwd(t_data **data, char *pwd);
void					ft_freearr(char **arr);
void					ft_freecmd(t_commands *cmd);
t_commands				*ft_createcommand(char **str);
char					*ft_returnpwd(t_data **data);
char					*ft_returnrule(t_env *env, char *rts);

//	-----------------------    EXIT_STATUS    ------------------------

extern int				g_exit_status;

//	-----------------------    EXIT_STATUS    ------------------------

t_forchitat				*createNodefork(int value);
void					appendNodefork(t_forchitat **head, int value);
void					freeListfork(t_forchitat *head);

char					*return_wsback(char *str);
char					**ft_changeelement(char **arr, int index,
							char *newelement);
t_execcommand			*ft_returndataforexec(t_data **data, t_commands *cmnd);
void					ft_freeexeccommand(t_execcommand *execcommand);
int						ft_execute_one_pip(t_data **data, t_commands *cmnd);
int						ft_execute_middle_commands(t_data **data,
							t_commands *cmnd, t_commands *omo);
int						ft_execute_last_command(t_data **data, t_commands *cmnd,
							t_commands *omo);
void					ft_executebultin(t_data **data, t_commands *cmnd,
							int forkita);
void					ft_execute_builtins(t_data **data, t_commands *cmnd);
void					ft_execute_builtins2(t_data **data, t_commands *cmnd);
int						ft_check_builtins(t_commands *cmndd, char *cmnd);
void					ft_execute_all(t_data **data, t_commands *cmnd);

void					ft_execvee(char **cmd, t_data **data);
void					ft_execute_only_one_cmd_with_no_pipes(t_data **data,
							t_commands *cmnd);
void					ft_execute_first_command(t_data **data,
							t_commands *cmnd);
void					ft_execute_middle_commandz(t_data **data,
							t_commands *cmnd);
void					ft_execute_last_commaand(t_data **data,
							t_commands *cmnd);
void					ft_execute_more_than_one_cmd_with_pipes(t_data **data,
							t_commands *cmnd);
void					ft_execute_the_cmd(t_data **data, t_commands *cmnd);
char					**ft_env_to_array(t_env *env);
char					*ft_rtexpath(t_env *env, char *cmnd, int i, char *path);

//	-----------------------    EXECUTION    ------------------------
char					*return_wsback(char *str);
void					ft_check_if_directory(t_data **data, char *cmd,
							char *str);
void					ft_handle_path_existance(t_data **data, char *cmd);
int						ft_check_cmd(t_data **data, t_commands *comond,
							char *cmd);
int						ft_check_if_executable(char *str);
void					ft_print_er(char *str, char *err, int exit_status);
int						ft_check_whether_builtins(char *cmd);
void					ft_sigint(int sig);

void					ft_executesecondcmnd(t_data **data, t_commands *cmnd,
							int **pipes);

int						ft_strcmp(const char *s1, const char *s2);

char					*ft_strcpy(char *dest, const char *src);

int						ft_rulefinder(char *cmd, char *arraytofind);

char					*getValue(char *input);

char					*fetchValue(char *str, t_env *head);

t_env					*charArrayToEnvList(char **charArray);

void					appendEnvNode(t_env **head, char *str);

t_env					*createEnvNode(char *str);

void					delete_last_node(t_env **head);

void					deleteNode(t_env **head, char *target);

void					add_last_node(t_env **head, const char *str);

void					add_before_last_node(t_env **head, const char *str);

void					printenv(t_env *head, int fd);

int						ft_iseqin(char *str);

void					ft_echo(char **cmd, int fd);

void					ft_execute_all(t_data **data, t_commands *cmnd);

int						ft_execute(t_data **data, t_commands *cmnd);

int						ft_count(char **str);

char					*ft_retpwd(void);

int						ft_which_line(char **envp, char *str);

char					*ft_line_w_out_path(char *str, int len);

char					**ft_find_path(char **envp, t_env *head);

int						ft_chdir_error_print(char *path);

char					*ft_makethelist(char *cmd, char **path, t_env *head);

void					ft_execve(char **envp, char **cmnd, t_env *head);

void					ft_exit(t_data **data, t_commands *cmnds);

void					ft_pwd(t_data **data, int fd);

void					ft_cd(t_data **data, t_commands *comond, char *path);

void					ft_env(t_data **data, int fd);

void					ft_unset(t_data **data, t_commands *cmnd);

void					ft_export(t_data **data, char **args, int i, int fd);

int						ft_doesmatch(char *str, char *qst);

int						ft_ruleexist(t_data **data, char *iden);

void					ft_initialize(t_data **data, char **env);

void					ft_unsetiden(t_env **env, t_env **envnocmd, char *iden);

void					ft_exporttherule(t_data **data, char *iden, char *value,
							char *str);

void					free_commands(t_commands *head);

int						ft_strcmpwithoutnull(char *str, char *rts);

int						**ft_create_pipes(t_commands *cmnd);

void					ft_free_pipes(int **pipes, t_commands *cmnd, int i);

int						ft_check_last_character(char *str, char c);

int						ft_count_how_many_pipes(t_commands *cmnd);

void					free_t_data(t_data **dat);

//	-----------------------    EXECUTION    ------------------------

#endif
