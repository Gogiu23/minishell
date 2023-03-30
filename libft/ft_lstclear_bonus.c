/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 21:12:23 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/22 18:22:12 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	int		i;
	t_list	*my;

	i = 0;
	my = *lst;
	while (my != NULL)
	{
		del(my->content);
		my = my->next;
		free(*lst);
		*lst = my;
	}
	*lst = NULL;
}
