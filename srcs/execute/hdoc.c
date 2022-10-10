/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:47 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 13:00:48 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include "../../includes/parse.h"
#include <readline/readline.h>

void	unlink_hdoc(t_argv *argv)
{
	t_argv	*tmp;
	t_redir	*hdoc;

	tmp = argv;
	while (tmp)
	{
		hdoc = tmp->hdoc;
		while (hdoc)
		{
			unlink(hdoc->value);
			hdoc = hdoc->next;
		}
		tmp = tmp->next;
	}
}

static void	read_for_hdoc(int fd, char *name)
{
	char	*line;
	char	*input;

	while (fd > 0)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, &name[7]) == SUCCESS)
		{
			free(input);
			break ;
		}
		if (replace_env_hdoc(&line, input))
			ft_error_exit("hdoc", "error", FAIL);
		ft_putendl_fd(line, fd);
		free(line);
		free(input);
	}
}

static void	run_hdoc(t_redir *hdoc)
{
	int		fd;
	t_redir	*tmp;

	tmp = hdoc;
	while (tmp)
	{
		unlink(tmp->value);
		fd = ft_open(tmp->value, HDOC);
		read_for_hdoc(fd, tmp->value);
		close(fd);
		tmp = tmp->next;
	}
}

static int	make_hdoc(t_argv *argv)
{
	int		status;
	pid_t	pid;
	t_argv	*tmp;

	tmp = argv;
	ignore_signal();
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, hdoc_sigint_handler);
		while (tmp)
		{
			run_hdoc(tmp->hdoc);
			tmp = tmp->next;
		}
		exit (SUCCESS);
	}
	if (pid < 0)
		ft_error("fork", strerror(errno), FAIL);
	wait(&status);
	status = status >> 8;
	g_info.last_exit_num = status;
	return (status);
}

int	check_heredoc(t_argv *argv)
{
	t_argv	*tmp;
	int		result;

	tmp = argv;
	result = SUCCESS;
	while (tmp)
	{
		if (tmp->hdoc)
		{
			result = make_hdoc(argv);
			break ;
		}
		tmp = tmp->next;
	}
	return (result);
}
