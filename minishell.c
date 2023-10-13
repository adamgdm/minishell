#include "minishell.h"

int		g_exit_status = 55;

void	_print_token(t_token *token)
{
	printf("-----------------------------------------------\n");
	while (token)
	{
		printf("[content]: %s\n", token->content);
		printf("[type]: %d\n", token->type);
		printf("[state]: %d\n", token->state);
		printf("[before_expanded]: %s\n", token->before_expanded);
		printf("[space_check]: %d\n", token->space_check);
		printf("-----------------------------------------------\n");
		token = token->next;
	}
}

void	_print_commands(t_commands *commands)
{
	int	i;

	i = 0;
	printf("$-----------------commands---------------------$\n");
	while (commands)
	{
		_print_array(commands->cmd);
		printf("in_file: %d\n", commands->in_file);
		printf("out_file: %d\n", commands->out_file);
		printf("error_exist: %d\n", commands->error_exist);
		printf("pipefd[0]: %d  ", commands->pipefd[0]);
		printf("pipefd[1]: %d\n", commands->pipefd[1]);
		printf("-----------------------------------------------\n");
		commands = commands->next;
		i++;
	}
}

void	ft_exportminimum(t_data **data)
{
	char	*pwd;
	char	*str;

	pwd = ft_returnpwd(data);
	str = ft_strjoin("PWD=", pwd);
	(*data)->env = ft_create_env_node(str);
	free(str);
	free(pwd);
	pwd = ft_itoa(1);
	str = ft_strjoin("SHLVL=", pwd);
	ft_append_env_node(&(*data)->env, str);
	free(str);
	free(pwd);
	add_last_node(&(*data)->env, "_=env");
}

void	ft_exportminimumeq(t_data **data)
{
	char	*pwd;
	char	*str;

	(*data)->envnoeq = ft_create_env_node("OLDPWD");
	pwd = ft_returnpwd(data);
	str = ft_strjoin("PWD=", pwd);
	ft_append_env_node(&(*data)->envnoeq, str);
	free(pwd);
	free(str);
	pwd = ft_itoa(1);
	str = ft_strjoin("SHLVL=", pwd);
	ft_append_env_node(&(*data)->envnoeq, str);
	free(str);
	free(pwd);
}

void	ft_printennv(t_env *head, int fd)
{
	t_env	*x;

	x = head;
	while (x)
	{
		ft_putstr_fd(x->str, fd);
		ft_putchar_fd('\n', fd);
		x = x->next;
	}
}

void	ft_initalizebasevalue(t_data **data)
{

	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("malloc");
		exit(1);
	}
	ft_exportminimum(data);
	ft_exportminimumeq(data);
}

void	ft_initialize(t_data **data, char **env)
{
	t_data	*y;
	char	*str;
	int		SHLVL;

	if (!(*env))
		ft_initalizebasevalue(data);
	else
	{
		y = malloc(sizeof(t_data));
		if (!y)
		{
			perror("malloc");
			exit(1);
		}
		y->env = ft_array_to_elist(env);
		y->envnoeq = ft_array_to_elist(env);
		delete_last_node(&(y->env));
		delete_last_node(&(y->envnoeq));
		add_last_node(&(y->env), "_=env");
		(*data) = y;
	}
	y->path = ft_returnpwd(&y);
	str = ft_fetchvalue("SHLVL", (*data)->envnoeq);
	if (!str)
		SHLVL = 1;
	else
	{
		SHLVL = ft_atoi(str);
		SHLVL++;
	}
	free(str);
	if (SHLVL == 999)
		str = ft_strdup("");
	else
		str = ft_itoa(SHLVL);
	ft_unsetiden(&((*data)->env), &((*data)->envnoeq), "SHLVL");
	ft_exporttherule(data, "SHLVL", str, NULL);
	free(str);
}

int	ft_doesmatch(char *str, char *qst)
{
	int	index;

	index = 0;
	if (!str || !qst)
		return (0);
	while (str[index] != '\0' || qst[index] != '\0')
	{
		if (str[index] != qst[index])
			return (0);
		index++;
	}
	if (!qst[index] && !str[index])
		return (1);
	return (0);
}

void	ft_sigints(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = (127 + sig) % 256;
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\e[01;32mBoubou_shell> \e[0;37m", 1);
		exit(0);
	}
}

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\e[01;32mBoubou_shell> \e[0;37m", 1);
		g_exit_status = (127 + sig) % 256;
	}
}

int	ft_handle_more_than_one_arg(t_data **data, char *str)
{
	ft_check_if_directory(data, str, return_wsback(str));
	return (g_exit_status);
}

int	main(int ac, char **av, char **envp)
{
	t_token		*result;
	t_data		*g_data;
	char		*input;
	int			a;
	t_commands	*commands;

	(void)av;
	g_data = NULL;
	if (ac != 1)
		return (ft_handle_more_than_one_arg(&g_data, av[1]));
	ft_initialize(&g_data, envp);
	// printf("exit_status: %d\n", g_exit_status);
	// ft_printennv(g_data->env, 1);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	// printf("exit_status: %d\n", g_exit_status);
	while (1)
	{
		input = readline("\e[01;32mBoubou_shell> \e[0;37m");
		if (input && *input)
			add_history(input);
		if (!input)
			ft_exit(&g_data, NULL);
		result = _lexer(input);
		if (!result)
			continue ;
		a = _syntax_check(&result);
		if (a)
		{
			_free_all_tokens(&result, 1);
			free(input);
			if (a == -1)
			{
				free_t_data(&g_data);
				return (g_exit_status);
			}
			continue ;
		}
		_expander(&result, g_data);
		_update_tokens(&result);
		// _print_token(result);
		commands = _parser(&result, g_data);
		// _print_commands(commands);
		_free_all_tokens(&result, 0);
		ft_execute_the_cmd(&g_data, commands);

		free(input);
		free_commands(commands);
	}
	return (g_exit_status);
}
