/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:48:56 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/18 19:52:31 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

char	**free_double_pointer(char **arr, int i)
{
	while (i >= 0)
	{
		free (arr[i]);
		i--;
	}
	free (arr);
	return (NULL);
}

char	**ft_export(char *env[], char *new_string)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_double_pointer(new_env, i - 1));
	}
	new_env[i] = ft_strdup(new_string);
	if (!new_env[i])
		return (free_double_pointer(new_env, i - 1));
	new_env[i + 1] = NULL;
	free_double_pointer(env, i - 1);
	return (new_env);
}
