/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:15:01 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/18 19:52:40 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

char	**change_env(char *env[], char **new_env, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (env[j])
	{
		if (i == j)
		{
			j++;
			continue ;
		}
		new_env[k] = ft_strdup(env[j]);
		if (!new_env[k])
			return (free_double_pointer(new_env, k - 1));
		j++;
		k++;
	}
	new_env[k] = NULL;
	free_double_pointer(env, j - 1);
	return (new_env);
}

char	**ft_unset(char *env[], char *str)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			break ;
	if (env[i] == NULL)
		return (env);
	j = 0;
	while (env[j])
		j++;
	new_env = (char **)malloc(sizeof(char *) * (j - 1));
	if (!new_env)
		return (NULL);
	return (change_env(env, new_env, i));
}
