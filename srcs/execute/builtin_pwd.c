/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:30 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 13:00:38 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include <limits.h>

void	ft_pwd(char **cmd)
{
	char	cwd[PATH_MAX];

	if (cmd[1])
	{
		ft_error("pwd", "too many arguments", FAIL);
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		ft_error("pwd", strerror(errno), FAIL);
		return ;
	}
	printf("%s\n", cwd);
}
