/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 12:15:26 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/11 15:07:55 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = NULL;
	if ((char)c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char *)s);
	}
	else if (s != 0)
	{
		while (*s != '\0')
		{
			if (*s == (char)c)
				ptr = (char *)s;
			s++;
		}
		if (ptr != 0)
			return (ptr);
	}
	return (0);
}
