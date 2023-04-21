/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 19:42:05 by vduchi            #+#    #+#             */
/*   Updated: 2023/04/21 11:36:53 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	free_double_ret_int(char **split, int i, int out)
{
	if (split)
	{
		if (split[i])
			while (split[i])
				i++;
		while (--i >= 0)
			free(split[i]);
		free(split);
	}
	return (out);
}

char	**free_double_ret_char(char **array, int i)
{
	if (i > 0)
	{
		while (--i >= 0)
			free(array[i]);
		free(array);
		return (NULL);
	}
	else
	{
		while (array[i])
			i++;
		while (--i >= 0)
			free(array[i]);
		free(array);
		return (NULL);
	}
}
