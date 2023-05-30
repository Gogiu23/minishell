/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:50:22 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/30 16:58:03 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	quotes_check(char *c, int *quotes)
{
	if (*c == '\'' && quotes[0] == 0 && quotes[1] == 0)
		quotes[0] = 1;
	else if (*c == '\'' && quotes[0] == 1)
		quotes[0] = 0;
	else if (*c == '\"' && quotes[1] == 0 && quotes[0] == 0)
		quotes[1] = 1;
	else if (*c == '\"' && quotes[1] == 1)
		quotes[1] = 0;
	if (quotes[0] == 0 && quotes[1] == 0 \
		&& *c != '\'' && *c != '\"')
		quotes[2] = 1;
	else
		quotes[2] = 0;
}

char	**free_my_split(char **split, int **len_words, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	free(*len_words);
	*len_words = NULL;
	return (NULL);
}

int	free_split_with_index(char **split, int index, int i)
{
	while (--index >= 0)
	{
		if (index == i)
			continue ;
		free(split[i]);
	}
	free(split);
	split = NULL;
	return (1);
}

int	free_split(char **split, int i)
{
	while (--i >= 0)
		free(split[i]);
	free(split);
	return (1);
}

char	**free_len(int **len_words)
{
	free(*len_words);
	*len_words = NULL;
	return (NULL);
}
