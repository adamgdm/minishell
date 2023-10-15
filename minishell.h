/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoujdam <agoujdam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 01:14:12 by agoujdam          #+#    #+#             */
/*   Updated: 2023/10/15 01:47:35 by agoujdam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_state
{
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
	char				*path;
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

//------------------------------------    NORMINETTE    --------

typedef struct s_vars
{
	char				*save;
	int					i;
	int					j;
	int					k;
}						t_vars;

typedef struct s_vars2
{
	t_token				*current;
	t_token				*head;
	int					i;
	int					j;
	char				*s;
}						t_vars2;

typedef struct s_vars3
{
	char				**commands;
	int					in_file;
	int					out_file;
	int					error;
	int					already_printed;
	int					previous_pipe;
	int					*result_pipe;
}						t_vars3;

//------------------------------------    NORMINETTE    -----------

int						ft_handle_more_than_one_arg(t_data **data, char *str);
void					ft_sigint(int sig);
void					ft_sigints(int sig);
int						ft_doesmatch(char *str, char *qst);
void					ft_initialize(t_data **data, char **env, char *str);
void					ft_exportminimum(t_data **data);
void					ft_exportminimumeq(t_data **data);
void					ft_printennv(t_env *head, int fd);
void					ft_initalizebasevalue(t_data **data);
void					ft_initializevalues(t_data **data, char **env);

//	-----------------------    PARSING    ------------------------

t_token					*_lexer(char **input);
t_token					*_create_token(char *value, enum e_token type,
							enum e_state state, int check_space);
void					_add_token(t_token **head, t_token *new);
void					_update_tokens(t_token **result);
int						_it_contains(int c);
void					_expander(t_token **head, t_data *data);
void					_expander_norm(t_token **head);
void					_expander_norm2(t_token **head, t_data *data);
void					_update_before_expanded(t_token **head);
char					*_append(char *str, char c);
int						_syntax_check(t_token **result);
t_commands				*_parser(t_token **result, t_data *data);
t_commands				*_create_command(t_vars3 *vars);
void					_add_command(t_commands **head, t_commands *new);
void					_print_array(char **array);
void					_free_all_tokens(t_token **head, int check);
int						_process_env_value(char *value);
int						*_here_doc(char *content, int check, t_data *data);
char					*_expand_word(t_token *head, t_data *data);
char					*_expand_word2(char *content, t_data *data);
void					ft_sigints(int sig);
void					_join_exit_status(char **save, int *i);
void					_join_digit(char **save, char *content, t_data *data,
							int *i);
void					_join_dollar_with_char(char **save, char *content,
							int *i);
void					_join_the_word(char **save, char *tmp, t_data *data,
							t_token *head);
void					_join_the_word_doc(char **save, char *tmp,
							t_data *data);
void					_norminette(char **save, t_token *head, t_data *data,
							t_vars *vars);
void					_norminette_doc(char **save, char *content,
							t_data *data, t_vars *vars);
void					_token_creation(char *input, t_token **head, int *i);
int						_norminette1(char *input, t_token **head, int *i,
							int *j);
int						_norminette2(char *input, t_token **head, int *i,
							int *j);
void					_norminette3(char *input, t_token **head, char **save,
							int *i);
int						_norminette4(char *input, t_vars2 *vars);
int						_lexer_norm(t_token **head, char *input);
void					_lexer_norm2(char *input, t_token **head, int *i,
							int *j);
int						_lexer_norm3(t_token **head, char *input);
void					_lexer_norm4(char *input, t_token **head, int *i,
							int *j);
void					_token_norm(char *input, t_token **head, int *i);
void					_token_norm2(char *input, t_token **head, int *i);
void					_parser_norm(t_token *current, int *out_file,
							int *error, int *already_printed);
void					_parser_free_norm(t_token *current);
void					_parser_norm2(t_token *current, int *out_file,
							int *error, int *already_printed);
void					_parser_norm3(t_token *current, int *in_file,
							int *error, int *already_printed);
void					_parser_norm4(t_token *current, int *in_file,
							t_data *data);
int						_parser_norm5(t_commands **head, int **result_pipe,
							t_vars3 *vars, int *previous_pipe);
int						_is_there_space_or_tab(char *content);
int						_parser_norm6(t_commands **head, t_token *current,
							t_vars3 *vars, t_data *data);
void					_initialize_vars(t_vars3 *vars);
char					**_append_string(char **commands, char *content);
void					_do_norm(t_token *current, t_vars3 *vars);
int						_syntax_norm(t_token *current);
int						_syntax_norm2(t_token *current);
int						_syntax_norm3(t_token *current);
int						_syntax_norm4(t_token *current);
int						_syntax_norm5(void);
int						_syntax_norm6(void);
int						_syntax_norm7(t_token *current, int i);
void					_update_tokens_utils(t_token *current);
int						_check_type(enum e_token type);
int						_do_norm2(t_token *current);
void					_do_norm3(t_token *current, t_vars3 *vars,
							t_data *data);
void					free_commands(t_commands *head);
void					free_commands2(t_commands *head);
int						_launch_shell(t_data *g_data);
void					_minishell_norm(t_data **g_data, t_commands *commands,
							char *input, t_token **result);
t_commands				*_minishell_norm2(t_token **result, t_data *g_data);
int						_minishell_norm3(t_data **g_data);
t_token					*_minishell_norm4(char **input, t_data **g_data);

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

//	-----------------------    EXECUTION    ------------------------

int						ft_check_if_file_using_stat(char *file);
void					ft_freepathandpaths(char *path, char **paths);
char					*ft_rtexpath(t_env *env, char *cmnd, int i, char *path);
char					*ft_rtexpathve(t_env *env, char *cmnd, int i,
							char *path);
char					**ft_env_to_array(t_env *env);
t_execcommand			*ft_returndataforexec(t_data **data, t_commands *cmnd);
t_execcommand			*ft_returndataforexecve(t_data **data,
							t_commands *cmnd);
int						ft_execvee(char **cmd, t_data **data);
char					**ft_changeelement(char **arr, int index,
							char *newelement);
void					ft_freeexeccommand(t_execcommand *execcommand);
void					ft_set_exit_status(void);
void					ft_set_up_io_mid_redirection(t_commands *cmnd);
void					ft_execute_child_mid_process(t_data **data,
							t_commands *cmnd);
void					ft_execute_middle_commandz(t_data **data,
							t_commands *cmnd);
t_commands				*return_node_after_error(t_commands *cmnd);
void					ft_ft_clozi_pipes_before(t_commands *cmnd);
void					ft_ft_clozi_pipes(t_commands *cmnd);
void					ft_set_up_io_redirection(t_commands *cmnd);
void					ft_execute_child_process(t_data **data,
							t_commands *cmnd);
void					ft_execute_last_commaand(t_data **data,
							t_commands *cmnd);
int						ft_builtinechoexpwithpara(t_data **data,
							t_commands *cmnd);
void					ft_execute_parent_process(t_commands **cmnd);
void					ft_efn(t_commands **comnd, t_commands *current);
void					ft_execute_first_command(t_data **data,
							t_commands *cmnd);
void					ft_ft_clozi_pipes_after(t_commands *cmnd);
void					ft_check_if_directory(t_data **data, char *cmd,
							char *str);
int						ft_check_if_executable(char *str);
int						ft_check_cmd(t_data **data, t_commands *comond,
							char *cmd);
void					ft_pwd_pre(char *str, t_data **data, int fd);
void					ft_env_pre(char *str, t_data **data, int fd);
int						ft_builtincdexpwithtpara(t_data **data,
							t_commands *cmnd);
int						ft_check_whether_builtins(char *cmd);
void					ft_print_er(char *str, char *err, int exit_status);
char					*return_wsback(char *str);
void					ft_handle_path_existance(t_data **data, char *cmd);
void					wait_for_processes(t_commands *cmnd);
void					ft_clozi_pipes(t_commands *cmnd);
void					ft_execute_more_than_one_cmd_with_pipes(t_data **data,
							t_commands *cmnd);
void					ft_execute_only_one_cmd_with_no_pipes(t_data **data,
							t_commands *cmnd);
void					ft_execute_the_cmd(t_data **data, t_commands *cmnd);
t_env					*ft_create_env_node(char *str);
void					ft_append_env_node(t_env **head, char *str);
t_env					*ft_array_to_elist(char **charArray);
int						ft_rulefinder(char *cmd, char *arraytofind);
char					*ft_getvalue(char *input);
void					delete_last_node(t_env **head);
void					add_last_node(t_env **head, const char *str);
void					add_bln_norminette(t_env **head, char *str);
void					add_before_last_node(t_env **head, char *str);
void					ft_deletethenode(t_env **head, char *target);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_fetchvalue(char *str, t_env *head);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_count(char **str);
int						ft_chdir_error_print(char *path);
void					ft_free_cd_stuff(char *str, char *str2, char **str3);
void					ft_free_and_replace(t_data **data, char *str,
							int casse);
void					ft_set_exit_status_cd(int status);
void					ft_handle_lblanat(t_data **data, char *pwd, char *path,
							int status);
void					ft_cd(t_data **data, t_commands *comond, char *path);
void					ft_unsetandex(t_data **data, char **cmd, char *str,
							char *rts);
void					ft_unsetandexport(t_data **data, char *rts, char *pwd,
							char *str);
char					*ft_return_home_or_pwd(t_data **data, char *path,
							char *lol);
int						ft_handle_cd_errors(t_data **data, t_commands *cmnd,
							char *path, char *lol);
void					ft_print_the_long_goddamn_sentence(void);
char					*ft_returncwd(void);
int						ft_free_return(char *str, int ret);
int						ft_does_directory_exist(t_data **data, char *path);
int						isdnin(char *cmd, char *arraytofind);
void					ft_echo_norm(char **cmd, int i, int fd);
void					ft_echo(char **cmd, int fd);
void					ft_env(t_data **data, int fd);
void					ft_freearr(char **arr);
void					ft_freecmd(t_commands *cmd);
t_commands				*ft_createcommand(char **str);
int						ft_isbiggerthankbir(char *str);
long long				ft_atoll(char *str);
int						ft_isnumber(char *str);
void					ft_error_exit(t_commands *cmnds);
void					ft_exit(t_data **data, t_commands *cmnds);
void					free_env_list(t_env *head);
void					free_t_data(t_data **dat);
void					free_commands(t_commands *head);
int						ft_number(char *str);
void					ft_free_array(char **array);
void					ft_printenv(t_env *env, int fd);
void					printargs(char **args);
int						ft_printerror(char *str);
int						ft_checkerrors(char *command, char *identifier);
void					ft_export(t_data **data, char **args, int i, int fd);
void					ft_unsetiden(t_env **env, t_env **envnocmd, char *iden);
char					**ft_parse_args_norm(char *str, int condition, int i,
							char **returnval);
void					ft_free_strtmp(char *str, char *tmp);
char					*ft_exporttherulenorm(t_data **data, char *iden,
							char *value, char *str);
void					ft_exporttherule(t_data **data, char *iden, char *value,
							char *str);
char					**ft_parse_args(char *str, int condition, int i,
							char **returnval);
int						ft_freeretone(char *str);
char					*ft_returnrule(t_env *env, char *rts);
int						ft_ruleexist(t_data **data, char *iden);
int						ft_checkexportorappend(char *str);
char					*ft_ft_getvalue(char *str);
void					ft_append(t_data **data, char *iden, char *value);
void					ft_pwd(t_data **data, int fd);
char					*ft_returnpwd(t_data **data);
char					*ft_returnfetch(t_data **data, char *buffer);
void					ft_freenode(t_env *node);
void					ft_deletenodebycontent(t_env **head, char *target);
void					ft_rulefinderanddelete_eq(t_data **data, char *rule);
void					ft_rulefinderanddelete(t_data **data, char *rule);
void					ft_unset(t_data **data, t_commands *cmnd);

//	-----------------------    EXECUTION    ------------------------

#endif
