/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:12:36 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/23 19:41:04 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*my;

	if (!lst)
		return (0);
	my = lst;
	i = 1;
	while (my->next != NULL)
	{
		my = my->next;
		i++;
	}
	return (i);
}
