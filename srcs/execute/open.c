/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:52 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 13:00:52 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include <fcntl.h>

int	ft_open(char *file, int type)
{
	int	fd;

	if (type == T_OUT)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (type == A_OUT)
		fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (type == IN)
		fd = open(file, O_RDONLY);
	if (type == HDOC)
		fd = open(file, O_CREAT | O_WRONLY, S_IRUSR);
	if (fd < 0 && g_info.pid != getpid())
		ft_error_exit(file, strerror(errno), FAIL);
	if (fd < 0)
	{
		ft_error(file, strerror(errno), FAIL);
		return (-1);
	}
	return (fd);
}
