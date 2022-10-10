/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:01:00 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 13:01:00 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	set_child_exit(int status)
{
	if (status == 2)
	{
		printf("\n");
		g_info.last_exit_num = status + 128;
	}
	else if (status == 3)
	{
		printf("Quit: %d\n", status);
		g_info.last_exit_num = status + 128;
	}
	else
		g_info.last_exit_num = status >> 8;
}

static void	wait_childs(int cnt_pipe)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < cnt_pipe + 1)
	{
		if (wait(&status) < 0)
			status = 1;
	}
	set_child_exit(status);
}

static void	run_execve_proc(char **cmd)
{
	char	*path;

	if (!cmd)
		exit(SUCCESS);
	path = get_path(*cmd);
	if (!path)
		ft_error_exit(*cmd, "command not found", ERR_CMD_NOT_FOUND);
	if (execve(path, cmd, g_info.env) == -1)
		ft_error_exit(*cmd, strerror(errno), FAIL);
}

static void	run_child_proc(t_argv *argv, int **pipes, int i)
{
	set_stdin_pipe(pipes, i - 1);
	set_stdout_pipe(argv, pipes, i);
	set_stdout_redir(argv);
	set_stdin_redir(argv);
	if (is_builtin(argv->cmd) == TRUE)
		run_builtin_proc(argv->cmd);
	else
		run_execve_proc(argv->cmd);
}

void	run_fork(t_argv *argv, pid_t *pids, int **pipes, int cnt_pipe)
{
	int		i;
	t_argv	*tmp;

	i = -1;
	tmp = argv;
	ignore_signal();
	while (++i < cnt_pipe + 1)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			default_signal();
			run_child_proc(tmp, pipes, i);
		}
		if (pids[i] < 0)
		{
			ft_error("fork", strerror(errno), FAIL);
			break ;
		}
		tmp = tmp->next;
	}
	close_pipes(pipes, cnt_pipe);
	wait_childs(cnt_pipe);
}
