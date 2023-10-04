#include "minishell.h"
int g_exit_status = 148;

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

void ft_initialize(t_data **x, char **env)
{
    t_data *y;
    y = (*x);
    y->env = charArrayToEnvList(env);
    y->envnoeq = charArrayToEnvList(env);
	delete_last_node(&(y->env));
	delete_last_node(&(y->envnoeq));
	add_last_node(&(y->env), ft_strdup("_=env"));
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

int    ft_execute(t_data **data, t_commands *cmnd)
{
	char **pwd;

	pwd = malloc(sizeof(char *));
	(*pwd) = ft_returnrule((*data)->env, "OLDPWD");
	if (!cmnd || !cmnd->cmd)
		return (-1);
    if (ft_doesmatch(cmnd->cmd[0], "pwd"))
        ft_pwd(cmnd->out_file);
	else if (ft_doesmatch(cmnd->cmd[0], "cd"))
		ft_cd(data ,cmnd->cmd[1], pwd);
	else if (ft_doesmatch(cmnd->cmd[0], "env"))
		ft_env(data, (*pwd),cmnd->out_file);
	else if (ft_doesmatch(cmnd->cmd[0], "unset"))
		ft_unset(data, cmnd);
	else if (ft_doesmatch(cmnd->cmd[0], "export"))
	{
		ft_export(data, cmnd->cmd, cmnd->out_file);
	}
	else if (ft_doesmatch(cmnd->cmd[0], "echo"))
		ft_echo(cmnd->cmd, cmnd->out_file);
    else if (ft_doesmatch(cmnd->cmd[0], "exit"))
		ft_exit((data), cmnd);
    else
	{
		free(pwd); 
		return (1);
	}
	free(pwd);
	return (0);
}


int main(int ac, char **av, char **envp) 
{
	(void)ac;
	(void)av;
	t_data	*data;
	t_token *result;

	data = malloc(sizeof(t_data));
	ft_initialize(&data, envp);
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
		_expander(&result, data);
		_update_tokens(&result);
		//_print_token(result);
		//_print_token(result);
		t_commands *commands = _parser(&result);
		//_print_commands(commands);
		 _free_all_tokens(&result, 0);
		 ft_execute_all(&data, commands);
		 free(input);
		free_commands(commands);
	}

	return 0;
}
