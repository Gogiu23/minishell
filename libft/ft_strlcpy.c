/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:48:46 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/19 16:15:31 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (dstsize != 0)
	{
		while (++i < (dstsize - 1) && src[i] != '\0')
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (len);
}
