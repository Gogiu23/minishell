/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelon>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 18:51:35 by vduchi            #+#    #+#             */
/*   Updated: 2022/05/20 18:02:57 by vduchi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			num++;
		i++;
	}
	return (num);
}

static char	*protection_str(char *str, char **result, int pos)
{
	if (!str)
	{
		while (pos > 0)
		{
			pos--;
			free(result[pos]);
		}
		free(result);
		return (NULL);
	}
	return (str);
}

static char	**write_str(const char *s, char c, char **result)
{
	int		i;
	int		pos;
	int		start;
	char	*str;

	i = 0;
	start = 0;
	pos = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			str = ft_substr(s, start, i - start + 1);
			if (protection_str(str, result, pos) == NULL)
				return (NULL);
			result[pos] = protection_str(str, result, pos);
			pos++;
		}
		if (s[i] == c && s[i + 1] != c)
			start = i + 1;
		i++;
	}
	result[pos] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	char	**result;

	result = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	result = write_str(s, c, result);
	return (result);
}
