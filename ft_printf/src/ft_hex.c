/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 23:25:50 by vduchi            #+#    #+#             */
/*   Updated: 2022/11/15 20:28:48 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

static int	return_value(char *str, int *count)
{
	if (!ft_print_str(str, 0, count))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

static void	ft_calc(int *mode, char *c, unsigned int *x, unsigned long long *p)
{
	if (*mode > 0)
	{
		if (*mode == 1)
			*c = "0123456789ABCDEF"[*x % 16];
		else
			*c = "0123456789abcdef"[*x % 16];
		*x /= 16;
	}
	else
	{
		*c = "0123456789abcdef"[*p % 16];
		*p /= 16;
	}
}

static int	ft_error_p_x(int mode, int *count)
{
	if (mode == 0)
	{
		if (write (1, "0x0", 3) != 3)
			return (0);
		*count = *count + 3;
	}
	else if (mode == 1)
	{
		if (write (1, "0", 1) != 1)
			return (0);
		*count = *count + 1;
	}
	else
	{
		if (write (1, "0x", 2) != 2)
			return (0);
		*count = *count + 2;
	}
	return (1);
}

static int	ft_output_hex(int mode, unsigned int x, \
		unsigned long long p, int *count)
{
	int		i;
	char	c;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * 21);
	if (!str)
		return (0);
	if (!mode)
	{
		if (!ft_error_p_x(2, count))
		{
			free(str);
			return (0);
		}
	}
	while ((p > 0 || x > 0) && i < 21)
	{
		ft_calc(&mode, &c, &x, &p);
		str[i] = c;
		i++;
	}
	str[i] = '\0';
	return (return_value(str, count));
}

int	ft_print_hex(unsigned int x, unsigned long long p, \
		int mode, int *count)
{
	if (mode > 0)
	{
		if (!x)
		{
			if (!ft_error_p_x(1, count))
				return (0);
			return (1);
		}
		return (ft_output_hex(mode, x, p, count));
	}
	else
	{
		if (!p)
		{
			if (!ft_error_p_x(0, count))
				return (0);
			return (1);
		}
		return (ft_output_hex(mode, x, p, count));
	}
}
