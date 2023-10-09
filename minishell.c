#include "minishell.h"
int g_exit_status = 55;

void _print_token(t_token *token)
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

void _print_commands(t_commands *commands)
{
	int i = 0;
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

void ft_exportminimum(t_data **data)
{
	char *pwd;
	char *str;

	pwd = ft_returnpwd();
	str = ft_strjoin("PWD=", pwd);
	(*data)->env = createEnvNode(str);
	free(str);
	free(pwd);
	pwd = ft_itoa(1);
	str = ft_strjoin("SHLVL=", pwd);
	appendEnvNode(&(*data)->env, str);
	free(str);
	free(pwd);
	add_last_node(&(*data)->env, "_=env");
}

void ft_exportminimumeq(t_data **data)
{
	char *pwd;
	char *str;

	(*data)->envnoeq = createEnvNode("OLDPWD");
	pwd = ft_returnpwd();
	str = ft_strjoin("PWD=", pwd);
	appendEnvNode(&(*data)->envnoeq, str);
	free(pwd);
	free(str);
	pwd = ft_itoa(1);
	str = ft_strjoin("SHLVL=", pwd);
	appendEnvNode(&(*data)->envnoeq, str);
	free(str);
	free(pwd);
}

void ft_printennv(t_env *head, int fd)
{
	t_env *x;

	x = head;
	while (x)
	{
		ft_putstr_fd(x->str, fd);
		ft_putchar_fd('\n', fd);
		x = x->next;
	}
}

t_data *ft_initalizebasevalue(t_data **data)
{
	char *str;
	int SHLVL;

	printf("HELLOSAMA\n");
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("malloc");
		exit(1);
	}
	ft_exportminimum(data);
	ft_exportminimumeq(data);
}

void ft_initialize(t_data **data, char **env)
{
	t_data *y;
	char *str;
	int SHLVL;

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
		y->env = charArrayToEnvList(env);
		y->envnoeq = charArrayToEnvList(env);
		delete_last_node(&(y->env));
		delete_last_node(&(y->envnoeq));
		add_last_node(&(y->env), "_=env");
		(*data) = y;
	}
	str = fetchValue("SHLVL", (*data)->envnoeq);
	if (!str)
		SHLVL = 0;
	else
	{
		SHLVL = ft_atoi(str);
		SHLVL++;
	}
	free(str);
	str = ft_itoa(SHLVL);
	ft_unsetiden(&((*data)->env), &((*data)->envnoeq), "SHLVL");
	ft_exporttherule(data, "SHLVL", str);
	free(str);
}

int ft_doesmatch(char *str, char *qst)
{
	int index = 0;
	if (!str || !qst)
		return (0);
	while (str[index] != '\0' || qst[index] != '\0')
	{
		if (str[index] != qst[index])
			return 0;
		index++;
	}
	if (!qst[index] && !str[index])
		return 1;
	return (0);
}

void ft_sigints(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = (127 + sig) % 256;
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\e[01;32mBoubou_shell> \e[0;37m", 1);
		exit(0);
	}
}

void ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		ft_putstr_fd("\n", 1);
		ft_putstr_fd("\e[01;32mBoubou_shell> \e[0;37m", 1);
		g_exit_status = (127 + sig) % 256;
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_token *result;
	t_data *g_data;

	g_data = NULL;
	ft_initialize(&g_data, envp);
	// printf("exit_status: %d\n", g_exit_status);
	// ft_printennv(g_data->env, 1);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	// printf("exit_status: %d\n", g_exit_status);
	while (1)
	{
		char *input = readline("\e[01;32mBoubou_shell> \e[0;37m");
		if (input && *input)
			add_history(input);
		if (!input)
			ft_exit(&g_data, NULL);
		result = _lexer(input);
		if (!result)
			continue;
		if (_syntax_check(&result))
		{
			_free_all_tokens(&result, 1);
			free(input);
			continue;
		}
		_expander(&result, g_data);
		_update_tokens(&result);
		//_print_token(result);
		//_print_token(result);
		t_commands *commands = _parser(&result, g_data);
		// _print_commands(commands);
		_free_all_tokens(&result, 0);
		ft_execute_the_cmd(&g_data, commands);
		free(input);
		free_commands(commands);
	}

	return g_exit_status;
}
