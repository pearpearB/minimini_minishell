/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:11 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 13:00:12 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

t_info	g_info;

static void	unset_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(int ac, char *av[], char *envp[])
{
	t_argv	*argvs;

	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("too many arguments", STDERR_FILENO);
		exit(FAIL);
	}
	g_info.pid = getpid();
	init_env(envp);
	while (1)
	{
		argvs = NULL;
		unset_echoctl();
		main_signal();
		parse(&argvs);
		execute(argvs);
	}
}
