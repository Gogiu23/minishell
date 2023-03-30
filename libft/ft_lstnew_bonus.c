/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 18:04:11 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/24 11:15:12 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*one;

	one = malloc(sizeof(t_list) * 1);
	if (!one)
		return (NULL);
	one->content = content;
	one->next = NULL;
	return (one);
}
