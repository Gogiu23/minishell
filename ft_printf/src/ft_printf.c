/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 22:14:52 by vduchi            #+#    #+#             */
/*   Updated: 2022/11/15 20:23:36 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/ft_printf.h"

static int	ft_check(char c, va_list args, int *count)
{
	int	res;

	res = 1;
	if (c == 'c')
		res = ft_print_char(va_arg(args, int), count);
	else if (c == 'd' || c == 'i')
		res = ft_print_num(0, va_arg(args, int), count);
	else if (c == 's')
		res = ft_print_str(va_arg(args, char *), 1, count);
	else if (c == 'p')
		res = ft_print_hex(0, va_arg(args, unsigned long long), 0, count);
	else if (c == 'u')
		res = ft_print_num(va_arg(args, unsigned int), 0, count);
	else if (c == 'x')
		res = ft_print_hex(va_arg(args, unsigned int), 0, 2, count);
	else if (c == 'X')
		res = ft_print_hex(va_arg(args, unsigned int), 0, 1, count);
	else if (c == '%')
		res = ft_print_char(c, count);
	return (res);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			if (!ft_check(*str, args, &count))
				return (-1);
		}
		else
		{
			if (write (1, str, 1) != 1)
				return (-1);
			count++;
		}
		str++;
	}
	va_end(args);
	return (count);
}

/* int	main(void)
{
	int	p1;
	int	p2;
	char	*str;

	str = malloc(4);
	str[0] = '\0';
	p1 = ft_printf("My: %p\n", str);
	p2 = printf("De: %p\n", str);
	printf("p1: %d\np2: %d\n", p1, p2);
	return (0);
} */