/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 14:13:57 by jihyukim          #+#    #+#             */
/*   Updated: 2022/10/10 12:59:36 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_free;
	t_list	*seek;

	if (!del)
		return ;
	seek = *lst;
	while (seek)
	{
		to_free = seek;
		seek = seek->next;
		ft_lstdelone(to_free, del);
	}
	*lst = 0;
}
