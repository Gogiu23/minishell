/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:01:29 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/30 17:08:48 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	update_string(char **str)
{
	char	*new;

	new = ft_strdup(*str);
	if (!new)
		return (1);
	free(*str);
	*str = ft_strdup(new);
	if (!*str)
	{
		free(new);
		new = NULL;
		return (1);
	}
	return (0);
}

void	modify_string(char *str, int *quote, int new_value, int *index)
{
	int	copy;

	copy = *index;
	while (str[copy])
	{
		str[copy] = str[copy + 1];
		copy++;
	}
	*quote = new_value;
	(*index)--;
}

void	check_string(char *str, int *quotes, int *j)
{
	if (str[*j] == '\'' && quotes[0] == 0 && quotes[1] == 0)
		modify_string(str, &quotes[0], 1, j);
	else if (str[*j] == '\'' && quotes[0] == 1 && quotes[1] == 0)
		modify_string(str, &quotes[0], 0, j);
	else if (str[*j] == '\"' && quotes[0] == 0 && quotes[1] == 0)
		modify_string(str, &quotes[1], 1, j);
	else if (str[*j] == '\"' && quotes[0] == 0 && quotes[1] == 1)
		modify_string(str, &quotes[1], 0, j);
}

int	correct_quotes(char **split, int index)
{
	int	i;
	int	j;
	int	quotes[2];

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	index = 0;
	while (split[++i])
	{
		j = -1;
		while (split[i][++j])
			check_string(split[i], quotes, &j);
//		if(update_string(&split[i]))
//			return (free_split_with_index(split, index, i));
	}
	i = -1;
	while (split[++i])
		printf("Word modified:%s-->\n", split[i]);
	return (0);
}
