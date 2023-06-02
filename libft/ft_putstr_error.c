/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:08:10 by gdominic          #+#    #+#             */
/*   Updated: 2023/06/02 13:34:07 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_error(const char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	else
	{
		write (2, s, ft_strlen(s));
		exit (EXIT_FAILURE);
	}
}
