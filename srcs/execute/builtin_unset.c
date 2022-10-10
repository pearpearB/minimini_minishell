/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:00:32 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 13:00:40 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	del_env_one(t_env *del)
{
	if (del->prev)
		del->prev->next = del->next;
	else
		g_info.env_list = del->next;
	if (del->next)
		del->next->prev = del->prev;
	free(del->key);
	free(del->value);
	free(del);
}

void	ft_unset(char **cmd)
{
	t_env	*del;
	int		i;

	i = 0;
	if (!cmd[1])
		return ;
	while (cmd[++i])
	{
		del = get_env(cmd[i]);
		if (del)
			del_env_one(del);
		else
		{
			if (!is_valid_key(cmd[i]))
				print_invalid_key("unset: `", cmd[i]);
		}
	}
	make_env_arr();
}
