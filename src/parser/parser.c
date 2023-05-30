/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vduchi <vduchi@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:40:46 by vduchi            #+#    #+#             */
/*   Updated: 2023/05/30 17:52:55 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	*calculate_length(char *str, int *len_words)
{
	int	i;
	int	word;
	int	quotes[3];

	i = -1;
	word = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = 1;
	if (str[i + 1] == ' ' && i == -1)
		while (str[i + 1] == ' ')
			i++;
	len_words[0] = i + 1;
	while (str[++i])
	{
		if (str[i] == ' ' && str[i - 1] == ' ' && quotes[2])
			continue ;
		quotes_check(&str[i], quotes);
		if ((str[i] == ' ' && quotes[2])
			|| (str[i + 1] == '\0' && str[i] != ' '))
			len_words[++word] = i;
	}
	return (len_words);
}

int	*count_words(char *str, int *words)
{
	int	i;
	int	quotes[3];
	int	*len_words;

	i = -1;
	quotes[0] = 0;
	quotes[1] = 0;
	quotes[2] = 1;
	while (str[++i])
	{
		if (str[i] == ' ' && i == 0)
			while (str[i] == ' ')
				i++;
		if (str[i] == ' ' && str[i - 1] == ' ' && quotes[2])
			continue ;
		quotes_check(&str[i], quotes);
		if ((str[i] == ' ' && quotes[2])
			|| (str[i + 1] == '\0' && str[i] != ' '))
			(*words)++;
//		printf("C: %c, Single: %d, Double %d, Not_in_quotes %d, Count %d\n", str[i], quotes[0], quotes[1], quotes[2], *words);
	}
	len_words = (int *)malloc(sizeof(int) * (*words + 1));
	if (!len_words)
		return (NULL);
	return (calculate_length(str, len_words));
}

int	fill_words(char **split, char *str, int *len_words, int index)
{
	int	i;
	int	l;

	i = -1;
	l = -1;
	while (++i < index)
	{
		if (i == 0)
			split[i] = ft_substr(str, len_words[0], len_words[1] - len_words[0]);
		else
		{
			l = len_words[i];
			while (str[l] == ' ')
				l++;
			if (i == (index - 1) && str[len_words[i + 1]] != ' '
				&& str[len_words[i + 1] + 1] == '\0')
				split[i] = ft_substr(str, l, len_words[i + 1] - l + 1);
			else
				split[i] = ft_substr(str, l, len_words[i + 1] - l);
		}
		if (!split[i])
			return (free_split(split, i));
	}
	split[i] = NULL;
	return (0);
}

char	**parse_string(char *str)
{
	int		i;
	int		index;
	int		*len_words;
	char	**split;

	i = -1;
	index = 0;
	len_words = count_words(str, &index);
	if (!len_words)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (index + 1));
	if (!split)
		return (free_len(&len_words));
	if (fill_words(split, str, len_words, index))
		return (free_len(&len_words));
	while (++i < index)
		printf("Word: %s-->\n", split[i]);
	if (correct_quotes(split, index + 1))
		return (free_len(&len_words));
	return (free_my_split(split, &len_words, i + 1));
}

//int	main(void)
//{
//	int		check;
//	char	*string;
//
//	check = 1;
//	while (check)
//	{
//		string = readline("$> ");
//		if (string[0] == '\0')
//		{
//			free(string);
//			string = NULL;
//			check = 0;
//		}
//		else
//		{
//			parse_string(string);
//			free(string);
//			string = NULL;
//		}
//	}
//	return (0);
//}

//char	**parser(char *str)
//{
//	char	**elements;

//	elements = parse_string(str);
//	if (!elements)
//		return (NULL);
//	return (elements);
//}
