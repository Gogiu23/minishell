/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:26:59 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/11 12:04:10 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char *dst, const char *src, int control)
{
	size_t	len;

	len = 0;
	if (control == 0)
	{
		while (dst[len] != '\0')
			len++;
	}
	else
	{
		while (src[len] != '\0')
			len++;
	}
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	len = ft_count(dst, src, 0);
	if (len > dstsize)
		return (dstsize + ft_count(dst, src, 1));
	else if (dstsize != 0)
	{
		while (i < (dstsize - len - 1) && src[i] != '\0')
		{
			if (dstsize == len)
				break ;
			dst[len + i] = src[i];
			i++;
		}
		dst[len + i] = '\0';
	}
	return (len + ft_count(dst, src, 1));
}
