/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaqir <afaqir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 22:50:26 by afaqir            #+#    #+#             */
/*   Updated: 2023/10/14 22:50:27 by afaqir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	str = ft_strjoin("shlvl=", pwd);
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
	str = ft_strjoin("shlvl=", pwd);
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

void	ft_initializevalues(t_data **data, char **env)
{
	(*data) = malloc(sizeof(t_data));
	if (!(*data))
	{
		perror("malloc");
		exit(1);
	}
	(*data)->env = ft_array_to_elist(env);
	(*data)->envnoeq = ft_array_to_elist(env);
	delete_last_node(&((*data)->env));
	delete_last_node(&((*data)->envnoeq));
	add_last_node(&((*data)->env), "_=env");
}

void	ft_initialize(t_data **data, char **env, char *str)
{
	int	shlvl;

	if (!env || !(*env))
		ft_initalizebasevalue(data);
	else
		ft_initializevalues(data, env);
	(*data)->path = ft_returnpwd(data);
	str = ft_fetchvalue("shlvl", (*data)->envnoeq);
	if (!str)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(str);
		shlvl++;
	}
	free(str);
	if (shlvl == 1000)
		str = ft_strdup("");
	else
		str = ft_itoa(shlvl);
	ft_unsetiden(&((*data)->env), &((*data)->envnoeq), "shlvl");
	ft_exporttherule(data, "shlvl", str, NULL);
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
		exit(g_exit_status);
	}
}

void	ft_sigint(int sig)
{
	if (sig == SIGINT)
	{
		(void)sig;
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = (127 + sig) % 256;
	}
}

int	ft_handle_more_than_one_arg(t_data **data, char *str)
{
	ft_check_if_directory(data, str, return_wsback(str));
	return (g_exit_status);
}

void	free_commands2(t_commands *head)
{
	t_commands	*current;
	t_commands	*temp;
	int			i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		i = 0;
		temp = current;
		current = current->next;
		while (temp->cmd && temp->cmd[i] != NULL)
		{
			printf("freeing %s\n", temp->cmd[i]);
			i++;
		}
		free(temp->cmd[i]);
		free(temp->cmd);
		printf("freeing %d %d\n", temp->pipefd[0], temp->pipefd[1]);
		free(temp->pipefd);
		free(temp);
	}
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
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (_launch_shell(g_data));
	return (g_exit_status);
}
