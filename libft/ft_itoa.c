/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:58:51 by vduchi            #+#    #+#             */
/*   Updated: 2022/11/16 15:35:47 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_int_to_str(char *str, long int n, int sign, int len)
{
	int	i;

	i = 0;
	if (sign == 1)
	{
		str[0] = '-';
		len--;
	}
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		str[len + sign - i - 1] = ((n % 10) + '0');
		n /= 10;
		i++;
	}
	str[len + sign] = '\0';
	return (str);
}

static int	ft_count(long int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*str;	

	sign = 0;
	len = ft_count((long int)n);
	if (len == 0)
		str = ft_strdup("0");
	else
	{
		if (n < 0)
			sign = 1;
		str = ft_calloc(sizeof(char), len + 1);
		if (!str)
			return (NULL);
		str = ft_int_to_str(str, (long int)n, sign, len);
	}
	return (str);
}
