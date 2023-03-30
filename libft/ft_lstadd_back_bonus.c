/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:33:46 by vduchi            #+#    #+#             */
/*   Updated: 2022/12/02 19:37:17 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newl)
{
	t_list	*my;

	my = NULL;
	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = newl;
	else
	{
		my = *lst;
		while (my->next != NULL)
			my = my->next;
		my->next = newl;
	}
}
