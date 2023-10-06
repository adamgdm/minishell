#include "minishell.h"
int g_exit_status = 148;
t_data *g_data;


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

void	_print_commands(t_commands *commands)
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

char *ft_itoa(int n)
{
	char *str;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = n;
	while (k > 0)
	{
		k = k / 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		str[i - 1] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

t_env *ft_exportminimum()
{
	char *pwd;
	char *str;

	pwd = ft_returnpwd();
	str = ft_strjoin("PWD=", pwd);
	t_env *env = createEnvNode(str);
	free(str);
	free(pwd);
	pwd = ft_itoa(1);
	str = ft_strjoin("SHLVL=", pwd);
	appendEnvNode(&(env), str);
	free(str);
	free(pwd);
	add_last_node(&(env), "_=env");
	return (env);
}

t_env *ft_exportminimumeq()
{
	char *pwd;
	char *str;

	t_env *env = createEnvNode("OLDPWD");
	pwd = ft_returnpwd();
	str = ft_strjoin("PWD=", pwd);
	appendEnvNode(&(env), str);
	free(pwd);
	free(str);
	pwd = ft_itoa(1);
	str = ft_strjoin("SHLVL=", pwd);
	appendEnvNode(&(env), str);
	free(str);
	free(pwd);
	return (env);
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

void ft_initalizebasevalue(t_data **data)
{
	char *str;
	int SHLVL;
	
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("malloc");
		exit(1);
	}
	(*data)->env = ft_exportminimum();
	(*data)->envnoeq = ft_exportminimumeq();
	ft_printennv((*data)->env, 1);
}

void ft_initialize(t_data **data, char **env)
{
	t_data *y;
/*	char *str;
	int SHLVL;
	if (!(*data) && env &&(*env))
	{*/
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
/*	}
	else if (!(*data) && env && (!(*env)))
	{
		printf("ALLO\n");
		ft_initalizebasevalue(data);
	}
	else
	{
		str = ft_returnrule((*data)->env, "SHLVL");
		SHLVL = ft_atoi(str);
		SHLVL++;
		free(str);
		str = ft_itoa(SHLVL);
		ft_unsetiden(&((*data)->env), &((*data)->envnoeq), "SHLVL");
		ft_exporttherule(data, "SHLVL", str);
		free(str);
	}*/
}

/*void ft_initialize(t_data **x, char **env)
{
    t_data *y;
	char *str;
	int SHLVL;
	char *number;

	/*if (x)
		SHLVL = ft_atoi(fetchValue("SHLVL", y->envnoeq));
	else
		SHLVL = 0;
	SHLVL++;
    y = (*x);
	if (!env)
	{
		y->envnoeq = createEnvNode("OLDPWD");
		str = ft_returnpwd();
		number = ft_itoa(SHLVL);
		appendEnvNode(&(y->envnoeq), ft_strjoin("PWD=", str));
		appendEnvNode(&(y->envnoeq), ft_strjoin("SHLVL", number));
	  	y->env = createEnvNode(ft_strdup(ft_strjoin("PWD", str)));
		appendEnvNode(&(y->env), ft_strdup(ft_strjoin("SHLVL", number)));
	}
	else
	{
		y->env = charArrayToEnvList(env);
		y->envnoeq = charArrayToEnvList(env);
		delete_last_node(&(y->env));
		delete_last_node(&(y->envnoeq));
		add_last_node(&(y->env), ft_strdup("_=env"));
	}
}*/

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

void ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void ft_sigquit(int sig)
{
	ft_exit(&g_data, NULL);
}

int main(int ac, char **av, char **envp) 
{
	(void)ac;
	(void)av;
	t_token *result;

	ft_initialize(&g_data ,envp);
	//ft_printennv(g_data->env, 1);
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigquit);
	while (1)
	{
		char *input = readline("\e[01;32mBoubou_shell> \e[0;37m");
		if (input && *input)
			add_history(input);
		if (!input)
			return (0);
		result = _lexer(input);
		if (!result)
			continue;
		if(_syntax_check(&result))
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
		ft_execute_all(&g_data, commands);
		 free(input);
		free_commands(commands);
	}

	return 0;
}
