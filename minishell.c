#include "minishell.h"


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
		printf("-----------------------------------------------\n");
		commands = commands->next;
		i++;
	}
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

int ft_doesmatch(char *str, char *qst)
{
    int index = 0;
    
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

void    ft_execute(t_data **data, t_commands *cmnd, char **envp)
{
    if (ft_doesmatch(cmnd->cmd[0], "pwd"))
        ft_pwd(cmnd->out_file);
	else if (ft_doesmatch(cmnd->cmd[0], "cd"))
		ft_cd(data ,cmnd->cmd[1], ft_retpwd());
	else if (ft_doesmatch(cmnd->cmd[0], "env"))
		ft_env(&(*data)->env, cmnd->out_file);
	else if (ft_doesmatch(cmnd->cmd[0], "unset"))
		ft_unset(data, cmnd);
	else if (ft_doesmatch(cmnd->cmd[0], "export"))
		ft_export(&(*data)->env, &(*data)->envnoeq, cmnd, cmnd->out_file);
	else if (ft_doesmatch(cmnd->cmd[0], "echo"))
		ft_echo(cmnd->cmd, cmnd->out_file);
    else if (ft_doesmatch(cmnd->cmd[0], "exit"))
		ft_exit((data), cmnd);
    else
		printf("Sbr lmk mazal massalit, ah ou exit fiha leaks, chof dok dialk wdiali antklf bihom ghda rah drni rassi. mhm tryiha db\n");
        //ft_execve(envp, cmnd->cmd, (*data)->env);
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
		char *input = readline("Boubou_shell> ");
		if (input && *input)
			add_history(input);
		result = _lexer(input);
		if (!result)
			continue;
		if(_syntax_check(&result))
		{
			_free_all_tokens(&result);
			free(input);
			continue;
		}
		_expander(&result);
		//_print_token(result);
		_update_tokens(&result);
		 t_commands *commands = _parser(&result);
		//_print_commands(commands);
		_free_all_tokens(&result);
		ft_execute(&data, commands,envp);
		free(input);
		free_commands(commands);
	

	}

	return 0;
}
