/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 05:27:11 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/24 22:27:23 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(int n, int sign, int fd)
{
	int		i;
	char	c[11];

	i = 0;
	while (n > 0)
	{
		if (sign == -1)
		{
			write (fd, "-", 1);
			sign++;
		}
		c[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	while (--i >= 0)
		write (fd, &c[i], 1);
}

static int	ft_count(int n, int fd)
{
	int	res;

	res = 0;
	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		res = -1;
		n = 0;
	}
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		res++;
		n /= 10;
	}
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		len;
	int		sign;

	sign = 1;
	len = ft_count(n, fd);
	if (len == 0)
		write (fd, "0", 1);
	else if (n < 0)
	{
		sign = -1;
		n *= -1;
	}
	if (len != -1)
		ft_print(n, sign, fd);
}
