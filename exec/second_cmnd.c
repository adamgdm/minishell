#include "../minishell.h"

void	ft_execute_middle_commandz(t_data **data, t_commands *cmnd)
{
	int			forkita;
	t_commands	*current;

	if (ft_check_cmd(data, cmnd, NULL))
	{
		if (ft_builtings_cd_exit_unset_exportWithParameters(data, cmnd))
			return ;
		cmnd->pid = fork();
		if (cmnd->pid == 0)
		{
			signal(SIGINT, ft_sigints);
			if (cmnd->out_file == 1 && cmnd->in_file == 0)
			{
				dup2(cmnd->pipefd[1], 1);
				dup2(cmnd->pipefd[0], 0);
			}
			else
			{
				if (cmnd->out_file == 1 && cmnd->in_file != 0)
				{
					dup2(cmnd->in_file, 0);
					dup2(cmnd->pipefd[1], 1);
				}
				else if (cmnd->out_file != 1 && cmnd->in_file == 0)
				{
					dup2(cmnd->out_file, 1);
					dup2(cmnd->pipefd[0], 0);
				}
				else
				{
					dup2(cmnd->in_file, 0);
					dup2(cmnd->out_file, 1);
				}
			}
			close(cmnd->pipefd[0]);
			close(cmnd->pipefd[1]);
			current = cmnd->next;
			while (current)
			{
				close(current->pipefd[0]);
				close(current->pipefd[1]);
				current = current->next;
			}
			current = cmnd->previous;
			while (current)
			{
				close(current->pipefd[0]);
				close(current->pipefd[1]);
				current = current->previous;
			}
			if (ft_builtings_echo_env_exportwithparameters(data, cmnd) == 0)
				ft_execvee(cmnd->cmd, data);
			else
				exit(0);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			close(cmnd->pipefd[1]);
		}
	}
}